/*
One Bell Simulator Interface v1.3 Beta
Serial CLI Functions

Copyright 2014-2016 Andrew J Instone-Cowie.

This is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
*********************************************************************************************
*                                   Function dumpData()                                     *
*********************************************************************************************
*/

// Dump current configuration data to the serial port.
void dumpData( void ) {

	// This is not part of the MBI specification.

	// generic loop counter
	int i;
	
	// What version of software are we running?
	mySerial.print(F("Version: "));
	mySerial.print( majorVersion );
	mySerial.print(F("."));
	mySerial.println( minorVersion );

	// What is the live timer value?
	// Only show the first value, for consistency with the multi-bell version, even
	// though 12 values are being received and stored.
	mySerial.print(F("Timer: "));
	mySerial.println( bellStrikeDelay[0]/10 );
	
	// What is the EEPROM timer value?
	// Again show only the first value
	mySerial.print(F("EEPROM: "));
	mySerial.println( EEPROM.read(0) );

	// What are the debounce timer values (EEPROM 19)? 
	mySerial.print(F("Debounce: "));
	mySerial.println( bellDebounceDelay );
	mySerial.print(F("EEPROM: "));
	mySerial.println( EEPROM.read(19) );

	// What is the simulator quirks mode? (Held in EEPROM location 17)
	mySerial.print(F("Simulator: "));
	printSimulatorTypeName( simulatorType );
	mySerial.println("");
	mySerial.print(F("EEPROM: "));
	printSimulatorTypeName( EEPROM.read(17) );
	mySerial.println("");

	// What are the most recent sensor values?
	mySerial.print(F("Sensor(1=HI, 0=LO): "));
	mySerial.println( bellSensorLastValue );

	// Show debug mode status 
	mySerial.print(F("Debug: "));
	if ( debugMode ) { 
		mySerial.println(F("ON"));
		mySerial.print(F("Flags: "));
		printDebugMask( debugFlagsMask, maxDebugFlags );
		printDebugFlagsSet();
	}
	else
	{
		mySerial.println (F("OFF"));
	}

	mySerial.print(F("Free Mem: "));
	mySerial.println( freeMemory() );  

}

/*
*********************************************************************************************
*                                   Function setTimers()                                    *
*********************************************************************************************
*/

// Set the volatile (active) delay timers
void setTimers( unsigned long value ) {

	// Set all volatile timers to the specified ms value, for testing and calibration.
	// Do not overwrite the EEPROM timers. Used by handleCLI() in debug mode only.

	int i;
	for ( i = 0; i < 12; i++ ) {
		// Set the volatile strike delays to the value given. Any integer value is valid.
		bellStrikeDelay[i] = value;
	}
}

/*
*********************************************************************************************
*                                   Function showCLI()                                      *
*********************************************************************************************
*/

// Display the CLI prompt to the serial port.
void showCLI( void ) {

	// This is not part of the MBI specification.

	// If you call showCLI(), you need to supply the carriage return later, e.g. after
	// you have echoed the keypress.

	// Print the first part of the CLI
	mySerial.print(F(" : Q/B/S/D/"));

	if ( debugMode )
	{
		// Print the debug mode options - in this version all debug options
		// are available at any debug level.
		mySerial.print(F("d/Z/0-9/"));
	}

	// Print the trailing part of the CLI
	mySerial.print(F("? "));

}

/*
*********************************************************************************************
*                                  Function handleCLI()                                     *
*********************************************************************************************
*/

// Handle CLI input.
void handleCLI( byte commandByte ) {

	// This is not part of the MBI specification.

	// This function is passed the first (and possibly only) byte from the serial buffer,
	// once we know it's not an MBI command or new delay data.

	// generic loop counter
	int i;

	// generic scratch variable for vtSerial.ReadLong
	int readval;

	switch ( commandByte ) {

	case '?':    // ?  = Dump values to serial for debugging
		mySerial.println( char( commandByte ) );
		dumpData();
		showCLI();
		// blink the LED to indicate we got a valid command
		// just a quick blink so as not to slow the CLI down too much when cycling
		blinkLED( LED, 0, 1 ); //one quick
		break;

	case 'Q':    // Q  = Set simulator quirks mode
		mySerial.println( char( commandByte ) );
		// prompt for a new simulator type (check validity)	   
		char readNewSimType; // store the character read
		readNewSimType = '0'; // any invalid type
		// Prompt the user for a new simulator type 
		mySerial.print(F(" -> Type ["));
		mySerial.print( validSimulatorTypes );
		mySerial.print(F("]: "));
		while (! checkValidSimulatorType( readNewSimType ) ) {		
			if ( mySerial.available() ) {
				readNewSimType = toupper(mySerial.read());
			}
		}
		mySerial.println(readNewSimType);
		simulatorType = readNewSimType;
		printSimulatorTypeName( simulatorType );
		mySerial.println("");
		showCLI();
		// blink the LED to indicate we got a valid command
		blinkLED( LED, 2, 1 );
		break;		

	case 'B':    // B  = Cycle round the debounce timer value (ms)
		mySerial.println( char( commandByte ) );
		// Mod the current delay by the max delay, then add one
		// If it's currently 20, modding it = 0, + 1 = 1
		// If it's currently 1, modding it = 1, + 1 = 2, etc
		// That way it can never be 0 or more than 20.
		bellDebounceDelay = ( bellDebounceDelay % maxDebounceDelay ) + 1;
		mySerial.print(F("Debounce: "));
		mySerial.print( bellDebounceDelay );
		mySerial.println(F("ms"));
		showCLI();
		// just a quick blink so as not to slow the CLI down too much when cycling
		blinkLED( LED, 0, 1 ); //one quick
		break;
		
	case 'S':    // S  = Save settings to EEPROM as bytes
		mySerial.println( char( commandByte ) );
		saveToEEPROM();
		showCLI();
		// blink the LED to indicate we got a valid command
		blinkLED( LED, 2, 5 );
		break;

	case 'D':    // D  = Set debug mode ON, or change debug flags
		mySerial.println( char( commandByte ) );
		if ( ! debugMode ) {
			// Turn on debug mode
			debugMode = true;
			mySerial.println(F("Debug ON"));
			// Debug flags may already be set, so list them
			mySerial.print(F("Flags: "));
			printDebugMask( debugFlagsMask, maxDebugFlags );
			printDebugFlagsSet();
			showCLI();
			// blink the LED to indicate we got a valid command
			blinkLED( LED, 2, 6 );
		}
		else
		{
			// Debug mode is already on, so cycle round the debug flag options.
			// Elimination of VTSerial requires a cyclic approach.
			// Cycle round all potential debug flag values. For 3 bits this is (b001 - b111 ==
			// d1 - d7), or 1 to 2^maxDebugFlags - 1
			mySerial.println( char( commandByte ) );
			// Mod the current flags by the maximum (currently 7), then add one
			// If it's currently 7, modding it 7 = 0, + 1 = 1
			// If it's currently 1, modding it 7 = 1, + 1 = 2, etc
			// That way it can never be 0 or more than 7.
			debugFlagsMask = ( debugFlagsMask % 7 ) + 1;
			mySerial.print(F("Flags: "));
			printDebugMask( debugFlagsMask, maxDebugFlags );
			printDebugFlagsSet();
			showCLI();
			// just a quick blink so as not to slow the CLI down too much when cycling
			blinkLED( LED, 0, 1 ); //one quick
		} //! debugMode
		break;
		
	case 'd':    // d  = Set debug mode OFF
		mySerial.println( char( commandByte ) );
		if ( debugMode ) {
			debugMode = false;
			mySerial.println(F("Debug OFF"));
			showCLI();
			// blink the LED to indicate we got a valid command
			blinkLED( LED, 2, 7 );
			// Don't change the debug level here, remember it in case debugging is turned back on
		} // debugMode
		break;

	case 'Z':    // Z  = Set volatile (active) timers to 500msec for calibration
		// Debug mode only
		mySerial.println( char( commandByte ) );
		if ( debugMode ) {
			// Debug mode only
			setTimers( defaultDelayTimer );
			mySerial.println(F("Default timers"));
			// Display the updated data
			dumpData();
			// blink the LED to indicate we got a valid command
			blinkLED( LED, 2, 8 );
		}
		showCLI();
		break;
		
	case '0' ... '9':    // 0...9  = Debug Markers. Label range wheeze from the Arduino forums
		// Debug mode only
		if ( debugMode ) { 
			mySerial.print (F("DEBUG MARKER "));
			mySerial.println( char( commandByte ) );
		} else {
			mySerial.println( char( commandByte ) );
			showCLI();
			// just a quick blink so as not to slow the CLI down too much
			blinkLED( LED, 0, 1 ); //one quick
		}       
		break;

	default:
		// So this isn't an MBI command, not bell delay data, and it's not a non-MBI CLI command.
		// We don't know what this is, echo it as a char, flash the LED, and throw the data away.
		// Note than any other bytes that were read into the buffer are never looked at either.
		mySerial.println( char( commandByte ) );
		showCLI();
		blinkLED( LED, 3, 0 );
		
	} //switch tempDelayBuffer   
}

/*
*********************************************************************************************
*                           Function checkValidSimulatorType()                              *
*********************************************************************************************
*/

//Check that the simulator type supplied by the user (or found in EEPROM) is valid,
//by seeing if it exists in the list validSimulatorTypes[].

int checkValidSimulatorType( char testchar )
{
	//The test char should be listed in the array validSimulatorTypes[]
	int i;
	//scan the validSimulatorTypes[] array
	for ( i = 0; i < sizeof( validSimulatorTypes ) - 1; i++ ) {
		if( testchar == validSimulatorTypes[i] ) {
			//found the character, it's valid
			return true;
			//no need to look any further down the array
			break;
		}
	}
	// If we get here the testchar wasn't found, so it's invalid
	return false;
}

/*
*********************************************************************************************
*                             Function printSimulatorTypeName()                             *
*********************************************************************************************
*/

// Passed the char code for the simulator type, prints a textual representation of that type.

void printSimulatorTypeName( char thisType ) {

	// So this is reasonably horrible, but as I can't do F() globally,
	// this will have to do to get the text version into flash...	
	switch ( thisType ) {
	case 'A':
		mySerial.print(F("Abel"));
		break;
	case 'B':
		mySerial.print(F("Beltower"));
		break;
	case 'R':
		mySerial.print(F("Ringleader"));
		break;
	case 'V':
		mySerial.print(F("Virtual Belfry"));
		break;
	case 'X':
		mySerial.print(F("Generic"));
		break;
	default: // Some other
		mySerial.print(F("Unknown"));
		break;
	}
	
}



