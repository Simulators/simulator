/*
One Bell Simulator Interface v1.2 Beta

Copyright 2014, 2015 Andrew J Instone-Cowie.

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

Tested against Abel 3.9.1, Beltower 2015 (12.29) & Virtual Belfry 3.2.

	1.1 : One Bell version derived from Simulator Interface v2.2.
		Reduce code size heavily for One Bell version (8kB ATTiny85).
		Eliminate VTSerial (back to v1.7 cyclic code for option U, new code for option D).
		Implement SoftwareSerial and associated changes for ATTiny85 version
		Too many changes from main code to have a #define HW_ONEBELL!
		7,420 Bytes Flash, 215 Bytes SRAM.
		** 1st Manx Release (on Rev A PCB) - 20/05/2015 **
		Tested against Abel 3.9.1 (no code changes).
		Tested against Virtual Belfry 3.2 (no code changes).
	1.2 : Re-indent all the code with TestFX.
		Changed EEPROM handling to read-before-write to reduce EEPROM write wear, as per
		ATmel recommended practice.
		Amended recommended ATmega328P fuse settings.
		7,468 Bytes Flash, 215 Bytes SRAM
	
*/

/*
Pins used on the ATTiny85 are as follows (physical package pins in brackets):
D0 (5) - LED
D2 (7) - Sensor Input
D3 (2) - Serial TX
D4 (3) - Serial RX
This minimises having hardwired connections to the ICSP pins. It is necessary to
unplug the IR sensor module from the PCB when programming the AVR.

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

// Include the free memory library, freeMemory() is called by dumpdata().
#include <MemoryFree.h>

// Include the SoftwareSerial library (no hardware UART on the ATTiny85).
#include <SoftwareSerial.h>

// Initialise the SoftwareSerial library.
SoftwareSerial mySerial(4, 3); // RX, TX

// Bell timers and other non-volatile data are stored in EEPROM. The locations are the
// same as the 12-bell simulator board, but some locations are not used in the One Bell
// implementation:
// Locations 0-11  : Bells 1-12 Delay Timers (in cs)
// Locations 12-15 : Reserved for future Bells 13-16 Delay Timers
// Location  16    : Accidental Status (#,b) - Not supported yet
// Location  17    : Simulator Type (A,B,R,X)
// Location  18    : Number of channels (bell pins) active & to be scanned - NOT USED
// Location  19    : Debounce Timer (in ms)
// Location  20    : Serial port speed (as an index into serialSpeeds[]) - NOT USED

#include <EEPROM.h>

// Software version
const int majorVersion = 1;
const int minorVersion = 2;

// -------------------------------------------------------------------------------------------
//                                    Core Simulator
// -------------------------------------------------------------------------------------------

// The number of input channels for the One Bell version, oddly enough, always equals 1.
// Note that the delay timers data structure is still set up for 12 bells, as the simulators
// send and expect 12-bell data.
int numChannels = 1;

// Define bell sensor input pin.
const int bellSensorPin = 2;

// Define the character sent on the serial port to the simulator software, as
// defined in the MBI interface specification. This is an ASCII character, and for the One
// Bell version is always '1'.
const char bellStrikeChar = '1';

// Set up a variable to store the last observed sensor status, so we can detect transitions
// in input state. This is important to avoid duplicated sensor signals. 
int bellSensorLastValue; //initialise in setup, and set LOW (see below)

// Set up an array of strike signal timer delays, one per bell. The data type is unsigned
// long, because these values will be added to the output of millis(). Note that this code
// does everything in millisenconds (as does Beltower), although the MBI interface and Abel
// define values in centiseconds.
unsigned long bellStrikeDelay[12]; // initialise these in setup()

// Set up a variable to hold the actual time of the next character is due to be sent. The
// data type is unsigned long, because these values will be the sum of bellStrikeDelay and
//the output of millis().
unsigned long bellCharSendTime; // initialise in setup()

// -------------------------------------------------------------------------------------------
//                                   Sensor Debounce
// -------------------------------------------------------------------------------------------

// Set up a variable to hold the time that the debounce timer will expire. The data type is
// unsigned long, because these values will be the sum of bellDebounceDelay and the output
// of millis().
unsigned long bellDebounceEndTime; // initialise in setup()

// Set up a variable to hold the debounce delay time, in milliseconds.
unsigned long bellDebounceDelay ; // initialised from EEPROM in setup

// Define the maximum permitted debounce timer value. Current value is stored in EEPROM, so
// must be <=255 ms. This value is used when setting the timer via the U CLI option.
// The minDebounceTimer will always be 1ms, so no definition for it.
const unsigned long maxDebounceDelay = 20; //ms

// Define the default debounce timer value in case the EEPROM is not yet set sensibly.
const unsigned long defaultDebounceDelay = 4; //ms

// -------------------------------------------------------------------------------------------
//                                    State Machines
// -------------------------------------------------------------------------------------------

// Set up an integer variable to indicate whether the state machine is in the
// program state "WAIT_FOR_INPUT" (0), "WAIT_FOR_DEBOUNCE" (1) or "WAIT_TO_SEND"(2))
int bellMachineState; // initialise in setup()

// Define the possible machine states as text to make the code more readable.
#define WAIT_FOR_INPUT 0
#define WAIT_FOR_DEBOUNCE 1
#define WAIT_TO_SEND 2

// -------------------------------------------------------------------------------------------
//                                      Debugging
// -------------------------------------------------------------------------------------------
// Set up a Debug Mode flag - this always cleared on reset, so not held in EEPROM.
boolean debugMode = false;

// Set up a Debug Flags Mask variable. The first 4 bits (0-3) correspond to debugging
// facilities in the code (1=on, 0=off). This allows each facility to turned on and off
// independently. These can be changed on the fly with the D option.
int debugFlagsMask = 1; //debug starts with DEBUG_PULSE_TIMER flag set by default

// Define the maximum configured number of flags. This value will depend on the flags
// actually implemented in the code. Currently there are 3 flags, as #defined below.
// If you add a debug level, increment this constant so that the CLI works.
const int maxDebugFlags = 3;

// Define the debug flags as text to make the code more readable
#define DEBUG_PULSE_TIMER 1		//bit 0
#define DEBUG_SHOW_MISFIRES 2	//bit 1
#define DEBUG_SHOW_DEBOUNCE 4	//bit 2
// (See also the function printDebugFlagName(), seeing as F() is not available globally)

// -------------------------------------------------------------------------------------------
//                                   Debug Pulse Timing
// -------------------------------------------------------------------------------------------

// These variables are used for debug mode pulse length timing and counting only. There is
// no need to do pulse timing during normal operation.

// Set up two variables to hold the actual start and end times of the sensor pulse.
// The data type is unsigned long, because the values will be the output of micros(). These
// are used in debug mode only to calculate the length of the (first) sensor pulse.
unsigned long pulseStartTime; // initialise in setup()
unsigned long pulseEndTime;   // initialise in setup()

// Set up a variable to store the last observed sensor status, so we can detect transitions.
// This is used for debug mode pulse timing only, because updating the real
// bellSensorLastValue would lose the debounce effect for real simulator operation (which
// has to carry on regardless).
int pulseTimeLastValue; //initialise in setup, and set LOW (see below)

// Set up an integer variable to count the pulses (to show how noisy a sensor is). We do this
// by counting spurious pulse *ends* (LOW to HIGH) when we aren't expecting them, and to make
// sure we timed only the first pulse.
int pulseTimeCount; //initialise in setup, and set to zero

// -------------------------------------------------------------------------------------------
//                                     LEDs & Timing
// -------------------------------------------------------------------------------------------

// Signal LED pin definition
const int LED = 0;

/*
*********************************************************************************************
*                                   Function setup()                                        *
*********************************************************************************************
*/

// the setup routine runs once on powerup or reset:
void setup() {   

	// initialize the LED pin as output and turn the LED off.
	pinMode( LED, OUTPUT );
	digitalWrite( LED, LOW );

	// setup data structures

	// initialize the bell sensor digital input pin with the pullup resistor active.
	// The photohead pulls the pin LOW when there is a signal.
	pinMode( bellSensorPin, INPUT_PULLUP );

	// initialize the last sensor status for the bell. Set this initially
	// to be LOW, so that the very first pass of loop() doesn't find a spurious transition
	// if the bells are down (and thus signalling continuously) and result in a fire-up
	// on startup.
	bellSensorLastValue = LOW;

	// generic setup loop counter
	int i;
	for ( i = 0; i < 12; i++ ) {
		// Load the strike delays from EEPROM, converting the cs byte value in EEPROM to ms.
		// There are always 12 of these sent by the simulator, even though this is the One Bell
		// version of the hardware.
		bellStrikeDelay[i] = long( EEPROM.read(i) ) * 10;
	}
	
	// initialize the strike send time value. This value should never get used, because
	// it will be overwritten when the actual time is calculated as the state machine enters
	// "WAIT_TO_SEND".
	bellCharSendTime = millis();

	// initialize the debounce timer end time value. This value should never get used,
	// because it will be overwritten when the actual time is calculated as the state
	// machine leaves "WAIT_FOR_INPUT".
	bellDebounceEndTime = millis();

	// initialize the state machine flag. Starts by waiting for input.
	// Setting this to "WAIT_TO_SEND" would result in an immediate timer expiry for every
	// bell on the first pass of loop(), and another one row fire-up.
	bellMachineState = WAIT_FOR_INPUT;

	// initialise the variables used for debug mode pulse length measurements    
	pulseStartTime = micros();
	pulseEndTime = micros();
	pulseTimeLastValue = HIGH;
	pulseTimeCount = 0;
	
	// initialise the debounce timer from EEPROM. If the value is <1 or >20, set it to default.
	// Cast the byte value read into a long so we can add it to millis().
	bellDebounceDelay = long( EEPROM.read(19) );
	// but the EEPROM value may not be set to a sensible value! Seed a sane value.
	if ( bellDebounceDelay < 1 || bellDebounceDelay > maxDebounceDelay ) {
		bellDebounceDelay = defaultDebounceDelay;
	}

	// Set up the serial port. The MBI interface spec uses 2400 8N1. Note that SoftwareSerial
	// does not support the 2400_8N1 syntax.
	mySerial.begin( 2400 );
	mySerial.listen();
	// For compatibility with the MBI startup message - It's unclear whether any of the
	// simulators actually use this for anything.
	mySerial.println(F("<On.>"));

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

	// main loop start, process the state machine. There is only one state machine in this
	// version, so there is no for loop here.

	// Variable to store the value read from the pin
	int bellSensorValue;
	
	switch ( bellMachineState ) {

		// ---------------------------------------------------------------------------------------
		// -                                 WAIT_FOR_INPUT                                      -
		// ---------------------------------------------------------------------------------------
	case WAIT_FOR_INPUT:

		// The bell is in "WAIT_FOR_INPUT" state
		// Read the value from the sensor pin
		bellSensorValue = digitalRead( bellSensorPin );
		
		if ( bellSensorValue == LOW && bellSensorLastValue == HIGH ) {
			
			// This is a HIGH to LOW transition since we last looked, so we have the start of a
			// sensor pulse. Note the current time in a scratch variable (to avoid calling
			// millis() twice)
			unsigned long timeNow;
			timeNow = millis();
			
			// Set the time that the character should be sent to the simulator to now + the delay
			// timer. (Do this calculation here so we only have to do the comparison in following
			// loops, not the addition)
			bellCharSendTime = timeNow + bellStrikeDelay[0]; //always delay[0] for the One Bell

			// Set the time that the debounce timer will expire to to now + the debounce timer.
			// (Do this calculation here so we only have to do the comparison in following loops,
			// not the addition)
			bellDebounceEndTime = timeNow + bellDebounceDelay;
			
			// Set the last observed value to the current state of the sensor, which is LOW.
			// For an explanation of why we do this, see below.
			bellSensorLastValue = bellSensorValue;

			// Use the LED to signal strikes on bell 1 (MBI always starts at bell 1, even for
			// <12 bells). Turn on when the pulse is received, off when character is sent. 
			digitalWrite( LED, HIGH );
			
			// Move the machine state on to "WAIT_FOR_DEBOUNCE"
			bellMachineState = WAIT_FOR_DEBOUNCE;
			
			// If we are in debug mode, grab the pulse start time and reset the counter.
			// Both the pulse timer and the misfire detection require pulse timing to be done
			if ( debugMode && isDebugFlagSet( DEBUG_PULSE_TIMER | DEBUG_SHOW_MISFIRES ) ) {
				
				pulseStartTime = micros();
				
				// Avoid overflows giving a silly number if we get to a debug print before the end
				// of the first pulse! A pulse length of 0 means the pulse has not ended yet.
				pulseEndTime = pulseStartTime;
				pulseTimeLastValue = bellSensorValue;
				pulseTimeCount = 0; //incremented at the END of the pulse
				
				// We only run this code at the start of a valid pulse. The counter is used
				// to ensure that we only measure the duration of the first pulse in a potential
				// string of noisy input pulses (which are ignored by the main interface code).
				
			} //debugMode
			
		}
		else // this is not the start of a pulse
		{

			// Set the last observed value to the current state of the sensor, which may
			// (still) be LOW or (by now) HIGH.
			bellSensorLastValue = bellSensorValue;
			
			// We stay in the "WAIT_FOR_INPUT" state. We may have come back here and found the
			// sensor still LOW after sending the character to the simulator if the delay is
			// very short and the pulse very long, hence the transition detection.
			
		} //bellSensorValue
		
		break; //bellMachineState == WAIT_FOR_INPUT

		// ---------------------------------------------------------------------------------------
		// -                                WAIT_FOR_DEBOUNCE                                    -
		// ---------------------------------------------------------------------------------------      
	case WAIT_FOR_DEBOUNCE:
		
		// The bell is in "WAIT_FOR_DEBOUNCE" state.
		// Check whether the signal has ended too soon (and so is considered noise).
		
		// Read the value from the sensor pin
		bellSensorValue = digitalRead( bellSensorPin );
		
		if ( bellSensorValue == HIGH ) {
			
			// Input has gone high again, pulse was too short, so this is a misfire.
			
			// Turn the LED off again if it was on
			digitalWrite( LED, LOW );
			
			// Set the machine state back to "WAIT_FOR_INPUT"
			bellMachineState = WAIT_FOR_INPUT;
			
			// If we are in a debug mode, report the misfire and pulse data.
			if ( debugMode && isDebugFlagSet( DEBUG_SHOW_MISFIRES ) ) {
				
				// Grab the time of the end of the pulse (approximately) 
				pulseEndTime = micros();
				
				mySerial.print( bellStrikeChar );
				mySerial.print(F(" "));
				mySerial.print( bellCharSendTime );
				mySerial.print(F(" M " ));
				mySerial.println( pulseEndTime - pulseStartTime );
				
				// There is no need to set the pulse counter here - misfires are by
				// definition pulse #1 of 1. There may however be noise pulses *after*
				// the first one which is longer than the debounce timer, so we will
				// update the pulse counter when in WAIT_TO_SEND
				
			} //debugMode
			
		}
		else if ( millis() >= bellDebounceEndTime )
		{
			
			// Input is still low (otherwise we would have bailed out in the clause above)
			// and the debounce timer has now expired, so we have a good signal at least 
			// bellDebounceDelay ms long. Move the machine on to WAIT_TO_SEND state.
			bellMachineState = WAIT_TO_SEND;
			
			// Note that with SoftwareSerial, writes are blocking (there being no UART
			// write buffer), so each character written takes ~4ms to process. If
			// DEBUG_SHOW_DEBOUNCE is set, this will set an artificial floor of ~30ms on the
			// value of DEBUG_PULSE_TIMER output, as we don't grab the pulse end time until we
			// are in WAIT_TO_SEND. This is an issue only for debugging output.
			
			if ( debugMode && isDebugFlagSet( DEBUG_SHOW_DEBOUNCE ) ) {
				mySerial.print( bellStrikeChar);
				mySerial.print(F(" "));
				mySerial.print( bellCharSendTime );
				mySerial.println(F(" D" ));
			} //debugMode		 
			
		}
		
		// There is no other else here - if the input is still low and the timer
		// has not expired, we are still testing the signal quality so we just loop round.
		
		break; // bellMachineState == WAIT_FOR_DEBOUNCE

		// ---------------------------------------------------------------------------------------
		// -                                    WAIT_TO_SEND                                     -
		// ---------------------------------------------------------------------------------------      
	case WAIT_TO_SEND:
		
		// The bell is in "WAIT_TO_SEND" state.

		// We don't read the sensor pin at all when in this state. This debounces the input
		// and ignores spurious input. However there is a weakness here: If the delay is
		// insanely long (the protocol supports up to 0xFE (254) centiseconds (Abel allows
		// values up to 250cs (0xFA) or 2550ms to be input, Beltower allows values up to 2550ms
		// (in 10ms increments) (0xFF)), then there is the possibility that signals may be
		// lost. This has not been addressed here, as it means having more than one signal
		// outstanding for a single bell, and a queue of timers, and this behaviour is not
		// representative of the behaviour of real bells...
		
		// Check the timer - has it expired?
		if ( millis() >= bellCharSendTime ) {
			
			// Timer has expired, send the appropriate character to the interface. This uses
			// Serial.print because the MBI protocol specifies ASCII characters for bell strike
			// signals. (The serial command code uses Serial.write because it sends raw bytes.)
			
			// If any debug mode is set, suppress the normal output altogether. Debug code
			// supplies its own output as needed
			if ( ! debugMode ) {
				mySerial.print( bellStrikeChar );
			}
			
			// Turn the LED off again if appropriate
			digitalWrite( LED, LOW );
			
			// Set the machine state back to "WAIT_FOR_INPUT"
			bellMachineState = WAIT_FOR_INPUT;       
			
			// If we are in debug, send the timer values. This could be logged to a file for
			// later analysis.
			if ( debugMode ) {
				
				if ( isDebugFlagSet( DEBUG_PULSE_TIMER ) ) {
					
					mySerial.print( bellStrikeChar );
					mySerial.print(F(" "));
					mySerial.print( bellCharSendTime );
					mySerial.print(F(" S "));
					mySerial.print( pulseEndTime - pulseStartTime );
					mySerial.print(F(" "));
					mySerial.println(pulseTimeCount);
					
					// Reset the pulse counter, as we are going back to WAIT_FOR_INPUT
					pulseTimeCount = 0;
				}

			} //debugMode
			
		} //timer expired

		// There is no ELSE here - there is nothing to do if we are waiting to send and the
		// timer has not expired, other than do the debugging below, we just loop and check
		// again on the next loop.
		
		// If we are in debug mode then we DO read the pin, but only to check for the end of
		// sensor pulses during the "wait to send" period, and grab the time for debug output.
		
		if ( debugMode && isDebugFlagSet( DEBUG_PULSE_TIMER ) ) {
			
			int bellSensorValue;
			bellSensorValue = digitalRead(bellSensorPin);
			
			if ( bellSensorValue == HIGH && pulseTimeLastValue == LOW ) {
				// LOW to HIGH transition, a pulse just ended
				
				if ( pulseTimeCount == 0 ) {
					
					// This is the end of the first pulse (after a successful debounce), so note the
					// time.
					pulseEndTime = micros();
					pulseTimeCount++; // so we don't time any subsequent noisy pulses
					
				}
				else
				{
					
					// End of a spurious noise pulse after the first timed one, increment the
					// pulse counter.
					pulseTimeCount++;
					
				}
				
			} //bellSensorValue == HIGH && pulseTimeLastValue[i] == LOW
			
			// Update the last seen sensor value.
			pulseTimeLastValue = bellSensorValue;
			
		} //debugMode  
		
		break; //bellMachineState == WAIT_TO_SEND
		
	} //case

	// Is there any serial input pending? If there is, process it
	while ( mySerial.available() ) {
		handleSerial();
	}

} //loop()

/*
*********************************************************************************************
*                                 Function handleSerial()                                   *
*********************************************************************************************
*/

// serialEvent() is not available in SoftwareSerial.

void handleSerial( void ) {

	/*  
We have to handle command input from the simulator software via the serial interface.
We also have to handle the non-MBI CLI for the prototype interface.

The MBI protocol defines two distinct commands, plus the timers:
0xFD = Are you there?, correct response is 0xFD
0xFE = Send timer values, correct response is to send 12 bytes of timer values terminated 
		with 0xFF
0xNN = Anything else is the first of 12 bytes of hex timer values, terminated with 0xFF

The implementation by Abel 3.7.0c and Beltower 12.15 appears to be as follows:
0xFD - Not used by either application.
0xFE - Not used by Abel. 
		Beltower retrieves the timer values when the sensor dialogue is opened, or when
		the "Refresh from Box" button is clicked. Sometimes two 0xFEs are issued in
		quick succession after submitting timers in Beltower 2013.
0xNN - Abel sends the delay values on program start, and then when a value is changed.
		It does not appear to use the 0xFE command to retrieve the values for checking.
		Beltower does not send the values on startup, because the interface should store
		them. The values are only sent when the sensors dialogue is closed. They are then
		retrieved (0xFE) again (sometimes twice in succession) and checked against the values
		sent. What happens if the first byte of delay data is 0xFD or 0xFE is not specified.
		
If debugging is enabled when an MBI command is received, debugging is then turned off. If an
MBI command has been received, then most likely the simulator software has been started, and
if debug is enabled, then each bell signal generates debug output which causes a fire-up
in the simulator.
*/

	// We got here because there is stuff in the serial buffer waiting for us.
	// We'll stay here until we have processed everything there is before we revert to loop().  
	while ( mySerial.available() ) {

		// peek at the first byte in the buffer, without debuffering it, to see what's coming:
		byte peekChar = mySerial.peek(); // what is waiting?
		byte inChar; // to hold the bytes when they are read().

		// What have we got?
		switch ( peekChar ) {

		case 0xFD:    // FD = Are You There command?
			inChar = (byte)mySerial.read(); //debuffer the character
			mySerial.write(0xFD);
			// Disable debugging
			debugMode = false;
			// blink the LED to indicate we got a valid command
			blinkLED( LED, 1, 1 );   
			break;
			
		case 0xFE:    // FE = Send Delay Values
			inChar = (byte)mySerial.read(); //debuffer the character
			int i;
			for ( i = 0; i < 12; i++ ) {
				// Convert the ms unsigned long strike delay into a centisecond byte value.
				// The strike delay is not constrain()ed, as all possible byte values appear
				// to be valid there's not much point. Dividing a value and casting as a byte looks a
				// bit odd, but if all gone according to plan bellStrikeDelay[] will only ever contain
				// multiples of 10.
				mySerial.write( byte( bellStrikeDelay[i]/10 ) );
			}
			mySerial.write(0xFF); // protocol terminator
			// Disable debugging
			debugMode = false;
			// blink the LED to indicate we got a valid command
			blinkLED( LED, 1, 2 );   
			break;

		default:
			/*
	Any non-command data must first be assumed to be the delay timers, because the protocol
	does not include any leading command character to announce that delay data is a-coming.
	So we set Serial.setTimeout and Serial.readBytesUntil to read 13 bytes, or timeout, and
	then look, check that we got all 13 bytes and that the last one is 0xFF. If it is, it's
	delay data. What happens if the first byte of delay data is 0xFD/0xFE is not defined in
	the protocol.
	
	Note that setTimeout & readBytesUntil are part of the Stream class, not SoftwareSerial
	(or HardwareSerial), so they can still be used here as SoftwareSerial inherits from
	Stream, which is (a) handy, and (b) not documented.
	*/

			// We are expecting to read 13 bytes in total (bells 1-12 & 0xFF).
			byte tempDelayBuffer[13]; // Bells 1-12 & 0xFF. Zero indexed.
			byte bytesRead; // how many bytes did we read?
			mySerial.setTimeout(1000); // 1 sec
			
			// Serial.readBytesUntil will only write into a char[], so cast it to get it
			// to write into a byte[] array.
			bytesRead = mySerial.readBytesUntil( 0xFF, (char *)tempDelayBuffer, 13 ); 

			// Did we get enough bytes, and is the 13th byte 0xFF?
			if (bytesRead == 13 && tempDelayBuffer[12] == 0xFF) {
				// This looks like delay timer data, we are good to go, so update the active timer
				// values in bellStrikeDelay[], and save the values in the EEPROM. Convert the data
				// format to a long, and remember to convert centiseconds to milliseconds.

				int i;
				for ( i = 0; i < 12; i++ ) {
					if ( tempDelayBuffer[i] != 0 ) {
						// Don't overwrite timers with zero values, for better compatibility
						// with the Splitter Box.
						bellStrikeDelay[i] = long(tempDelayBuffer[i]) * 10;
						
						// Store the byte value in EEPROM locations 0-11
						// Check first that the value has actually changed, to reduce EEPROM write wear.
						// (Already checked above that we are not writing a zero)
						if ( EEPROM.read(i) != tempDelayBuffer[i] ) {
							EEPROM.write( i, tempDelayBuffer[i] );
						}							
					}		  
				}
				
				// Disable debugging
				debugMode = false;

				// blink the LED to indicate we got a valid command
				blinkLED( LED, 1, 3 );
				
			}
			else
			{
				/*
		Either we didn't read enough data for it to be delay values, or the last byte was
		not 0xFF. It might be a (non-MBI) CLI command, but we have read the data now so we
		can't peek any more.

		If we got here then we know we read at least one byte (because there was a byte to
		peek at, and we called readBytesUntil. We will look only at the first byte in the
		array, if someone managed to get two commands in before the 1000ms timeout, hard luck.
		Moral: Wait for the CLI to respond - there is no typeahead!
		*/

				// Hand the first byte over to handleCLI() to see if that can make sense of it...
				handleCLI( tempDelayBuffer[0] );
				
			} //else 
			
		} //switch peekchar
		
	}//serial available

}//serial event


