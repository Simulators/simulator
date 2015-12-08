/*
Splitter Box v1.4 Beta

Copyright 2015 Andrew J Instone-Cowie.

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

	1.1 : First beta version - breadboard prototype
	1.2 : Minor cosmetic fixes
		  Loop timings (8MHz internal oscillator)
		   - Passthrough Mode (idle) = 83us (range 82-95us)
		   - Shared Mode (idle) = 51us (range 50-63us)
		   - Config Mode (idle) = 87us (range 86-99us)
	1.3 : Prototype PCB Ver1 09/2015
	1.4 : Changed EEPROM handling to read-before-write to reduce EEPROM write wear, as per
		  ATmel recommended practice.
		  Amended recommended ATmega328P fuse settings.
		  Extend inputs and mapped characters to include ABCD (to support interfaces on 16)
		  and WXYZ (to support switches).
		  11,098 Bytes Flash, 431 Bytes SRAM.
	
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

// Uncomment the following line to use a pin as a CRO timing pin.
// This should be commented out in production code.
//#define USE_CRO

// Include the free memory library, freeMemory() is called by dumpdata().
#include <MemoryFree.h>

// Include attributes file for the terminal handling functions.
#include "Terminal_Functions.h"

#include <EEPROM.h>
// EEPROM locations 0 - 15 = target USB ports (as index 0-5)
// EEPROM locations 16 - 31 = mapped chars (as 0-9ET)

// Software version
const int majorVersion = 1;
const int minorVersion = 4;

// ------------------------------------------------------------------------------------------
//                                    USB Serial Ports
// ------------------------------------------------------------------------------------------

#include <SoftwareSerial.h>

// Define the USB serial ports as a pointer array. Avoid putting serials on MISO/MOSI/SCK
// RX, TX
SoftwareSerial *portUSB[] = {
	new SoftwareSerial(2, 3),
	new SoftwareSerial(4, 5),
	new SoftwareSerial(6, 7),
	new SoftwareSerial(8, 9),
	new SoftwareSerial(10, 14), //A0
	new SoftwareSerial(15, 16)  //A1, A2
};

// Set up an array of names for the USB ports for the CLI to use. '-' means disabled.
const char portNames[7]={'A','B','C','D','E','F','-'};

// Define the number of USB ports available, plus the "disabled" setting
const int numPorts=7; //number of SoftwareSerial ports (indexed 0 to numPorts -1) (ie 0-6)

// ------------------------------------------------------------------------------------------
//                                       Debugging
// ------------------------------------------------------------------------------------------

// Set up a Debug Mode flag - this always cleared on reset, so not held in EEPROM.
boolean debugMode = false;

// If USE_CRO was defined above, define a pin for CRO timing measurements.
#if defined USE_CRO
const int CROpin = 19; // 19 == A5
#endif

// ------------------------------------------------------------------------------------------
//                                    Mode Change Button
// ------------------------------------------------------------------------------------------

// Define pin and parameters for the mode change button. Any press between 
// buttonMinimumPressTime and buttonShortPressTime is a short press. Any press longer than
// buttonShortPressTime is a long press. Any press within buttonGuardTime of the last press
// is rejected. Note that the code detects the press (and its duration) when the button
// is released.
const int buttonPin = 11; //MOSI
boolean buttonPressPending = false;
unsigned long buttonPressStartTime;
unsigned long buttonPressEndTime = millis();
unsigned long buttonDuration; //msec
const unsigned long buttonGuardTime = 500; //msec
const unsigned long buttonMinimumPressTime = 50; //msec
const unsigned long buttonShortPressTime = 1000; //msec

// ------------------------------------------------------------------------------------------
//                                          Signal LED
// ------------------------------------------------------------------------------------------

// Define pins and parameters for the bi-colour 2-pin signal LED change button.
const int ledRed = 12; //MISO
const int ledGreen = 13; //SCK
boolean ledBlinkState = false;
unsigned long ledBlinkPeriod; //msec
unsigned long ledNextStateChangeTime; //msec

// ------------------------------------------------------------------------------------------
//                                        Operating Mode
// ------------------------------------------------------------------------------------------

// Define an integer to hold the current operating mode, and define the modes as text to
// make the code more readable.
int operatingMode;
#define MODE_PASSTHROUGH 0
#define MODE_SHARED 1
#define MODE_CONFIG 2

// ------------------------------------------------------------------------------------------
//                                        Target Mapping
// ------------------------------------------------------------------------------------------

// Define a struct to represnt the relationship between the incoming characters from the
// simulator interface (constants), the target USB port for each, and the outgoing character
// to which each incoming character should be mapped.
// Note that simulator interfaces do not currently send A-D, or W-Z (switch codes)
typedef struct {
	const char inputChar;		//0-9ETABCDWXYZ, received from the simulator interface
	int targetSerialPort;		//Store as 0-5 - map these to A-F for display. 6 = off
	char mappedChar;			//0-9ETABCDWXYZ, sent to the simulator PC(s).
} TargetSelector;

// Create the target map and set some default values. Some of these will be overwritten
// in setup() from EEPROM values.
TargetSelector Targets[20] = {
	{'1',0,'1'},
	{'2',1,'2'},
	{'3',2,'3'},
	{'4',3,'4'},
	{'5',4,'5'},
	{'6',5,'6'},
	{'7',6,'7'},
	{'8',6,'8'},
	{'9',6,'9'},
	{'0',6,'0'},
	{'E',6,'E'},
	{'T',6,'T'},
	{'A',6,'A'},
	{'B',6,'B'},
	{'C',6,'C'},
	{'D',6,'D'},
	{'W',6,'W'},
	{'X',6,'X'},
	{'Y',6,'Y'},
	{'Z',6,'Z'}
}; 

// Define an array of valid mapped characters for input checking.
//ABCD is standard nomenclature for 13-16, WXYZ for switches.
const char validMappedChars[] = "1234567890ETABCDWXYZ"; 

// Define the maximum number of targets, and an integer as an index value when
// searching the Targets[] array.
const int numTargets = 20;
int targetIndex;

// ------------------------------------------------------------------------------------------
//                                     CLI Terminal
// ------------------------------------------------------------------------------------------

// Define the terminal display configurations as text to make the code more readable.
// See termSetFor().
#define TERM_DEFAULT 0
#define TERM_HEADING 1
#define TERM_CLI 2
#define TERM_INPUT 3
#define TERM_CONFIRM 4
#define TERM_DEBUG 5

/*
*********************************************************************************************
*                                       Function setup()                                    *
*********************************************************************************************
*/

void setup() {
	
	// Generic setup loop counter
	int i; //

	// initialize mode change button pin.
	pinMode(buttonPin, INPUT_PULLUP);

	// initialize the LED pins as outputs.
	pinMode(ledRed, OUTPUT);
	pinMode(ledGreen, OUTPUT);

	// set LED pins appropriately (LEDs off).
	digitalWrite(ledRed, LOW);
	digitalWrite(ledGreen, LOW);
	
	// initialize the timing pin, if used.
	#ifdef USE_CRO
	pinMode( CROpin, OUTPUT );
	digitalWrite( CROpin, LOW );
	#endif

	// Set up the serial port and the USB ports
	Serial.begin(2400, SERIAL_8N1);
	//using numPorts-1 to take account of zero indexing and the last "port" being the
	//disabled setting.
	for ( i = 0; i < (numPorts - 1); i++ ) {
		portUSB[i]->begin(2400);
		// For compatibility with the MBI startup message - It's unclear whether any of the
		// simulators actually use this for anything.
		portUSB[i]->println( "<On.>" );
	}
	portUSB[0]->listen();

	// Load the Targets[] mapping data from EEPROM
	if ( ! loadFromEEPROM() ) {
		termSetFor( TERM_DEBUG );
		portUSB[0]->println(F("Invalid EEPROM data"));
		termSetFor( TERM_DEFAULT );
	}
	// Announce the software version on startup or reset
	blinkLED( ledGreen, majorVersion, minorVersion ); 
	
	// Set the initial operating mode and appropriate LED
	operatingMode = MODE_PASSTHROUGH;
	digitalWrite(ledRed, HIGH);
	
}

/*
*********************************************************************************************
*                                        Function loop()                                    *
*********************************************************************************************
*/

void loop() {

	// main loop start, waggle the CRO timing pin up. 
	// Timing pin overhead is ~8usec overall for both writes.
	// v1.0 code on Uno is ~92us per loop.
	#ifdef USE_CRO
	digitalWrite( CROpin, HIGH );
	#endif
	
	//Process the button and the LEDs
	processButton(scanButton());
	processLeds();
	
	switch ( operatingMode ) {
		
	case MODE_PASSTHROUGH:
		// read byes from USB A and copy them to the serial port as quickly as possible
		while( portUSB[0]->available() ) {
			Serial.write( portUSB[0]->read() );
		}
		break;

	case MODE_SHARED:
		//Currently nothing to do in shared mode - we never read the USB ports, and the
		//serial port is read in serialEvent() below.
		break;

	case MODE_CONFIG:
		// read input on USB A and pass each byte to the CLI handler. Any output in
		// MODE_CONFIG is generated by the handleCLI() function.
		while ( portUSB[0]->available() ) {
			// Read the byte and pass it over to handleCLI() for processing
			handleCLI( portUSB[0]->read() );
		}//serial available
		break;
	}
	
	// main loop complete, waggle the timing pin down.
	#ifdef USE_CRO
	digitalWrite( CROpin, LOW );
	#endif
		
}

/*
*********************************************************************************************
*                                     Function serialEvent()                                *
*********************************************************************************************
*/

void serialEvent() {

	/* Handle input from the interface */
	switch ( operatingMode ) {
		
	case MODE_PASSTHROUGH:
		// read byes from the serial port and copy them to USB A as quickly as possible
		while( Serial.available() ) {
			portUSB[0]->write( Serial.read() );
		}
		break;

	case MODE_SHARED:
		// read byes from the serial port, then identify which USB port they should be sent
		// to and as what mapped character.
		while( Serial.available() ) {
			byte readChar = Serial.read();
			
			//find the Targets[] index position (i.e. the destination USB port) for this
			//incoming character. We should only get 1-90ET from the upstream interface.
			targetIndex = -1;
			int i;
			
			for ( i = 0; i < 12; i++) {
				if (readChar == Targets[i].inputChar) {
					targetIndex = i;
					//don't do a break here, scan the whole array every time so the loop
					//time is always consistent.
				}
			}

			//if the port number returned is a sane value... (-1 to ignore the disabled port.
			//so 0-5 are valid, 6 is disabled)
			if( Targets[targetIndex].targetSerialPort < (numPorts - 1) ) {
				//...write the mapped character for the this incoming character to the
				//incoming character's target USB port.
				portUSB[Targets[targetIndex].targetSerialPort]->write( Targets[targetIndex].mappedChar );
			}

		} //while
		
		break;

	case MODE_CONFIG:
		//do nothing with the hardware serial interface
		break;

	} //switch operatingmode

}

