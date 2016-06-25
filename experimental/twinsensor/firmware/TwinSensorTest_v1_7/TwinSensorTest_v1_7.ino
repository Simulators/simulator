/*
Twin Sensor Test v1.7 Beta

Copyright 2016 Andrew J Instone-Cowie.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

	1.1 : First test version
	1.2 : With output pin
	1.3 : Attempted port to ATtiny84A
	1.4 : ATmega328P-PU breadboard test, single LED.
	1.5 : Not used
	1.6 : Options M & W for setup without a bell.
		Replace some hastily hardcoded literals with constants.
		Hold the backstroke cutoff point as a variable to avoid some FP calculations.
		Options O & o to simulate prog button presses in the CLI
	1.7	: Add USE_ATMEGA382P & USE_ATTINY85 preprocessor #defines, in preparation for an
		ATtiny version. USE_ATTINY85 removes all serial and debugging code with, resulting
		code is ~4KB. Also EEPROM values other than bellDirection and bellMinDelta are not
		loaded from EEPROM (as there is no no way to set them. Defaults are now set in the
		main code. The USE_ATTINY85 version compiles OK, but no test hardware exists yet.
	
*/

/*
ATmega328P fuse settings for 8MHz internal clock:
low_fuses=0xe2
	SUT0
	CKSEL3
	CKSEL2
	CKSEL0
high_fuses=0xd7
	SPIEN
	EESAVE
extended_fuses=0x05
	BODLEVEL1
	
ATTiny85 fuse settings for 8MHz internal clock:
low_fuses=0xe2
	SUT0
	CKSEL3
	CKSEL2
	CKSEL0
high_fuses=0xd5
	SPIEN
	EESAVE
	BODLEVEL1
extended_fuses=0xFF
*/

// Uncomment the following line to use a pin as a CRO timing pin, only when USE_ATMEGA382P
// is set (there are insufficient pins on the ATtiny85 to allow for a CRO pin.
// This should be commented out in production code.
#define USE_CRO

// Comment out ONE of the following microcontroller types. Note tha the USE_ATTINY85
// removes all all serial IO and debugging functions. 
#define USE_ATMEGA382P
//#define USE_ATTINY85

// Uncomment the following line to upload code to the ATmega328P Veroboard prototype
// (which has the signal LED on the wrong pin.....)
//#define VERO_PROTOTYPE

#ifdef USE_ATMEGA382P
// Include the free memory library, freeMemory() is called by dumpdata().
#include <MemoryFree.h>

// Include attributes file for the terminal handling functions.
#include "Terminal_Functions.h"
#endif

// The next two lines for VTSerial can also be commented out for USE_ATTINY85, but there is
// an as yet undiagnosed problem with putting a #ifdef/#endif around them.

// Include the VTSerial library for VT100-style input functions.
#include <VTSerial.h>

// Initialise the VTSerial library.
VTSerial vtSerial;

// NEED TO ADD ENABLE INTERRUPTS LIBRARY HERE LATER?

// Timers and other non-volatile data are stored in EEPROM:
// Locations 0-1   : Sensor 0-1 Strike Delay Timeouts (in cs)
// Locations 2-3   : Sensor 0-1 Rendezvous Timeouts (in ms)
// Location  4     : Debounce Timer (in ms)
// Location  5     : Serial port speed (as an index into serialSpeeds[])
// Location  6	   : Bell (wheel) handstroke direction
// Locations 7-10  : Bell minimum delta time (long, uses EEPROM.put/get)
// Locations 11-14 : Speed Factor (float, uses EEPROM.put/get)

#include <EEPROM.h>

// Software version
const int majorVersion = 1;
const int minorVersion = 7;

// -------------------------------------------------------------------------------------------
//                                    Core Sensor
// -------------------------------------------------------------------------------------------

// Define the number of sensors (always 2, indexed as 0 and 1).
const int numSensors = 2;

#ifdef USE_ATMEGA382P
// Define sensor input pins. 
const int sensorPin[] = { 4, 14 }; //A0
// Define output pin. 
const int outputPin = 3;
#elif defined USE_ATTINY85
// Define sensor input pins. 
const int sensorPin[] = { 3, 4 }; //A0
// Define output pin. 
const int outputPin = 2;
#endif

// Set up an array to store the last observed sensor status, so we can detect transitions
// in input state. This is important to avoid duplicated sensor signals. 
int sensorLastValue[2]; //initialise these in setup, and set them LOW (see below)

// Set up an array of strike signal delay timers between pulse and sending signal to interface.
// Initialise these to a standard 100ms here, for ATmega328P the values will be overwritten
// from EEPROM in setup() from EEPROM 0 & 1, for ATtiny85 they won't.
unsigned long sensorStrikeTimeout[] = { 100, 100 }; // ms

// Set up an array to hold the actual time of the next strike signal is due to be sent.
// One per sensor, so opening the possibility to odd-struckness beung configured.
// The data type is unsigned long, because these values will be the sum of
// sensorStrikeTime and the output of millis().
unsigned long sensorStrikeTime[2]; // initialise these in setup()

// Set up an array to hold the actual time of the start of the sensor pulse, to determine
// which way the wheel is going and which sensor was first to rendezvous.
// The data type is unsigned long, because these values will be output of millis().
unsigned long sensorPulseStartTime[2]; // initialise these in setup()

#ifdef USE_ATMEGA382P
// Set up an array of the characters sent on the serial port.
const char sensorChar[] = { 'A', 'B' };

// Set up an array of the permitted serial port speeds. Also declare an int to hold the
// indexed value, and a sane default.
unsigned long serialSpeeds[] = { 2400, 4800, 9600 };
int serialSpeed = 2; // index into serialSpeeds[], not the actual bps, loaded from EEPROM 
const long defaultSerialSpeed = 2; // 9600bps
#endif

// -------------------------------------------------------------------------------------------
//                                   Sensor Debounce
// -------------------------------------------------------------------------------------------

// Set up an array to hold the time that the debounce timer will expire, one per sensor. The
// data type is unsigned long, because these values will be the sum of sensorDebounceDelay and
// the output of millis().
unsigned long sensorDebounceEndTime[2]; // initialise these in setup()

// Set up a variable to hold the debounce delay time, in milliseconds. Initialise this to abort
// standard 3ms here, for ATmega328P the value will be overwritten from EEPROM in setup(),
// for ATtiny85 they won't.
unsigned long sensorDebounceTimeout = 3; // initialised from EEPROM in setup. See option B.

#ifdef USE_ATMEGA382P
// Define the maximum permitted debounce timer value. Current value is stored in EEPROM, so
// must be <=255 ms. This value is used when setting the timer via the B CLI option.
// The minDebounceTimer will always be 1ms, so no definition for it.
const unsigned long maxDebounceTimeout = 20; //ms

// Define the default debounce timer value in case the EEPROM is not yet set sensibly.
const unsigned long defaultDebounceTimeout = 3; //ms
#endif

// -------------------------------------------------------------------------------------------
//                                   Sensor Rendezvous
// -------------------------------------------------------------------------------------------

// Set up an array of sensor rendezvous timers. Initialise these to a standard 255ms here,
// for ATmega328P the values will be overwritten from EEPROM in setup() from EEPROM 2 & 3,
// for ATtiny85 they won't.
unsigned long sensorRendezvousTimeout[] = { 255, 255 }; // ms

// Set up an array to hold the time that the sensor rendezvous window will expire, one per
// sensor (although these will usually be the same). The data type is unsigned long to match
// the output of millis().
unsigned long sensorRendezvousTime[2]; // initialise these in setup()

// Setup a variable to hold the delta time between the sensors (as a proxy for 1/speed).
unsigned long sensorDeltaTime; // delta time between sensors, in ms.

// Setup a variable to hold the "speed factor" which the bellMinDelta is multiplied by to
// work out whether to suppress the backstroke. This is a float so we can have fractional,
// but the code avoids floating point calculations other than when the value changes.
// Initialise this here to 2.0, for ATmega328P load from EEPROM in setup().
float speedFactor = 2.0; // initialise these in setup() from EEPROM

#ifdef USE_ATMEGA382P
// Set up some defaults for setting sane values;
const float maxSpeedFactor = 10; // the minimum is 1.0
const float defaultSpeedFactor = 2.0;
#endif

// -------------------------------------------------------------------------------------------
//                                    State Machines
// -------------------------------------------------------------------------------------------

// Set up an array of integers to indicate which each per-sensor state machine is in the
// program state:
int sensorMachineState[2]; // initialise these in setup()

// Define the possible machine states as text to make the code more readable.
#define WAIT_FOR_INPUT 0
#define WAIT_FOR_DEBOUNCE 1
#define RENDEZVOUS 2
#define WAIT_TO_SEND 3
#define SLEEPING 4

#ifdef USE_ATMEGA382P
// -------------------------------------------------------------------------------------------
//                                      Debugging
// -------------------------------------------------------------------------------------------

// Set up a Debug Mode flag - this always cleared on reset, so not held in EEPROM.
boolean debugMode = false;

// Set up a Debug Flags Mask variable. The first 7 bits (0-6) correspond to debugging
// facilities in the code (1=on, 0=off). This allows each facility to turned on and off
// independently. These can be changed on the fly with the D option.
word debugFlagsMask = 127; //debug starts with everything enabled!

// Define the maximum configured number of flags. This value will depend on the flags
// actually implemented in the code. Currently there are 6 flags, as #defined below.
// If you add a debug level, increment this constant so that the CLI works.
const int maxDebugFlags = 7;

// Define the debug flags as text to make the code more readable
#define DEBUG_PULSE_TIMER 1		//bit 0
#define DEBUG_SHOW_MISFIRES 2	//bit 1
#define DEBUG_SHOW_DEBOUNCE 4	//bit 2
#define DEBUG_RENDEZVOUS 8		//bit 3
#define DEBUG_DELTA_TIMER 16	//bit 4
#define DEBUG_SLEEPING 32		//bit 5
#define DEBUG_BUTTON 64			//bit 6
// (See also the function printDebugFlagName(), seeing as F() is not available globally)


// -------------------------------------------------------------------------------------------
//                                   Debug Pulse Timing
// -------------------------------------------------------------------------------------------

// These variables are used for debug mode pulse length timing and counting only. There is
// no need to do pulse timing during normal operation.

// Set up two arrays to hold the actual start and end times of the sensor pulse, one per sensor.
// The data type is unsigned long, because these values will be the output of micros(). These
// are used in debug mode only to calculate the length of the (first) sensor pulse.
unsigned long pulseStartTime[2]; // initialise these in setup()
unsigned long pulseEndTime[2];   // initialise these in setup()

// Set up an array to store the last observed sensor status, so we can detect transitions.
// This array is used for debug mode pulse timing only, because updating the real
// bellSensorLastValue[] would lose the debounce effect for real simulator operation (which
// has to carry on regardless).
int pulseTimeLastValue[2]; //initialise these in setup, and set them LOW (see below)

// Set up an array of integers to count the pulses (to show how noisy a sensor is). We do this
// by counting spurious pulse *ends* (LOW to HIGH) when we aren't expecting them, and to make
// sure we timed only the first pulse.
int pulseTimeCount[2]; //initialise in setup, and set to zero


// -------------------------------------------------------------------------------------------
//                                     CLI Terminal
// -------------------------------------------------------------------------------------------

// Define the terminal display configurations as text to make the code more readable.
// See termSetFor().
#define TERM_DEFAULT 0
#define TERM_HEADING 1
#define TERM_CLI 2
#define TERM_INPUT 3
#define TERM_CONFIRM 4
#define TERM_DEBUG 5

#endif

// -------------------------------------------------------------------------------------------
//                                     LED & Timing
// -------------------------------------------------------------------------------------------

// Define pin and parameters for the signal LED, and optionally a CRO timing pin.
// Putting the Veroboard prototype LED on logical pin 10 was a hardware error.
#ifdef VERO_PROTOTYPE
const int LED = 10;
#elif defined USE_ATMEGA382P
const int LED = 16; //A2
#elif defined USE_ATTINY85
const int LED = 0;
#endif

boolean ledBlinkState = false;
unsigned long ledBlinkPeriod; //msec
unsigned long ledNextStateChangeTime; //msec

#ifdef USE_CRO
const int CROpin = 5; 
#endif


// ------------------------------------------------------------------------------------------
//                                      Prog Button
// ------------------------------------------------------------------------------------------

// Define pin and parameters for the programming mode button. Any press between 
// buttonMinimumPressTime and buttonShortPressTime is a short press. Any press longer than
// buttonShortPressTime is a long press. Any press within buttonGuardTime of the last press
// is rejected. Note that the code detects the press (and its duration) when the button
// is released.

#ifdef USE_ATMEGA382P
const int progButton = 15; //A1
#elif defined USE_ATTINY85
const int progButton = 1;
#endif

boolean buttonPressPending = false;
unsigned long buttonPressStartTime;
unsigned long buttonPressEndTime;
unsigned long buttonDuration; //msec

// Define parameters for the length of button presses
const unsigned long buttonGuardTime = 500; //msec
const unsigned long buttonMinimumPressTime = 50; //msec
const unsigned long buttonShortPressTime = 1000; //msec

// scanButton() return codes
#define BUTTON_SHORT 1
#define BUTTON_LONG 2
#define BUTTON_TOO_SHORT 99
#define BUTTON_TOO_EARLY 98


// ------------------------------------------------------------------------------------------
//                                      Learning Modes
// ------------------------------------------------------------------------------------------

// Define constants and variables for the learning modes. A short press of the button
// toggles learnDirection on and off. A long press toggles learnMinDelta on and off (with
// save of value - a short press cancels any change). See also Options o & O.

boolean learnDirection = false;
boolean learnMinDelta = false;

// Set up a time variable to store the learned minimum delta time. This will get stored in
// (a series of) EEPROM locations for startup. See sensorDeltaTime. This is the working value.
unsigned long bellMinDelta; //initialised on loadFromEEPROM()

// Set up a time variable to store the rolling minimum value time, initialised to 10 secs.
unsigned long trackedMinDelta = 10000;

// Set up some defaults for setting sane values;
const unsigned long maxBellMinDelta = 100;
const unsigned long defaultBellMinDelta = 10;

// Set up a variable to hold the cut-off point for the backstroke, to avoid having to
// calculate using FP maths for every strike.
unsigned long backstrokeCutoffDelta;

// Set up a byte variable to store the direction of the bell. Byte not boolean so this can
// be stored in EEPROM for startup. 0 = A triggers first on handstroke, 1 = B triggers first
// on handstroke.
byte bellDirection = 0; 

/*
*********************************************************************************************
*                                   Function setup()                                        *
*********************************************************************************************
*/

// the setup routine runs once on powerup or reset:
void setup() {   

	// initialize the LED pins as outputs.
	pinMode( LED, OUTPUT );

	// set LED pins appropriately (turn the LEDs off).
	digitalWrite( LED, LOW );
	
	// initialize the button pins as an input.
	pinMode( progButton, INPUT_PULLUP );

	// initialize the timing pin, if used.
#ifdef USE_CRO
	pinMode( CROpin, OUTPUT );
	digitalWrite( CROpin, LOW );
#endif

	// Initialise the output pin and set it HIGH
	pinMode( outputPin, OUTPUT );
	digitalWrite( outputPin, HIGH );

	// Load default values from EEPROM
	loadFromEEPROM();

	// generic setup loop counter
	int i;

	// Two sensors...
	for ( i = 0; i < numSensors; i++ ) {

		// initialize the sensor digital input pins with the pullup resistors active.
		// The detectors pull the pin LOW when there is a signal.
		pinMode( sensorPin[i], INPUT_PULLUP );

		// initialize the array holding the last sensor status for each sensor. Set these initially
		// to be LOW, so that the very first pass of loop() doesn't find a spurious transition
		// if the bells are down (and thus signalling continuously) and result in a fire-up
		// on startup.
		sensorLastValue[i] = LOW;
		
		#ifdef USE_ATMEGA382P
		// initialise the variables used for debug mode pulse length measurements    
		pulseTimeLastValue[i] = HIGH;
		pulseTimeCount[i] = 0;
		#endif
		
		// Set the thing going waiting for input
		sensorMachineState[i] = WAIT_FOR_INPUT;
		
	}
	
	// Calculate the initial value of the backstroke cutoff delta time. This is done here
	// (and when those values change) to avoid doing FP math in every signal. The term
	// "Cutoff" implies ringing down, the same value is "cut-in" for ringing up. speedFactor
	// & bellMinDelta are loaded from EEPROM.
	backstrokeCutoffDelta = speedFactor * bellMinDelta;

#ifdef USE_ATMEGA382P
	// Set up the serial port. 
	Serial.begin( serialSpeeds[serialSpeed], SERIAL_8N1 );
	termInit();
	Serial.print(F("<Sensor "));
	Serial.print( majorVersion );
	Serial.print(".");
	Serial.print( minorVersion );
	Serial.println(">");
#endif

	// Announce the software version on startup or reset
	blinkLED( LED, majorVersion, minorVersion ); 

}


/*
*********************************************************************************************
*                                     Function loop()                                       *
*********************************************************************************************
*/

// once setup has completed, the loop routine runs over and over again forever:
void loop() {

	// main loop start, waggle the CRO timing pin up. 

#ifdef USE_CRO
	digitalWrite( CROpin, HIGH );
#endif

	//Process the button and the LEDs
	processButton(scanButton());
	processLed();

	// main loop counters and scratch variables
	int i; // this sensor
	int j; // this sensor - 1
	int otherSensor; //abs(j)
	
	// Variable to store the value read from a pin
	int sensorValue;

	// loop around both sensors and look at the state of the state machine for each
	for ( i = 0; i < numSensors; i++ ) {

		switch ( sensorMachineState[i] ) {

			// ---------------------------------------------------------------------------------------
			// -                                 WAIT_FOR_INPUT                                      -
			// ---------------------------------------------------------------------------------------
		case WAIT_FOR_INPUT:

			// This sensor is in "WAIT_FOR_INPUT" state
			// Read the value from the sensor pin
			sensorValue = digitalRead( sensorPin[i] );
			
			if ( sensorValue == LOW && sensorLastValue[i] == HIGH ) {
				
				// This is a HIGH to LOW transition since we last looked, so we have the start of a
				// sensor pulse. Note the time, this is needed to establish precedence at rendezvous
				sensorPulseStartTime[i] = millis();
				
				// Set the time that the signal should be sent to the interface to now + the delay
				// timeout. (Do this calculation here so we only have to do the comparison in following
				// loops, not the addition)
				sensorStrikeTime[i] = sensorPulseStartTime[i] + sensorStrikeTimeout[i];

				// Set the time that the debounce timer will expire to to now + the debounce timeout.
				// (Do this calculation here so we only have to do the comparison in following loops,
				// not the addition)
				sensorDebounceEndTime[i] = sensorPulseStartTime[i] + sensorDebounceTimeout;
				
				// Set the time that the rendezvous timer will expire to to now + the rendezvous timeout.
				// (Do this calculation here so we only have to do the comparison in following loops,
				// not the addition)
				sensorRendezvousTime[i] = sensorPulseStartTime[i] + sensorRendezvousTimeout[i];
				
				// Set the last observed value to the current state of the sensor, which is LOW.
				// For an explanation of why we do this, see below.
				sensorLastValue[i] = sensorValue;
				
				// Move the machine state on to "WAIT_FOR_DEBOUNCE"
				sensorMachineState[i] = WAIT_FOR_DEBOUNCE;

#ifdef USE_ATMEGA382P				
				// If we are in debug mode, grab the pulse start time and reset the counter.
				// Both the pulse timer and the misfire detection require pulse timing to be done
				if ( debugMode && isDebugFlagSet( DEBUG_PULSE_TIMER | DEBUG_SHOW_MISFIRES ) ) {
					
					pulseStartTime[i] = micros();
					
					// Avoid overflows giving a silly number if we get to a debug print before the end
					// of the first pulse! A pulse length of 0 means the pulse has not ended yet.
					pulseEndTime[i] = pulseStartTime[i];
					pulseTimeLastValue[i] = sensorValue;
					pulseTimeCount[i] = 0; //incremented at the END of the pulse
					
					// We only run this code at the start of a valid pulse. The counter is used
					// to ensure that we only measure the duration of the first pulse in a potential
					// string of noisy input pulses (which are ignored by the main interface code).
					
				} //debugMode
#endif

			}
			else // this is not the start of a pulse
			{

				// Set the last observed value to the current state of the sensor, which may
				// (still) be LOW or (by now) HIGH.
				sensorLastValue[i] = sensorValue;
				
				// We stay in the "WAIT_FOR_INPUT" state. We may have come back here and found the
				// sensor still LOW after sending the signal to the simulator if the delay is
				// very short and the pulse very long, hence the transition detection.
				
			} //sensorValue
			
			break; //sensorMachineState == WAIT_FOR_INPUT

			// ---------------------------------------------------------------------------------------
			// -                                WAIT_FOR_DEBOUNCE                                    -
			// ---------------------------------------------------------------------------------------      
		case WAIT_FOR_DEBOUNCE:
			
			// This sensor is in "WAIT_FOR_DEBOUNCE" state.
			// Check whether the signal has ended too soon (and so is considered noise).
			
			// Read the value from the sensor pin
			sensorValue = digitalRead( sensorPin[i] );
			
			if ( sensorValue == HIGH ) {
				
				// Input has gone high again, pulse was too short, so this is a misfire.
				
				// Set the machine state back to "WAIT_FOR_INPUT"
				sensorMachineState[i] = WAIT_FOR_INPUT;

#ifdef USE_ATMEGA382P				
				// If we are in a debug mode, report the misfire and pulse data.
				if ( debugMode && isDebugFlagSet( DEBUG_SHOW_MISFIRES ) ) {
					
					// Grab the time of the end of the pulse (approximately) 
					pulseEndTime[i] = micros();
					
					Serial.print( sensorChar[i] );
					Serial.print(F(" "));
					Serial.print( sensorPulseStartTime[i] );
					Serial.print(F(" M " ));
					Serial.println( pulseEndTime[i] - pulseStartTime[i] );
					
					// There is no need to set the pulse counter here - misfires are by
					// definition pulse #1 of 1. There may however be noise pulses *after*
					// the first one which is longer than the debounce timer, so we will
					// update the pulse counter when in WAIT_TO_SEND
					
				} //debugMode
#endif

			}
			else if ( millis() >= sensorDebounceEndTime[i] )
			{
				
				// Input is still low (otherwise we would have bailed out in the clause above)
				// and the debounce timer has now expired, so we have a good signal at least 
				// sensorDebounceTimeout ms long. Move the machine on to RENDEZVOUS state.
				sensorMachineState[i] = RENDEZVOUS;

#ifdef USE_ATMEGA382P				
				if ( debugMode && isDebugFlagSet( DEBUG_SHOW_DEBOUNCE ) ) {
					Serial.print( sensorChar[i]);
					Serial.print(F(" "));
					Serial.print( sensorPulseStartTime[i] );
					Serial.println(F(" D" ));
				} //debugMode		 
#endif
				
			}
			
			// There is no other else here - if the input  is still low and the timer
			// has not expired, we are still testing the signal quality so we just loop round.
			
			break; // sensorMachineState == WAIT_FOR_DEBOUNCE


			// ---------------------------------------------------------------------------------------
			// -                                    RENDEZVOUS                                       -
			// ---------------------------------------------------------------------------------------      
		case RENDEZVOUS:
			
			// This sensor is in "RENDEZVOUS" state.
			// Check whether the other sensor is in rendezvous yet, and which sensor has precedence
			
			// Sensor indices are 0 & 1, so if this sensor = i, then the other sensor =
			// abs( i - 1 ), but note the caveat in the Arduino documentation that putting
			// functions inside abs() doesn't work properly, hence this code
			j = i - 1; // NB NOT i-- !
			otherSensor = abs(j);
			
			if ( millis() >= sensorRendezvousTime[i] ) {
				// This sensor has been waiting too long in rendezvous state, go back to
				// WAIT_FOR_INPUT. Rendezvous failed.
				sensorMachineState[i] = WAIT_FOR_INPUT;
				
				// Turn the LED off again if it was on
				strikeLED( false );

#ifdef USE_ATMEGA382P				
				// If we are in a debug mode, report the rendezvous miss.
				if ( debugMode && isDebugFlagSet( DEBUG_RENDEZVOUS ) ) {

					Serial.print( sensorChar[i] );
					Serial.print(F(" "));
					Serial.print( sensorPulseStartTime[i] );
					Serial.println(F(" R X " ));
					
				} //debugMode			
#endif
				
			} // Rendezvous time expired
			
			else if ( sensorMachineState[otherSensor] == RENDEZVOUS )
			{
				// Still within the rendezvous window, and the other sensor is in as well
				
				// Is this sensor the first (and so has precedence)?
				if ( sensorPulseStartTime[otherSensor] > sensorPulseStartTime[i] ) {
					// this sensor has precedence, so carry on
					
					// If learnDirection is true, save the current direction as handstroke.
					// That function unsets learnDirection. Note that this function gets called
					// as soon as rendezvous is confirmed, regardless of delta speed, so this
					// can be set in the belfry with the bell down (pull the bell to one side
					// (away from the pulley), short button press, swing the bell past the sensor).
					if ( learnDirection ) {
						setDirection(i);
					}
					
					// Calculate the time delta between the two sensors. This sensor was first,
					// so by definition the pulse time is earlier (smaller), and this result
					// will be positive.
					sensorDeltaTime = sensorPulseStartTime[otherSensor] - sensorPulseStartTime[i];

#ifdef USE_ATMEGA382P
					// If we are in a debug mode, report the delta time.
					if ( debugMode && isDebugFlagSet( DEBUG_DELTA_TIMER ) ) {

						Serial.print( sensorChar[i] );
						Serial.print(F(" "));
						Serial.print( sensorPulseStartTime[i] );
						Serial.print(F(" T " ));
						Serial.println( sensorDeltaTime );
						
					} //debugMode
#endif
					
					// If learnMinDelta is true, pass the delta time to the function
					// keeping track of the learned minimum. This function does not unset
					// learnMinDelta, the button is pressed a second time to terminate.
					// This updates trackedMinDelta, which is global in scope.
					if ( learnMinDelta ) {
						trackMinDelta( sensorDeltaTime );
					}
					
					// *********************************************************************
					// Current thinking is that there may not be a real need to trim the
					// value of sensorStrikeTimeout[], main impact on strike time changes
					// seems to be above the strike point. If there is then hopefully the
					// same trigger point can be used.
					// *********************************************************************
					
					// Decide whether to suppress the backstroke because the bell isn't
					// high enough. The handstroke always signals. To supress the stroke, 
					// move on to SLEEPING instead of WAIT_TO_SEND.
					
					// Empirically a speedFactor of "about 2" seems to sound about right,
					// based on tests on a single bell,
					if ( ( bellDirection != i ) && ( sensorDeltaTime > backstrokeCutoffDelta ) ) {
						//i.e. "this is backstroke and moving slowly".
						// 
						// Set this sensor's machine state on to "SLEEPING"
						sensorMachineState[i] = SLEEPING;
					}
					else
					{
						// Move on to send the signal
						sensorMachineState[i] = WAIT_TO_SEND;
						
						// Use the LED to signal strikes. Turn on when rendezvous achieved
						// and we not we are not supressing this strike, off when signal is sent.
						// (The LED may be used in other debug options, so hand this off to a function.)
						strikeLED( true );
					}
					
					// Set the other sensor machine state to "SLEEPING"
					sensorMachineState[otherSensor] = SLEEPING;  
					
				} // 1st to RENDEZVOUS
				
				/* No else here - If this sensor's start time is later than the other sensor,
				then this sensor is the second to arrive in rendezvous. The other sensor
				will see this sensor in rendezvous (perhaps next time round) and handle
				any output, and send the sensor to sleep. Otherwise the rendezvous timer will
				eventually expire and go back to WAIT_FOR_INPUT if nothing else happens.
				*/
				
			} // otherSensor == RENDEZVOUS
			
			// No else here either - This is the only sensor in rendezvous, keep waiting

#ifdef USE_ATMEGA382P			
			// If we are in debug mode then we DO read the pin, but only to check for the end of
			// sensor pulses during the "rendezvous" period, and grab the time for debug output.
			
			if ( debugMode && isDebugFlagSet( DEBUG_PULSE_TIMER ) ) {
				
				int sensorValue;
				sensorValue = digitalRead(sensorPin[i]);
				
				if ( sensorValue == HIGH && pulseTimeLastValue[i] == LOW ) {
					// LOW to HIGH transition, a pulse just ended
					
					if ( pulseTimeCount[i] == 0 ) {
						
						// This is the end of the first pulse (after a successful debounce), so note the
						// time.
						pulseEndTime[i] = micros();
						pulseTimeCount[i]++; // so we don't time any subsequent noisy pulses
						
					}
					else
					{
						
						// End of a spurious noise pulse after the first timed one, increment the
						// pulse counter.
						pulseTimeCount[i]++;
						
					}
					
				} //bellSensorValue == HIGH && pulseTimeLastValue[i] == LOW
				
				// Update the last seen sensor value.
				pulseTimeLastValue[i] = sensorValue;
				
			} //debugMode
#endif			
			
			break; // sensorMachineState == RENDEZVOUS

			
			// ---------------------------------------------------------------------------------------
			// -                                    WAIT_TO_SEND                                     -
			// ---------------------------------------------------------------------------------------      
		case WAIT_TO_SEND:
			
			// This sensor is in "WAIT_TO_SEND" state.

			// We don't read the sensor pin at all when in this state. This debounces the input
			// and ignores spurious input.
			
			// Check the timer - has it expired?
			if ( millis() >= sensorStrikeTime[i] ) {
				
				// Timer has expired, send the appropriate signal to the interface.
				// Generate an output pulse on the output pin
				// Nothing else time critical is happening at this point, so simply called
				// delay() to give a suitable pulse length.
				digitalWrite( outputPin, LOW );
				delay(10);
				digitalWrite( outputPin, HIGH);
				
				// Turn the LED off again if appropriate
				strikeLED( false );
				
				// Set the machine state back to "WAIT_FOR_INPUT"
				sensorMachineState[i] = WAIT_FOR_INPUT;       

#ifdef USE_ATMEGA382P				
				// If we are in debug, send the timer values. This could be logged to a file for
				// later analysis. Note that only the pulse from the sensor with precedence is reported.
				if ( debugMode && isDebugFlagSet( DEBUG_PULSE_TIMER ) ) {
					
					Serial.print( sensorChar[i] );
					Serial.print(F(" "));
					Serial.print( sensorPulseStartTime[i] );
					Serial.print(F(" S "));
					Serial.print( pulseEndTime[i] - pulseStartTime[i] );
					Serial.print(F(" "));
					Serial.println(pulseTimeCount[i]);
					
					// Reset the pulse counter, as we are going back to WAIT_FOR_INPUT
					pulseTimeCount[i] = 0;
					
				} //debugMode
#endif

			} //timer expired

			// There is no ELSE here - there is nothing to do if we are waiting to send and the
			// timer has not expired, other than do the debugging below, we just loop and check
			// again on the next loop.

#ifdef USE_ATMEGA382P			
			// If we are in debug mode then we DO read the pin, but only to check for the end of
			// sensor pulses during the "wait to send" period, and grab the time for debug output.
			
			if ( debugMode && isDebugFlagSet( DEBUG_PULSE_TIMER ) ) {
				
				int sensorValue;
				sensorValue = digitalRead(sensorPin[i]);
				
				if ( sensorValue == HIGH && pulseTimeLastValue[i] == LOW ) {
					// LOW to HIGH transition, a pulse just ended
					
					if ( pulseTimeCount[i] == 0 ) {
						
						// This is the end of the first pulse (after a successful debounce), so note the
						// time.
						pulseEndTime[i] = micros();
						pulseTimeCount[i]++; // so we don't time any subsequent noisy pulses
						
					}
					else
					{
						
						// End of a spurious noise pulse after the first timed one, increment the
						// pulse counter.
						pulseTimeCount[i]++;
						
					}
					
				} //bellSensorValue == HIGH && pulseTimeLastValue[i] == LOW
				
				// Update the last seen sensor value.
				pulseTimeLastValue[i] = sensorValue;
				
			} //debugMode  
#endif
			
			break; //sensorMachineState == WAIT_TO_SEND
			

			// ---------------------------------------------------------------------------------------
			// -                                      SLEEPING                                       -
			// ---------------------------------------------------------------------------------------      
		case SLEEPING:
			
			// This sensor is in "SLEEPING" state.

			// A sensor is put into SLEEPING state if it reached RENDEZVOUS without precedence.
			// It sleeps until sensorStrikeTime.
			
			// Check the timer - has it expired?
			if ( millis() >= sensorStrikeTime[i] ) {
				
				// Set the machine state back to "WAIT_FOR_INPUT"
				sensorMachineState[i] = WAIT_FOR_INPUT;       

#ifdef USE_ATMEGA382P				
				// If we are in debug, note that we woke up.
				if ( debugMode && isDebugFlagSet( DEBUG_SLEEPING ) ) {
					
					Serial.print( sensorChar[i] );
					Serial.print(F(" "));
					Serial.print( sensorPulseStartTime[i] );
					Serial.println(F(" Z"));

				} //debugMode
#endif
				
			} //timer expired

			break; //sensorMachineState == SLEEPING

			
		} //case
		
	} //for 0,1 sensors

	// main loop complete, waggle the timing pin down.
#ifdef USE_CRO
	digitalWrite( CROpin, LOW );
#endif

} //loop()

/*
*********************************************************************************************
*                                  Function serialEvent()                                   *
*********************************************************************************************
*/

#ifdef USE_ATMEGA382P
void serialEvent() {

	/*  
	If we have some serial input, pass the characters to the CLI handler
	*/

	// We got here because there is stuff in the serial buffer waiting for us.
	// We'll stay here until we have processed everything there is before we revert to loop().  
	while ( Serial.available() ) {

		// Hand the first byte over to handleCLI() to see if that can make sense of it...
		handleCLI( Serial.read() );
		
	}//serial available

}//serial event
#endif

