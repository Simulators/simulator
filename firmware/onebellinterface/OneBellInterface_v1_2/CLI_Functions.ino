/*
One Bell Simulator Interface v1.2 Beta
Serial CLI Functions

Copyright 2014, 2015 Andrew J Instone-Cowie.

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

	// What are the live timer values?
	mySerial.print(F("Timers: "));
	for ( i = 0; i < 12; i++ ) {
		// Dump the timer values.
		mySerial.print( bellStrikeDelay[i]/10 );
		mySerial.print(F(" "));
	}
	mySerial.println(""); //new line

	// What are the EEPROM timer values?
	mySerial.print(F("EEPROM: "));
	for ( i = 0; i < 12; i++ ) {
		// Dump the timer values.
		mySerial.print( EEPROM.read(i) );
		mySerial.print(F(" "));
	}
	mySerial.println(""); //new line

	// What are the debounce timer values (EEPROM 19)? 
	mySerial.print(F("Debounce: "));
	mySerial.println( bellDebounceDelay );
	mySerial.print(F("EEPROM: "));
	mySerial.println( EEPROM.read(19) );

	// What is the simulator quirks mode? (Held in EEPROM location 17)
	mySerial.print(F("Simulator: "));

	switch ( EEPROM.read(17) ) {
	case 'A': // Abel
		mySerial.println(F("Abel"));
		break;
	case 'B': // Beltower
		mySerial.println(F("Beltower"));
		break;
	case 'R': // Ringleader
		mySerial.println(F("Ringleader"));
		break;
	case 'X': // Generic
		mySerial.println(F("Generic"));
		break;
	default: // Some other EEPROM value
		mySerial.println(F("Unknown"));
		break;
	}

	// What are the most recent sensor values?
	mySerial.print(F("Sensor(1=HIGH, 0=LOW): "));
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
void setTimers( int value ) {

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
	mySerial.print(F(" : A/B/R/X/U/S/D/"));

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

	case 'A':    // A  = Set Abel quirks mode
		mySerial.println( char( commandByte ) );
		if ( EEPROM.read( 17 ) != 'A' ) {
			EEPROM.write( 17, 'A' ); // Save Abel mode to EEPROM location 17
		}
		mySerial.println(F("EEPROM: Abel"));
		showCLI();
		// blink the LED to indicate we got a valid command
		blinkLED( LED, 2, 1 );
		break;

	case 'B':    // B  = Set Beltower quirks mode
		mySerial.println( char( commandByte ) );
		if ( EEPROM.read( 17 ) != 'B' ) {
			EEPROM.write( 17, 'B' ); // Save Beltower mode to EEPROM location 17
		}
		mySerial.println(F("EEPROM: Beltower"));
		showCLI();
		// blink the LED to indicate we got a valid command
		blinkLED( LED, 2, 2 );
		break;

	case 'R':    // R  = Set Ringleader quirks mode
		mySerial.println( char( commandByte ) );
		if ( EEPROM.read( 17 ) != 'R' ) {
			EEPROM.write( 17, 'R' ); // Save Ringleader mode to EEPROM location 17
		}
		mySerial.println(F("EEPROM: Ringleader"));
		showCLI();
		// blink the LED to indicate we got a valid command
		blinkLED( LED, 2, 3 );
		break;

	case 'X':    // x  = Set no quirks mode - Generic simulator
		mySerial.println( char( commandByte ) );
		if ( EEPROM.read( 17 ) != 'X' ) {
			EEPROM.write( 17, 'X' ); // Save no quirks mode to EEPROM location 17
		}
		mySerial.println(F("EEPROM: Generic"));
		showCLI();
		// blink the LED to indicate we got a valid command
		blinkLED( LED, 2, 4 );
		break;

	case 'U':    // U  = Cycle round the debounce timer value (ms)
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
		if ( EEPROM.read( 19 ) != byte( bellDebounceDelay ) ) {
			EEPROM.write( 19, byte( bellDebounceDelay ) ); // Save bellDebounceDelay to location 19
		}
		mySerial.println(F("Saved"));
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
		debugMode = false;
		mySerial.println(F("Debug OFF"));
		showCLI();
		// blink the LED to indicate we got a valid command
		blinkLED( LED, 2, 7 );
		// Don't change the debug level here, remember it in case debugging is turned back on
		break;

	case 'Z':    // Z  = Set volatile (active) timers to 500msec for calibration
		// Debug mode only
		mySerial.println( char( commandByte ) );
		if ( debugMode ) {
			// Debug mode only
			setTimers( 500 );
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



