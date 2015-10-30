/*
Simulator Interface v2.3 Beta
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

	// Position the cursor and clear the screen.
	termClear();

	// generic loop counter
	int i;
	
	// What version of software are we running?
	termSetFor( TERM_HEADING );
	Serial.print(F("Software Version: "));
	Serial.print( majorVersion );
	Serial.print(F("."));
	Serial.println( minorVersion );
	termSetFor( TERM_DEFAULT );

	// What version of hardware are we compiled for? 
	Serial.print(F("Hardware Version: "));
#if defined HW_MK1
	Serial.println("1");
#elif defined HW_MK2
	Serial.println("2");
#else
	Serial.println(F("Unknown"));
#endif
	
	// How many channels are we scanning? 
	Serial.print(F("Active Channels: "));
	Serial.println( numChannels );
	Serial.print(F("EEPROM Channels: "));
	Serial.println( EEPROM.read(18) );
	
	// What are the live timer values?
	Serial.print(F("Active Timers (cs): "));
	for ( i = 0; i < 12; i++ ) {
		// Dump the timer values.
		Serial.print( bellStrikeDelay[i]/10 );
		Serial.print(F(" "));
	}
	Serial.println(""); //new line

	// What are the EEPROM timer values?
	Serial.print(F("EEPROM Timers (cs): "));
	for ( i = 0; i < 12; i++ ) {
		// Dump the timer values.
		Serial.print( EEPROM.read(i) );
		Serial.print(F(" "));
	}
	Serial.println(""); //new line

	// What are the debounce timer values (EEPROM 19)? 
	Serial.print(F("Active Debounce Timer (ms): "));
	Serial.println( bellDebounceDelay );
	Serial.print(F("EEPROM Debounce Timer (ms): "));
	Serial.println( EEPROM.read(19) );

	// What is the simulator quirks mode? (Held in EEPROM location 17)
	Serial.print(F("Simulator Type: "));

	switch ( EEPROM.read(17) ) {
	case 'A': // Abel
		Serial.println(F("Abel"));
		break;
	case 'B': // Beltower
		Serial.println(F("Beltower"));
		break;
	case 'R': // Ringleader
		Serial.println(F("Ringleader"));
		break;
	case 'X': // Generic
		Serial.println(F("Generic"));
		break;
	default: // Some other EEPROM value
		Serial.println(F("Unknown"));
		break;
	}

	// What are the most recent sensor values?
	Serial.print(F("Current Sensor Inputs (1=HIGH, 0=LOW): "));
	for ( i = 0; i < 12; i++ ) {
		// Dump the last read values.
		Serial.print( bellSensorLastValue[i] );
		Serial.print(F(" "));
	}
	Serial.println(""); //new line

	// What is the configured serial port speed(indexed in EEPROM 20)? 
	Serial.print(F("Serial Port Speed: "));
	serialSpeed = int( EEPROM.read(20) );
	// setup sets a default 2400 if the EEPROM value is bad...
	if ( serialSpeed < 0 || serialSpeed > 2 ) {
		serialSpeed = defaultSerialSpeed;
	}
	Serial.println( serialSpeeds[serialSpeed] );  

	// Support for an accidental is not yet written (and probably never will be)
	// Serial.println(F("Accidentals not supported"));
	
	// Show debug mode status 
	Serial.print(F("Debug Mode: "));
	if ( debugMode ) { 
		Serial.println(F("ON"));
		Serial.print(F("Debug Flags Mask: "));
		printDebugMask( debugFlagsMask, maxDebugFlags );
		Serial.println(F("Debug Flags Set: "));
		printDebugFlagsSet();
		Serial.print(F("Debug Bell Mask: "));
		printDebugMask( debugBellMask, 12 );
	}
	else
	{
		Serial.println (F("OFF"));
	}

	Serial.print(F("Free Memory: "));
	Serial.println( freeMemory() );  

#ifdef USE_CRO
	Serial.print(F("CRO Timing Pin Enabled: "));
	Serial.println( CROpin );  
#endif

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

	// The CLI is different when in debug mode.

	// Set the terminal modes for the CLI.
	termSetFor( TERM_CLI );

	// Print the first part of the CLI
	Serial.print(F(" : A/B/R/X/#/U/S/P/D/"));

	if ( debugMode )
	{
		// Print the debug mode options - in this version all debug options
		// are available at any debug level.
		Serial.print(F("d/Z/M/0-9/L/"));
	}

	// Print the trailing part of the CLI
	Serial.print(F("H/T/? "));

	// Set the terminal modes back to normal.
	termSetFor( TERM_DEFAULT );

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
		Serial.println( char( commandByte ) );
		dumpData();
		showCLI();
		// blink the LED to indicate we got a valid command
		// just a quick blink so as not to slow the CLI down too much when cycling
		blinkLED( LEDyellow, 0, 1 ); //one quick
		break;

	case 'A':    // A  = Set Abel quirks mode
		Serial.println( char( commandByte ) );
		if ( EEPROM.read( 17 ) != 'A' ) {
			EEPROM.write( 17, 'A' ); // Save Abel mode to EEPROM location 17
		}
		termSetFor( TERM_CONFIRM );
		Serial.println(F("Abel mode set in EEPROM"));
		termSetFor( TERM_DEFAULT );
		showCLI();
		// blink the LED to indicate we got a valid command
		blinkLED( LEDyellow, 2, 1 );
		break;

	case 'B':    // B  = Set Beltower quirks mode
		Serial.println( char( commandByte ) );
		if ( EEPROM.read( 17 ) != 'B' ) {
			EEPROM.write( 17, 'B' ); // Save Beltower mode to EEPROM location 17
		}
		termSetFor( TERM_CONFIRM );
		Serial.println(F("Beltower mode set in EEPROM"));
		termSetFor( TERM_DEFAULT );
		showCLI();
		// blink the LED to indicate we got a valid command
		blinkLED( LEDyellow, 2, 2 );
		break;

	case 'R':    // R  = Set Ringleader quirks mode
		Serial.println( char( commandByte ) );
		if ( EEPROM.read( 17 ) != 'R' ) {
			EEPROM.write( 17, 'R' ); // Save Ringleader mode to EEPROM location 17
		}
		termSetFor( TERM_CONFIRM );
		Serial.println(F("Ringleader mode set in EEPROM"));
		termSetFor( TERM_DEFAULT );
		showCLI();
		// blink the LED to indicate we got a valid command
		blinkLED( LEDyellow, 2, 3 );
		break;

	case 'X':    // x  = Set no quirks mode - Generic simulator
		Serial.println( char( commandByte ) );
		if ( EEPROM.read( 17 ) != 'X' ) {
			EEPROM.write( 17, 'X' ); // Save no quirks mode to EEPROM location 17
		}
		termSetFor( TERM_CONFIRM );
		Serial.println(F("Generic mode set in EEPROM"));
		termSetFor( TERM_DEFAULT );
		showCLI();
		// blink the LED to indicate we got a valid command
		blinkLED( LEDyellow, 2, 4 );
		break;

	case '#':    // #  = Set the number of active channels
		Serial.println( char( commandByte ) );
		readval = 0; // Set the value to be read deliberately out of range.
		do {
			termSetFor( TERM_INPUT );
			Serial.print(F(" -> Enter number of active channels [1-"));
			Serial.print(maxNumChannels);
			Serial.print(F("]: "));
			termSetFor( TERM_DEFAULT );
			readval = vtSerial.ReadLong();       // read integer
			Serial.println("");
		} while ( readval < 1 || readval > maxNumChannels );
		numChannels = readval;
		termSetFor( TERM_CONFIRM );
		Serial.print(F("Active Channels: "));
		Serial.println( numChannels );
		termSetFor( TERM_DEFAULT );
		showCLI();
		// just a quick blink so as not to slow the CLI down too much when cycling
		blinkLED( LEDyellow, 0, 1 ); //one quick
		break;
		
	case 'U':    // U  = Set the debounce timer value (ms)
		Serial.println( char( commandByte ) );
		readval = 0; // Set the value to be read deliberately out of range.
		do {
			termSetFor( TERM_INPUT );
			Serial.print(F(" -> Enter debounce timer [1-20ms]: "));
			termSetFor( TERM_DEFAULT );
			readval = vtSerial.ReadLong();       // read integer
			Serial.println("");
		} while ( readval < 1 || readval > maxDebounceDelay );
		bellDebounceDelay = readval;
		termSetFor( TERM_CONFIRM );
		Serial.print(F("Debounce Timer: "));
		Serial.print( bellDebounceDelay );
		Serial.println(F("ms"));
		termSetFor( TERM_DEFAULT );
		showCLI();
		// just a quick blink so as not to slow the CLI down too much when cycling
		blinkLED( LEDyellow, 0, 1 ); //one quick
		break;
		
	case 'S':    // S  = Save settings to EEPROM as bytes
		Serial.println( char( commandByte ) );
		termSetFor( TERM_CONFIRM );
		if ( EEPROM.read( 18 ) != byte( numChannels ) ) {
			EEPROM.write( 18, byte( numChannels ) ); // Save numChannels (int) to location 18
		}
		Serial.println(F("Active channels set in EEPROM"));
		if ( EEPROM.read( 19 ) != byte( bellDebounceDelay ) ) {
			EEPROM.write( 19, byte( bellDebounceDelay ) ); // Save bellDebounceDelay to location 19
		}
		Serial.println(F("Debounce timer set in EEPROM"));
		termSetFor( TERM_DEFAULT );
		showCLI();
		// blink the LED to indicate we got a valid command
		blinkLED( LEDyellow, 2, 5 );
		break;
		
	case 'P':    // P  = Set the serial port speed
		Serial.println( char( commandByte ) );
		readval = 9; // Set the value to be read deliberately out of range. (0 is valid value)
		do {
			termSetFor( TERM_INPUT );
			Serial.print(F(" -> Enter serial port speed (0=2400/1=4800/2=9600) [0/1/2]: "));
			termSetFor( TERM_DEFAULT );
			readval = vtSerial.ReadLong();       // read integer
			Serial.println("");
		} while ( readval < 0 || readval > 2 );
		serialSpeed = readval;
		termSetFor( TERM_CONFIRM );
		Serial.print(F("Serial Port Speed: "));
		Serial.println( serialSpeeds[serialSpeed] );
		if ( EEPROM.read( 20 ) != byte( serialSpeed ) ) {
			EEPROM.write( 20, byte( serialSpeed ) ); // Save serialSpeed to location 20
		}
		Serial.println(F("Serial speed set in EEPROM, please reboot interface"));
		termSetFor( TERM_DEFAULT );
		showCLI();
		// blink the LED to indicate we got a valid command
		blinkLED( LEDyellow, 2, 9 ); 
		break;
		
	case 'D':    // D  = Set debug mode ON, or cycle debug level 1 to maxDebugLevel
		Serial.println( char( commandByte ) );
		if ( ! debugMode ) {
			// Turn on debug mode
			debugMode = true;
			termSetFor( TERM_DEBUG );
			Serial.println(F("Debug Mode ON"));
			// Debug flags may already be set, so list them
			Serial.println(F("Debug Flags Set: "));
			printDebugFlagsSet();
			termSetFor( TERM_DEFAULT );
			showCLI();
			// blink the LED to indicate we got a valid command
			blinkLED( LEDyellow, 2, 6 );
		}
		else
		{
			// Debug mode is already on, so set the debug flags from 0 to maxDebugFlags
			// For each flag from 0 to maxDebugFlags-1
			// Prompt to toggle this flag by name
			// Get response, 1 = on, 0 = off
			// bitWrite the value in the debugFlagsMask
			// Note that you can turn all the flags off and still be in debug mode.
			for ( i = 0; i < maxDebugFlags; i++ ) {
				readval = 9; // Set the value to be read deliberately out of range.
				do {
					termSetFor( TERM_INPUT );
					Serial.print(F(" -> Enable "));
					printDebugFlagName( i );
					Serial.print(F(" (0=Off/1=On) [0/1]: "));
					termSetFor( TERM_DEFAULT );
					readval = vtSerial.ReadLong();       // read integer
					Serial.println("");
				} while ( readval < 0 || readval > 1 );
				if ( readval == 0 ) {
					// Clear the bit
					bitWrite( debugFlagsMask, i, 0 );
				}
				else if ( readval == 1 ) {
					// Set the bit
					bitWrite( debugFlagsMask, i, 1 );
				}
			}
			termSetFor( TERM_DEBUG );
			Serial.println(F("Debug Flags Set: "));
			printDebugFlagsSet();
			termSetFor( TERM_DEFAULT );
			showCLI();
			// just a quick blink so as not to slow the CLI down too much when cycling
			blinkLED( LEDyellow, 0, 1 ); //one quick
		} //! debugMode
		break;
		
	case 'd':    // d  = Set debug mode OFF
		Serial.println( char( commandByte ) );
		debugMode = false;
		termSetFor( TERM_DEBUG );
		Serial.println(F("Debug Mode OFF"));
		termSetFor( TERM_DEFAULT );
		showCLI();
		// blink the LED to indicate we got a valid command
		blinkLED( LEDyellow, 2, 7 );
		// Don't change the debug level here, remember it in case debugging is turned back on
		break;

	case 'Z':    // Z  = Set volatile (active) timers to 500msec for calibration
		// Debug mode only
		Serial.println( char( commandByte ) );
		if ( debugMode ) {
			// Debug mode only
			setTimers( 500 );
			termSetFor( TERM_DEBUG );
			Serial.println(F("Default active timers set"));
			termSetFor( TERM_DEFAULT );
			// Display the updated data
			dumpData();
			// blink the LED to indicate we got a valid command
			blinkLED( LEDyellow, 2, 8 );
		}
		showCLI();
		break;
		
	case 'M':    // M  = Toggle bits in the debug bell mask (1 = on, 0 = off)
		// Debug mode only
		Serial.println( char( commandByte ) );
		if ( debugMode ) {
			readval = 0; // Set the value to be read deliberately out of range.
			do {
				termSetFor( TERM_INPUT );
				// show the current mask, LSB (treble) first
				Serial.print(F("Debug Bell Mask: "));
				printDebugMask( debugBellMask, 12 ); // includes a CR
				// Prompt the user for a bell number to toggle on or off
				Serial.print(F(" -> Toggle bell value [1-12, 0=Done]: "));
				termSetFor( TERM_DEFAULT );
				readval = vtSerial.ReadLong(); // read integer ( expecting 1 - 12, 0 to finish)
				Serial.println("");
				// Toggle the channel bit in the debug mask by XOR-ing the current value it with 1
				// (remembering that bell numbers are 1-12, bits/channels are 0-11)
				if ( readval > 0 && readval < 13 ) {
					bitWrite( debugBellMask, readval - 1, ( bitRead ( debugBellMask, readval - 1 ) ^ 1 ));
				}
			} while ( readval > 0 && readval < 13 );
			// finish by showing the updated bell mask
			termSetFor( TERM_DEBUG );
			Serial.print(F("Debug Bell Mask: "));
			printDebugMask( debugBellMask, 12 );	  
			// The debug bell mask doesn't get saved anywhere and is reset to all-on on boot.
			termSetFor( TERM_DEFAULT );
			// just a quick blink so as not to slow the CLI down too much
			blinkLED( LEDyellow, 0, 1 ); //one quick
		}
		showCLI();
		break; 

	case '0' ... '9':    // 0...9  = Debug Markers. Label range wheeze from the Arduino forums
		// Debug mode only
		if ( debugMode ) { 
			Serial.print (F("DEBUG MARKER "));
			Serial.println( char( commandByte ) );
		} else {
			Serial.println( char( commandByte ) );
			showCLI();
			// just a quick blink so as not to slow the CLI down too much
			blinkLED( LEDyellow, 0, 1 ); //one quick
		}       
		break;

	case 'L':    // L  = Debug Levels Help
		// Debug mode only
		Serial.println( char( commandByte ) );
		if ( debugMode ) {
			showCLIDebugHelp();
		}
		showCLI();
		// just a quick blink so as not to slow the CLI down too much
		blinkLED( LEDyellow, 0, 1 ); //one quick
		break;
		
	case 'H':    // H  = Help
		Serial.println( char( commandByte ) );
		showCLIHelp();
		showCLI();
		// just a quick blink so as not to slow the CLI down too much
		blinkLED( LEDyellow, 0, 1 ); //one quick
		break;
		
	case 'T':    // T  = Test Mode
		Serial.println( char( commandByte ) );
		termSetFor( TERM_CONFIRM );
		Serial.print(F("Test Mode in "));
		Serial.print(testStartDelay);
		Serial.print(F(" seconds..."));
		termSetFor( TERM_DEFAULT );
		digitalWrite( LEDred, HIGH);
		digitalWrite( LEDyellow, HIGH);
		delay(testStartDelay * 1000); //testStartDelay is in seconds.
		// put all the channels into test mode
		for ( i = 0; i < 12; i++ ) {
			bellMachineState[i] = TEST_MODE;
		}
		break;  
		
	default:
		// So this isn't an MBI command, not bell delay data, and it's not a non-MBI CLI command.
		// We don't know what this is, echo it as a char, flash the LED, and throw the data away.
		// Note than any other bytes that were read into the buffer are never looked at either.
		Serial.println( char( commandByte ) );
		showCLI();
		blinkLED( LEDyellow, 3, 0 );
		
	} //switch tempDelayBuffer   
}

/*
*********************************************************************************************
*                                 Function showCLIHelp()                                    *
*********************************************************************************************
*/

// Display the CLI help text.
void showCLIHelp(void) {

	// This is not part of the MBI specification.

	// Position the cursor and clear the screen.
	termClear();

	// Keep it short, this is all static literal data!
	termSetFor( TERM_HEADING );
	Serial.println(F("CLI Commands:"));
	termSetFor( TERM_DEFAULT );
	Serial.println(F(" -> [A] - Set Abel simulator mode in EEPROM"));
	Serial.println(F(" -> [B] - Set Beltower simulator mode in EEPROM"));
	Serial.println(F(" -> [R] - Set Ringleader simulator mode in EEPROM"));
	Serial.println(F(" -> [X] - Set generic simulator mode in EEPROM"));
	Serial.print(F(" -> [#] - Set number of active channels (1->"));
	Serial.print(maxNumChannels);
	Serial.println(F(")"));
	Serial.println(F(" -> [U] - Set debounce timer (1ms->20ms)"));
	Serial.println(F(" -> [S] - Save settings in EEPROM"));
	Serial.println(F(" -> [P] - Set serial port speed in EEPROM"));
	Serial.println(F(" -> [D] - Turn debug mode ON or change debug flags"));
	Serial.println(F(" -> [d] - Turn debug mode OFF"));
	Serial.println(F(" -> [Z] - Set Active timers to default 500ms (debug mode only)"));
	Serial.println(F(" -> [M] - Set Debug Bell Mask (debug mode only)"));
	Serial.println(F(" -> [0-9] - Print debug markers (debug mode only)"));
	Serial.println(F(" -> [L] - Display debug levels help text (debug mode only)"));
	Serial.println(F(" -> [H] - Display this help text"));
	Serial.println(F(" -> [T] - Enter test mode (reset to exit)"));
	Serial.println(F(" -> [?] - Display current settings"));

}

/*
*********************************************************************************************
*                                Function showCLIDebugHelp()                                *
*********************************************************************************************
*/

// Display the CLI debug levels help text.
void showCLIDebugHelp(void) {

	// This is not part of the MBI specification.

	// Position the cursor and clear the screen.
	termClear();

	// Keep it short, this is all static literal data!
	termSetFor( TERM_HEADING );
	Serial.println(F("Debug Flags:"));
	termSetFor( TERM_DEFAULT );
	int i;
	
	for ( i = 0; i <maxDebugFlags; i++ ) {
		// Dump the debug levels.
		Serial.print(F(" ["));
		Serial.print( i );
		Serial.print(F("] -> "));
		printDebugFlagName( i );
		Serial.println("");
	}

}

