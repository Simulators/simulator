/*
Simulator Interface v2.5

Copyright 2014-2018 Andrew J Instone-Cowie.

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

Tested against Abel 3.10.0, Beltower 12.35 (2017), Virtual Belfry 3.5.

	1.2 : First production release
	1.3 : Changes to signal LED blink to support Beltower 2013 (12.15)
	1.4 : Additional CLI command Z sets volatile timers to 10msec.
		Additional CLI command # cycles the number of Active Channels
		Additional CLI command S saves Active Channels number to EEPROM
		Rewrote CLI handler to avoid collisions with delay data values.
		Additional CLI commands for debug output markers
	1.5 : Implement MemoryFree library and add function call to dumpdata()
		Reduce SRAM footprint by moving string literals to PROGMEM (F() macro)
		Rework Z debug option to set default 500ms volatile timers
		Add debug mode pulse length measurement in microseconds & pulse counting
		Loop time with CRO pin enabled is 120us, 130us with debug enabled.
		** 1st Cathedral Release - 25/05/2014 **
		e: Reorganise code into multiple source files. Not released.
	1.6 : Change to tri-state machine to improve debounce behaviour
		Implement debug level setting into the CLI (enhanced D option)
		Implement configurable debounce timer (option U)
		Rework S option to also save debounce timer to EEPROM
		Make CLI display debug-related options dynamically
		Implement multi-level debugging (ranges/exact values)
		Added red LED trigger on all bells as debug option for in-belfry testing
		Added rudimentary debug levels CLI help text (option L)
		Improved code to go back to WAIT_FOR_INPUT if signal ceases prematurely ("misfire")
	1.7 : Speedometer mode added
	1.8 : Terminal cursor control added.
		Reworked and improved CLI to use VTSerial.
		Speedometer configuration options added, saved in EEPROM.
		Loop time with CRO pin enabled 140us Simulator mode/90us Speedometer mode.
		Power supply: 2.5mVpp noise on 3.3V line, 10mVpp on 5V line.
		** 2nd Cathedral Release - 20/07/2014 **
	1.9 : Backport maxNumChannels from the one-bell version.
	2.1 : Update pin allocations for Mk2 (stripboard) hardware.
		Provide support for both versions of hardware through a #define
		Remove speedometer mode and supporting code.
		Disable debug mode if we receive an MBI command (i.e. the simulator started up)
		Loop time with CRO pin enabled 270us on Mk2 hardware (8MHz internal oscillator)
		Code released under GPL v3
		** 3rd Cathedral Release - 10/01/2015 **
	2.2 : Make serial port speed configurable 2400-9600bps for debugging (option P)
		Make debug messages much less verbose, to mitigate serial port buffer issues
		Framework for per-channel debugging and complete reworking of the debug code (I
		never liked the original implementation).
		Tested against Beltower 2015 (12.29) & Virtual Belfry 3.1b
		** 4th Cathedral Release (on Rev B PCB) - 23/05/2015 **
	2.3 : Add simple testmode to use interface as datasource for testing. Initially for
		SplitterBox testing.
		Re-indent all the code with TestFX.
		Tested against Abel 3.9.1.
		Fixed test mode bug (re-using loop counters and thus breaking open handstroke leads).
		Tested against Virtual Belfry 3.2 (no code changes).
		Changed EEPROM handling to read-before-write to reduce EEPROM write wear, as per
		ATmel recommended practice.
		Amended recommended ATmega328P fuse settings.
		12,708 Bytes Flash, 618 Bytes SRAM.
	2.4 : Add ability to disable individual sensors e.g. to bypass a faulty sensor, by means
		of a new state machine state SENSOR_DISABLED (option E).
		Update much of the EEPROM handling code, added locations to make enabled sensors and
		debug masks persistent.
		Code cleanup, remove a lot of hard coded constants. Some values remain fixed at 12
		because of the hardware config or the MBI protocol spec.
		Changed the way the # option works, to give a better CLI on interfaces with <12
		channels equipped.
		Simplified the CLI for setting simulator types (as option Q), and renamed the 
		debounce timer command from U to B. Updated LED signal codes.
		Tested against Virtual Belfry 3.3 (no code changes).
		15,188 Bytes Flash, 708 Bytes SRAM.
		** 5th Cathedral Release (on Rev B PCB) - 10/02/2016 **
	2.5 : Switched #ifdefs to use ARDUINO_{build.board} values for auto-selection.
		No functional changes.
		Final planned release of firmware for the Type 1 simulator.
		
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
*/

// Simulator Interface Hardware
//  - Mk1 hardware is a based on a full Uno R3, plus shields.
//  - Mk2 hardware is the stripboard/PCB ATmega328p version.
//  - The IDE sets up a #define ARDUINO_AVR_{BUILD.BOARD} from boards.txt
//    so there is no need to uncomment one of  the following lines.
//#define ARDUINO_AVR_SIMULATORMK1
//#define ARDUINO_AVR_SIMULATOR

// Uncomment the following line to use a pin as a CRO timing pin.
// This should be commented out in production code.
//#define USE_CRO

// Include the free memory library, freeMemory() is called by dumpdata().
#include <MemoryFree.h>

// Include the VTSerial library for VT100-style input functions.
#include <VTSerial.h>

// Initialise the VTSerial library.
VTSerial vtSerial;

// Include attributes file for the terminal handling functions.
#include "Terminal_Functions.h"

// Bell timers and other non-volatile data are stored in EEPROM:
// Locations 0-11  : Bells 1-12 Delay Timers (in cs)
// Locations 12-15 : Reserved for future Bells 13-16 Delay Timers
// Location  16    : Accidental Status (#,b) - Not supported yet
// Location  17    : Simulator Type (A,B,R,V,X)
// Location  18    : Number of channels (bell pins) active & to be scanned
// Location  19    : Debounce Timer (in ms)
// Location  20    : Serial port speed (as an index into serialSpeeds[])
// Location  21    : enabledSensorMask (lo byte) //TO DO
// Location  22    : enabledSensorMask (hi byte) //TO DO
// Location  23    : debugBellMask (lo byte) //TO DO
// Location  24    : debugBellMask (hi byte) //TO DO

#include <EEPROM.h>

// Software version
const int majorVersion = 2;
const int minorVersion = 5;

// -------------------------------------------------------------------------------------------
//                                    Core Simulator
// -------------------------------------------------------------------------------------------

// Define the maximum number of channels that can be set on the hardware. For the one-bell
// interface this is 1. For the 12-bell version this will be 12.
const int maxNumChannels = 12; // 1 for the one-bell, 12 for the 12-bell
// CHANGE THIS VALUE BEFORE UPLOADING TO AN INTERFACE WITH <12 CHANNELS EQUIPPED IN HW
// THE MAXIMUM VALUE, IMPOSED BY THE HARDWARE, IS 12.

// Define the number of input channels to scan (always starting at 0, held in EEPROM).
// Not scanning unused channels avoids issues with spurious signals being detected on
// floating inputs (even with INPUT_PULLPUP). Most data structures, etc are set up for this
// number of bells, except those where the simulators send and expect 12-bell values.
int numChannels; // initialised from EEPROM in setup

// Define bell sensor input pins, avoid 13 because of the LED (sensors are normally HIGH,
// the onboard LED will tend to pull it low), and 12 for the additional yellow signal LED
#ifdef ARDUINO_AVR_SIMULATORMK1
const int bellSensorPin[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 14, 15 }; //14-15 aka A0-A1
#endif

#ifdef ARDUINO_AVR_SIMULATOR
const int bellSensorPin[] = { 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 }; //14-19 aka A0-A5
#endif

// Set up an array of the characters sent on the serial port to the simulator software, as
// defined in the MBI interface specification. These are ASCII characters. This version
// does not support the W/X/Y/Z switch characters, and Beltower cannot use those characters.
const char bellStrikeChar[] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'E', 'T' };

// Set up an array to store the last observed sensor status, so we can detect transitions
// in input state. This is important to avoid duplicated sensor signals. 
int bellSensorLastValue[maxNumChannels]; //initialise these in setup, and set them LOW (see below)

// Set up an array of strike signal timer delays, one per bell. The data type is unsigned
// long, because these values will be added to the output of millis(). Note that this code
// does everything in millisenconds (as does Beltower), although the MBI interface and Abel
// define values in centiseconds. Hard coded to 12 because the MBI protocol always expects 12.
unsigned long bellStrikeDelay[12]; // initialise these in setup()

// Set up an array to hold the actual time of the next character is due to be sent, one per
// bell. The data type is unsigned long, because these values will be the sum of
// bellStrikeDelay and the output of millis().
unsigned long bellCharSendTime[maxNumChannels]; // initialise these in setup()

// Set up an array of the permitted serial port speeds. Note that Abel and Beltower
// (and the MBI protocol specification) REQUIRE 2400 bps. Other speeds may be useful only
// for debugging where the text output can overrun the serial transmit buffer and cause
// timing issues. Also declare an int to hold the indexed value, and a sane default.
unsigned long serialSpeeds[] = { 2400, 4800, 9600 };
int serialSpeed = 0; // index into serialSpeeds[], not the actual bps, loaded from EEPROM 
const long defaultSerialSpeed = 0; // 2400 - required by the simulators

// Set up an Enabled Sensor Mask variable as a 16 bit unsigned word. The first twelve bits
// (0-11) correspond to the sensor being enabled on that channel (1=true=on, 0=false=off).
// LSB = Channel 0 (usually treble).
word enabledSensorMask; // initialised from EEPROM in setup. See option E.

// Set up a char to hold the current simulator type (Abel, Beltower, etc
char simulatorType; // initialised from EEPROM in setup. See option E.

// Define a struct to list the available simulator package types and a one character
// abbreviation for input and EEPROM storage.
typedef struct {
	const char simOneChar;		//e.g. ABRVX
	String simLongName;			//e.g. Abel, Beltower, etc
} simName;

// Define the maximum number of simulator names in the array below.
const int numSimulatorNames = 5;

// Define an array of valid simulator names for input checking (e.g. Abel/Beltower/Ringleader
// /Virtual Belfry/Generic. See also printSimulatorTypeName() & checkValidSimulatorType();
simName simulatorNames[numSimulatorNames] = {
	{'A',"Abel"},
	{'B',"Beltower"},
	{'R',"Ringleader"},
	{'V',"Virtual Belfry"},
	{'X',"Generic"}
}; 

// -------------------------------------------------------------------------------------------
//                                   Sensor Debounce
// -------------------------------------------------------------------------------------------

// Set up an array to hold the time that the debounce timer will expire, one per bell. The
// data type is unsigned long, because these values will be the sum of bellDebounceDelay and
// the output of millis().
unsigned long bellDebounceEndTime[maxNumChannels]; // initialise these in setup()

// Set up a variable to hold the debounce delay time, in milliseconds.
unsigned long bellDebounceDelay ; // initialised from EEPROM in setup. See option U.

// Define the maximum permitted debounce timer value. Current value is stored in EEPROM, so
// must be <=255 ms. This value is used when setting the timer via the U CLI option.
// The minDebounceTimer will always be 1ms, so no definition for it.
const unsigned long maxDebounceDelay = 20; //ms

// Define the default debounce timer value in case the EEPROM is not yet set sensibly.
const unsigned long defaultDebounceDelay = 4; //ms

// -------------------------------------------------------------------------------------------
//                                    State Machines
// -------------------------------------------------------------------------------------------

// Set up an array of integers to indicate whether each per-bell state machine is in the
// program state "WAIT_FOR_INPUT" (0), "WAIT_FOR_DEBOUNCE" (1), "WAIT_TO_SEND"(2), 
// "TEST_MODE" (3) or "SENSOR_DISABLED" (4)
int bellMachineState[maxNumChannels]; // initialise these in setup()

// Define the possible machine states as text to make the code more readable.
#define WAIT_FOR_INPUT 0
#define WAIT_FOR_DEBOUNCE 1
#define WAIT_TO_SEND 2
#define TEST_MODE 3
#define SENSOR_DISABLED 4

// -------------------------------------------------------------------------------------------
//                                      Debugging
// -------------------------------------------------------------------------------------------
// Set up a Debug Mode flag - this always cleared on reset, so not held in EEPROM.
boolean debugMode = false;

// Set up a Debug Mask variable as a 16 bit unsigned word. The first twelve bits (0-11)
// correspond to debugging being enabled on that channel (1=true=on, 0=false=off). This
// allows per-channel debugging to be configured. LSB = Channel 0 (usually treble).
word debugBellMask; // initialised from EEPROM in setup. See option M.

// Set up a Debug Flags Mask variable. The first 4 bits (0-3) correspond to debugging
// facilities in the code (1=on, 0=off). This allows each facility to turned on and off
// independently. These can be changed on the fly with the D option.
word debugFlagsMask = 1; //debug starts with DEBUG_PULSE_TIMER flag set by default

// Define the maximum configured number of flags. This value will depend on the flags
// actually implemented in the code. Currently there are 4 flags, as #defined below.
// If you add a debug level, increment this constant so that the CLI works.
const int maxDebugFlags = 4;

// Define the debug flags as text to make the code more readable
#define DEBUG_PULSE_TIMER 1		//bit 0
#define DEBUG_SHOW_MISFIRES 2	//bit 1
#define DEBUG_SHOW_DEBOUNCE 4	//bit 2
#define DEBUG_SHOW_LED 8		//bit 3
// (See also the function printDebugFlagName(), seeing as F() is not available globally)

// Define the default debug deplay timer. See option Z.
const unsigned long defaultDelayTimer = 500;

// -------------------------------------------------------------------------------------------
//                                   Debug Pulse Timing
// -------------------------------------------------------------------------------------------

// These variables are used for debug mode pulse length timing and counting only. There is
// no need to do pulse timing during normal operation.

// Set up two arrays to hold the actual start and end times of the sensor pulse, one per bell.
// The data type is unsigned long, because these values will be the output of micros(). These
// are used in debug mode only to calculate the length of the (first) sensor pulse.
unsigned long pulseStartTime[maxNumChannels]; // initialise these in setup()
unsigned long pulseEndTime[maxNumChannels];   // initialise these in setup()

// Set up an array to store the last observed sensor status, so we can detect transitions.
// This array is used for debug mode pulse timing only, because updating the real
// bellSensorLastValue[] would lose the debounce effect for real simulator operation (which
// has to carry on regardless).
int pulseTimeLastValue[maxNumChannels]; //initialise these in setup, and set them LOW (see below)

// Set up an array of integers to count the pulses (to show how noisy a sensor is). We do this
// by counting spurious pulse *ends* (LOW to HIGH) when we aren't expecting them, and to make
// sure we timed only the first pulse.
int pulseTimeCount[maxNumChannels]; //initialise in setup, and set to zero

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

// -------------------------------------------------------------------------------------------
//                                     Test Mode
// -------------------------------------------------------------------------------------------

// These variables are used for test mode. None of these things are configurable on the fly.

// Define the delay before test mode kicks in after selecting the "T" CLI option
const int testStartDelay = 20; //seconds

// Define the number of bells used in test mode
const int testBells = 12;

// Define the inter-bell interval used in test mode. 200ms equates to a 12-bell peal speed
// of 3h30m with an open handstroke lead.
const int testInterval = 200; //msec

// -------------------------------------------------------------------------------------------
//                                     LEDs & Timing
// -------------------------------------------------------------------------------------------

// Miscellaneous LEDs and optionally a CRO timing pin
#ifdef ARDUINO_AVR_SIMULATORMK1
const int LEDred = 13;
const int LEDyellow = 12;
#endif

#ifdef ARDUINO_AVR_SIMULATOR
const int LEDred = 7;
const int LEDyellow = 6;
#endif

// If USE_CRO was defined above, define a pin for CRO timing measurements.
#if defined USE_CRO && defined ARDUINO_AVR_SIMULATORMK1
const int CROpin = 19; // 19 == A5
#endif

#if defined USE_CRO && defined ARDUINO_AVR_SIMULATOR
const int CROpin = 5; 
#endif

// Overall this leaves as spares the following pins:
// - Mk1: A2 (16), A3 (17) & A4 (18)
// - Mk2: 2, 3, 4

/*
*********************************************************************************************
*                                   Function setup()                                        *
*********************************************************************************************
*/

// the setup routine runs once on powerup or reset:
void setup() {   

	// initialize the LED pins as outputs.
	pinMode( LEDred, OUTPUT );
	pinMode( LEDyellow, OUTPUT );

	// set LED pins appropriately (turn the LEDs off).
	digitalWrite( LEDred, LOW );
	digitalWrite( LEDyellow, LOW );

	// initialize the timing pin, if used.
#ifdef USE_CRO
	pinMode( CROpin, OUTPUT );
	digitalWrite( CROpin, LOW );
#endif

	// Load default values from EEPROM
	loadFromEEPROM();

	// generic setup loop counter
	int i;

	// setup data structures for as many entries supported by the hardware, maxNumChannels,
	// even though we are looking at numChannels in operation.
	for ( i = 0; i < maxNumChannels; i++ ) {

		// initialize the bell sensor digital input pins with the pullup resistors active.
		// The photoheads pull the pin LOW when there is a signal.
		pinMode( bellSensorPin[i], INPUT_PULLUP );

		// initialize the array holding the last sensor status for each bell. Set these initially
		// to be LOW, so that the very first pass of loop() doesn't find a spurious transition
		// if the bells are down (and thus signalling continuously) and result in a fire-up
		// on startup.
		bellSensorLastValue[i] = LOW;
		
		// initialize the strike send time values. These values should never get used, because
		// they will be overwritten when the actual time is calculated as the state machine enters
		// "WAIT_TO_SEND", but there is no harm in initialising it here just in case.
		bellCharSendTime[i] = millis();

		// initialize the debounce timer end time values. These values should never get used,
		// because they will be overwritten when the actual time is calculated as the state
		// machine leaves "WAIT_FOR_INPUT", but there is no harm in initialising it here just in case.
		bellDebounceEndTime[i] = millis();

		// initialise the variables used for debug mode pulse length measurements    
		pulseStartTime[i] = micros();
		pulseEndTime[i] = micros();
		pulseTimeLastValue[i] = HIGH;
		pulseTimeCount[i] = 0;
		
	}
	
	// Set the enable state for all sensors. This initializes the state machine flag for each
	// bell. All enabled sensors start by waiting for input. Setting this to "WAIT_TO_SEND"
	// would result in an immediate timer expiry for every bell on the first pass of loop(),
	// and another one row fire-up.
	enableSensors( enabledSensorMask, numChannels );
	
	// Set up the serial port. The MBI interface spec uses 2400 8N1, another speed may have
	// been set for debugging purposes.
	Serial.begin( serialSpeeds[serialSpeed], SERIAL_8N1 );
	termInit();
	// For compatibility with the MBI startup message - It's unclear whether any of the
	// simulators use this for anything.
	Serial.println(F("<On.>"));

	// Announce the software version on startup or reset
	blinkLED( LEDyellow, majorVersion, minorVersion ); 

	// If the serial port speed is not explicitly set to 2400 in the EEPROM, turn the yellow
	// LED on and leave it on as a warning (until the next command changes the LED state)
	if ( serialSpeed != 0 ) {
		delay(100);
		digitalWrite( LEDyellow, HIGH );
	}

}

/*
*********************************************************************************************
*                                     Function loop()                                       *
*********************************************************************************************
*/

// once setup has completed, the loop routine runs over and over again forever:
void loop() {

	// main loop start, waggle the CRO timing pin up. 
	// Timing pin overhead is ~8usec overall for both writes.
	// v1.0 code on Uno is ~92us per loop.
#ifdef USE_CRO
	digitalWrite( CROpin, HIGH );
#endif

	// main loop counter
	int i;
	// test mode counters
	int j, k;

	// loop around all the active channels and look at the state of the state machine for each
	for ( i = 0; i < numChannels; i++ ) {

		// Variable to store the value read from the pin
		int bellSensorValue;
		
		switch ( bellMachineState[i] ) {

			// ---------------------------------------------------------------------------------------
			// -                                 WAIT_FOR_INPUT                                      -
			// ---------------------------------------------------------------------------------------
		case WAIT_FOR_INPUT:

			// This bell is in "WAIT_FOR_INPUT" state
			// Read the value from the sensor pin
			bellSensorValue = digitalRead( bellSensorPin[i] );
			
			if ( bellSensorValue == LOW && bellSensorLastValue[i] == HIGH ) {
				
				// This is a HIGH to LOW transition since we last looked, so we have the start of a
				// sensor pulse. Note the current time in a scratch variable (to avoid calling
				// millis() twice)
				unsigned long timeNow;
				timeNow = millis();
				
				// Set the time that the character should be sent to the simulator to now + the delay
				// timer. (Do this calculation here so we only have to do the comparison in following
				// loops, not the addition)
				bellCharSendTime[i] = timeNow + bellStrikeDelay[i];

				// Set the time that the debounce timer will expire to to now + the debounce timer.
				// (Do this calculation here so we only have to do the comparison in following loops,
				// not the addition)
				bellDebounceEndTime[i] = timeNow + bellDebounceDelay;
				
				// Set the last observed value to the current state of the sensor, which is LOW.
				// For an explanation of why we do this, see below.
				bellSensorLastValue[i] = bellSensorValue;

				// Use the Red LED to signal strikes on bell 1 (MBI always starts at bell 1, even for
				// <12 bells). Turn on when the pulse is received, off when character is sent. Array
				// is zero indexed. (The LED may be used in other debug options, so hand this off to
				// a function.)
				strikeLED( i, true );
				
				// Move the machine state on to "WAIT_FOR_DEBOUNCE"
				bellMachineState[i] = WAIT_FOR_DEBOUNCE;
				
				// If we are in debug mode, grab the pulse start time and reset the counter.
				// Both the pulse timer and the misfire detection require pulse timing to be done
				if ( debugThisBell( i ) && isDebugFlagSet( DEBUG_PULSE_TIMER | DEBUG_SHOW_MISFIRES ) ) {
					
					pulseStartTime[i] = micros();
					
					// Avoid overflows giving a silly number if we get to a debug print before the end
					// of the first pulse! A pulse length of 0 means the pulse has not ended yet.
					pulseEndTime[i] = pulseStartTime[i];
					pulseTimeLastValue[i] = bellSensorValue;
					pulseTimeCount[i] = 0; //incremented at the END of the pulse
					
					// We only run this code at the start of a valid pulse. The counter is used
					// to ensure that we only measure the duration of the first pulse in a potential
					// string of noisy input pulses (which are ignored by the main interface code).
					
				} //debugThisBell
				
			}
			else // this is not the start of a pulse
			{

				// Set the last observed value to the current state of the sensor, which may
				// (still) be LOW or (by now) HIGH.
				bellSensorLastValue[i] = bellSensorValue;
				
				// We stay in the "WAIT_FOR_INPUT" state. We may have come back here and found the
				// sensor still LOW after sending the character to the simulator if the delay is
				// very short and the pulse very long, hence the transition detection.
				
			} //bellSensorValue
			
			break; //bellMachineState == WAIT_FOR_INPUT

			// ---------------------------------------------------------------------------------------
			// -                                WAIT_FOR_DEBOUNCE                                    -
			// ---------------------------------------------------------------------------------------      
		case WAIT_FOR_DEBOUNCE:
			
			// This bell is in "WAIT_FOR_DEBOUNCE" state.
			// Check whether the signal has ended too soon (and so is considered noise).
			
			// Read the value from the sensor pin
			bellSensorValue = digitalRead( bellSensorPin[i] );
			
			if ( bellSensorValue == HIGH ) {
				
				// Input has gone high again, pulse was too short, so this is a misfire.
				
				// Turn the LED off again if it was on
				strikeLED( i, false );
				
				// Set the machine state back to "WAIT_FOR_INPUT"
				bellMachineState[i] = WAIT_FOR_INPUT;
				
				// If we are in a debug mode, report the misfire and pulse data.
				if ( debugThisBell( i ) && isDebugFlagSet( DEBUG_SHOW_MISFIRES ) ) {
					
					// Grab the time of the end of the pulse (approximately) 
					pulseEndTime[i] = micros();
					
					Serial.print( bellStrikeChar[i] );
					Serial.print(F(" "));
					Serial.print( bellCharSendTime[i] );
					Serial.print(F(" M " ));
					Serial.println( pulseEndTime[i] - pulseStartTime[i] );
					
					// There is no need to set the pulse counter here - misfires are by
					// definition pulse #1 of 1. There may however be noise pulses *after*
					// the first one which is longer than the debounce timer, so we will
					// update the pulse counter when in WAIT_TO_SEND
					
				} //debugThisBell
				
			}
			else if ( millis() >= bellDebounceEndTime[i] )
			{
				
				// Input is still low (otherwise we would have bailed out in the clause above)
				// and the debounce timer has now expired, so we have a good signal at least 
				// bellDebounceDelay ms long. Move the machine on to WAIT_TO_SEND state.
				bellMachineState[i] = WAIT_TO_SEND;
				
				if ( debugThisBell( i ) && isDebugFlagSet( DEBUG_SHOW_DEBOUNCE ) ) {
					Serial.print( bellStrikeChar[i]);
					Serial.print(F(" "));
					Serial.print( bellCharSendTime[i] );
					Serial.println(F(" D" ));
				} //debugThisBell		 
				
			}
			
			// There is no other else here - if the input  is still low and the timer
			// has not expired, we are still testing the signal quality so we just loop round.
			
			break; // bellMachineState == WAIT_FOR_DEBOUNCE

			// ---------------------------------------------------------------------------------------
			// -                                    WAIT_TO_SEND                                     -
			// ---------------------------------------------------------------------------------------      
		case WAIT_TO_SEND:
			
			// This bell is in "WAIT_TO_SEND" state.

			// We don't read the sensor pin at all when in this state. This debounces the input
			// and ignores spurious input. However there is a weakness here: If the delay is
			// insanely long (the protocol supports up to 0xFE (254) centiseconds (Abel allows
			// values up to 250cs (0xFA) or 2550ms to be input, Beltower allows values up to 2550ms
			// (in 10ms increments) (0xFF)), then there is the possibility that signals may be
			// lost. This has not been addressed here, as it means having more than one signal
			// outstanding for a single bell, and a queue of timers, and this behaviour is not
			// representative of the behaviour of real bells...
			
			// Check the timer - has it expired?
			if ( millis() >= bellCharSendTime[i] ) {
				
				// Timer has expired, send the appropriate character to the interface. This uses
				// Serial.print because the MBI protocol specifies ASCII characters for bell strike
				// signals. (The serial command code uses Serial.write because it sends raw bytes.)
				
				// If any debug mode is set, suppress the normal output altogether. Debug code
				// supplies its own output as needed
				if ( ! debugMode ) {
					Serial.print( bellStrikeChar[i] );
				}
				
				// Turn the LED off again if appropriate
				strikeLED( i, false );
				
				// Set the machine state back to "WAIT_FOR_INPUT"
				bellMachineState[i] = WAIT_FOR_INPUT;       
				
				// If we are in debug, send the timer values. This could be logged to a file for
				// later analysis.
				if ( debugThisBell( i ) ) {
					
					if ( isDebugFlagSet( DEBUG_PULSE_TIMER ) ) {
						
						Serial.print( bellStrikeChar[i] );
						Serial.print(F(" "));
						Serial.print( bellCharSendTime[i] );
						Serial.print(F(" S "));
						Serial.print( pulseEndTime[i] - pulseStartTime[i] );
						Serial.print(F(" "));
						Serial.println(pulseTimeCount[i]);
						
						// Reset the pulse counter, as we are going back to WAIT_FOR_INPUT
						pulseTimeCount[i] = 0;
					}
					else if ( isDebugFlagSet( DEBUG_SHOW_LED ) ) {
						Serial.print( bellStrikeChar[i] );
					}

				} //debugThisBell
				
			} //timer expired

			// There is no ELSE here - there is nothing to do if we are waiting to send and the
			// timer has not expired, other than do the debugging below, we just loop and check
			// again on the next loop.
			
			// If we are in debug mode then we DO read the pin, but only to check for the end of
			// sensor pulses during the "wait to send" period, and grab the time for debug output.
			
			if ( debugThisBell( i ) && isDebugFlagSet( DEBUG_PULSE_TIMER ) ) {
				
				int bellSensorValue;
				bellSensorValue = digitalRead(bellSensorPin[i]);
				
				if ( bellSensorValue == HIGH && pulseTimeLastValue[i] == LOW ) {
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
				pulseTimeLastValue[i] = bellSensorValue;
				
			} //debugThisBell  
			
			break; //bellMachineState == WAIT_TO_SEND

			// ---------------------------------------------------------------------------------------
			// -                                      TEST_MODE                                      -
			// ---------------------------------------------------------------------------------------      
		case TEST_MODE:
			
			// This bell is in "TEST_MODE" state.
			
			// Test mode works like this. The "T" CLI command puts all the channels into TEST_MODE
			// and waits for testStartDelay seconds. For all channels other than 0, test mode does
			// nothing and the code skips past. For channel 0, the first time we fall into the
			// function below, the interface start to generate rounds at the defined pace.
			// There is then no escape other than an interface reset.
			
			if( i == 0 ) {
				digitalWrite( LEDred, HIGH);
				digitalWrite( LEDyellow, HIGH);
				//ring rounds forever
				while(true) {
					// twice - handstroke and backstroke
					for ( j = 0; j < 2; j++ ) {
						for ( k = 0; k < testBells; k++ ) {
							Serial.print( bellStrikeChar[k] );
							delay(testInterval);
						}
					}
					// open handstroke lead
					delay(testInterval);
					// flash both LEDs slowly
					digitalWrite( LEDred, !digitalRead( LEDred ));
					digitalWrite( LEDyellow, !digitalRead( LEDyellow)); 
				}
			} // no else, only do this for channel 0
			
			break; //bellMachineState == TEST_MODE

			// ---------------------------------------------------------------------------------------
			// -                                      SENSOR_DISABLED                                -
			// ---------------------------------------------------------------------------------------      
		case SENSOR_DISABLED:
			
			// This bell is in "SENSOR_DISABLED" state.
			
			// If the sensor is disabled, simply ignore it. Do nothing other than keep the
			// yellow LED on. SENSOR_DISABLED mode toggled with WAIT_FOR_INPUT in CLI
			// option E (for Enable).
			digitalWrite( LEDyellow, HIGH);
			
			break; //bellMachineState == SENSOR_DISABLED

		} //case
		
	} //for numChannels

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

void serialEvent() {

	/*  
We have to handle command input from the simulator software via the serial interface.
We also have to handle the non-MBI CLI for the prototype Arduino interface.

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
	while ( Serial.available() ) {

		// peek at the first byte in the buffer, without debuffering it, to see what's coming:
		byte peekChar = Serial.peek(); // what is waiting?
		byte inChar; // to hold the bytes when they are read().

		// What have we got?
		switch ( peekChar ) {

		case 0xFD:    // FD = Are You There command?
			inChar = (byte)Serial.read(); //debuffer the character
			Serial.write(0xFD);
			// Disable debugging
			debugMode = false;
			// blink the LED to indicate we got a valid command
			blinkLED( LEDyellow, 1, 1 );   
			break;
			
		case 0xFE:    // FE = Send Delay Values
			inChar = (byte)Serial.read(); //debuffer the character
			int i;
			for ( i = 0; i < 12; i++ ) {
				// Convert the ms unsigned long strike delay into a centisecond byte value.
				// The strike delay is not constrain()ed, as all possible byte values appear
				// to be valid there's not much point. Dividing a value and casting as a byte looks a
				// bit odd, but if all gone according to plan bellStrikeDelay[] will only ever contain
				// multiples of 10.
				Serial.write( byte( bellStrikeDelay[i]/10 ) );
			}
			Serial.write(0xFF); // protocol terminator
			// Disable debugging
			debugMode = false;
			// blink the LED to indicate we got a valid command
			blinkLED( LEDyellow, 1, 2 );   
			break;

		default:
			/*
	Any non-command data must first be assumed to be the delay timers, because the protocol
	does not include any leading command character to announce that delay data is a-coming.
	So we set Serial.setTimeout and Serial.readBytesUntil to read 13 bytes, or timeout, and
	then look, check that we got all 13 bytes and that the last one is 0xFF. If it is, it's
	delay data. What happens if the first byte of delay data is 0xFD/0xFE is not defined in
	the protocol.
	*/

			// We are expecting to read 13 bytes in total (bells 1-12 & 0xFF).
			byte tempDelayBuffer[13]; // Bells 1-12 & 0xFF. Zero indexed.
			byte bytesRead; // how many bytes did we read?
			Serial.setTimeout(1000); // 1 sec
			
			// Serial.readBytesUntil will only write into a char[], so cast it to get it
			// to write into a byte[] array.
			bytesRead = Serial.readBytesUntil( 0xFF, (char *)tempDelayBuffer, 13 ); 

			// Did we get enough bytes, and is the 13th byte 0xFF?
			// THIS SHOULD BE AN EEPROM FUNCTION
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
				blinkLED( LEDyellow, 1, 3 );
				
			}
			else
			{
				/*
		Either we didn't read enough data for it to be delay values, or the last byte was
		not 0xFF. It might be a (non-MBI) CLI command, but we have read the data now so we
		can't peek any more.

		If we got here then we know we read at least one byte (because there was a byte to
		peek at, and we called readBytesUntil(). We will look only at the first byte in the
		array, if someone managed to get two commands in before the 1000ms timeout, hard luck.
		Moral: Wait for the CLI to respond - there is no typeahead!
		*/

				// Hand the first byte over to handleCLI() to see if that can make sense of it...
				handleCLI( tempDelayBuffer[0] );
				
			} //else 
			
		} //switch peekchar
		
	}//serial available

}//serial event


