/*
Simulator Interface v2.6
Serial CLI Functions

Copyright 2014-2025 Andrew J Instone-Cowie.

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
#if defined ARDUINO_AVR_SIMULATORMK1
	Serial.println("1");
#elif defined ARDUINO_AVR_SIMULATOR
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
	for ( i = 0; i < numChannels; i++ ) {
		// Dump the timer values.
		Serial.print( bellStrikeDelay[i]/10 );
		Serial.print(F(" "));
	}
	Serial.println(""); //new line

	// What are the EEPROM timer values?
	Serial.print(F("EEPROM Timers (cs): "));
	for ( i = 0; i < numChannels; i++ ) {
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

	// What is the simulator quirks mode? (Read in from EEPROM location 17)
	Serial.print(F("Active Simulator Type: "));
	printSimulatorTypeName( simulatorType );
	Serial.println("");
	Serial.print(F("EEPROM Simulator Type: "));
	printSimulatorTypeName( EEPROM.read(17) );
	Serial.println("");
	
	// Are delay timers being applied in the interface? (Read in from EEPROM location 25)
	// 0 = FALSE, anything else = TRUE.
	Serial.print(F("Apply Delay Timers: "));
	printTrueFalse( applyDelayTimers, true ); //second parameter for a newline
	Serial.print(F("EEPROM Apply Delay Timers: "));
	printTrueFalse( boolean( EEPROM.read(25) ), true ); //second parameter for a newline

	// What are the most recent sensor values?
	Serial.print(F("Current Sensor Inputs (1=HIGH, 0=LOW): "));
	for ( i = 0; i < numChannels; i++ ) {
		// Dump the last read values.
		Serial.print( bellSensorLastValue[i] );
		Serial.print(F(" "));
	}
	Serial.println(""); //new line

	// Which sensors are enabled?
	Serial.print(F("Enabled Sensors: "));
	printMask( enabledSensorMask, numChannels );
	
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
		printMask( debugFlagsMask, maxDebugFlags );
		Serial.println(F("Debug Flags Set: "));
		printDebugFlagsSet();
		Serial.print(F("Debug Bell Mask: "));
		printMask( debugBellMask, numChannels );
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
void setTimers( unsigned long value ) {

	// Set all volatile timers to the specified ms value, for testing and calibration.
	// Do not overwrite the EEPROM timers. Used by handleCLI() in debug mode only.

	int i;
	for ( i = 0; i < 12; i++ ) {
		// Set the volatile strike delays to the value given. Any integer value is valid.
		// 12 hard coded because the bellStrikeDelay[] array always has 12 values.
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
	//Serial.print(F(" : A/B/R/X/#/U/E/S/P/D/"));
	Serial.print(F(" : Q/#/B/E/S/P/D/X/"));

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

	case 'Q':    // Q  = Set simulator quirks mode
		Serial.println( char( commandByte ) );
		// prompt for a new simulator type (check validity)	   
		char readNewSimType; // store the character read
		readNewSimType = '0'; // any invalid type
		termSetFor( TERM_INPUT );
		// Prompt the user for a new simulator type 
		Serial.print(F(" -> New simulator type ["));
		// List the valid responses
		for ( i = 0; i < numSimulatorNames; i++) {
			Serial.print( simulatorNames[i].simOneChar );
		}
		Serial.print(F("]: "));
		termSetFor( TERM_DEFAULT );
		while (! checkValidSimulatorType( readNewSimType ) ) {		
			if ( Serial.available() ) {
				readNewSimType = toupper(Serial.read());
			}
		}
		Serial.println(readNewSimType);
		simulatorType = readNewSimType;
		termSetFor( TERM_CONFIRM );
		printSimulatorTypeName( simulatorType );
		Serial.println(F(" mode set"));
		termSetFor( TERM_DEFAULT );
		showCLI();
		// blink the LED to indicate we got a valid command
		blinkLED( LEDyellow, 2, 1 );
		break;

	case '#':    // #  = Set the number of active channels
		Serial.println( char( commandByte ) );
		readval = 0; // Set the value to be read deliberately out of range.
		do {
			termSetFor( TERM_INPUT );
			Serial.print(F(" -> Enter number of active channels [1-"));
			Serial.print(maxNumChannels); // this is the max the hardware will support.
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
		blinkLED( LEDyellow, 2, 2 );
		break;
		
	case 'B':    // B  = Set the debounce timer value (ms)
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
		blinkLED( LEDyellow, 2, 3 );
		break;
		
	case 'S':    // S  = Save settings to EEPROM as bytes
		Serial.println( char( commandByte ) );
		saveToEEPROM();
		showCLI();
		// blink the LED to indicate we got a valid command
		blinkLED( LEDyellow, 2, 5 );
		break;

	case 'E':    // E  = Enable/Disable a sensor (non-persistently)
		Serial.println( char( commandByte ) );
		readval = 0; // Set the value to be read deliberately out of range.
		do {
			termSetFor( TERM_INPUT );
			// show the enabled sensors, LSB (treble) first
			Serial.print(F("Enabled Sensors: "));
			printMask( enabledSensorMask, numChannels ); // includes a CR
			// Prompt the user for a sensor number to toggle on or off
			Serial.print(F(" -> Toggle bell value [1-"));
			Serial.print( numChannels );
			Serial.print(F(", 0=Done]: "));
			termSetFor( TERM_DEFAULT );
			readval = vtSerial.ReadLong(); // read integer ( expecting 1 - 12, 0 to finish)
			Serial.println("");
			// Toggle the channel bit in the enable mask by XOR-ing the current value with 1
			// (remembering that bell numbers are 1-12, bits/channels are 0-11). Max 12 bits.
			toggleMaskBit( &enabledSensorMask, readval - 1, numChannels );
		} while ( readval > 0 && readval <= numChannels );
		// Set the enable state for all sensors
		enableSensors( enabledSensorMask, numChannels );
		// finish by showing the updated enabled sensor list
		termSetFor( TERM_CONFIRM );
		Serial.print(F("Enabled Sensors: "));
		printMask( enabledSensorMask, numChannels ); // includes a CR
		termSetFor( TERM_DEFAULT );
		showCLI();
		blinkLED( LEDyellow, 2, 4 );
		break; 
			
	case 'X':    // X = Toggle apply delay timers flag
		applyDelayTimers = !applyDelayTimers;
		Serial.println( char( commandByte ) );
		termSetFor( TERM_CONFIRM );
		Serial.print(F("Apply delay timers "));
		printTrueFalse( applyDelayTimers, true ); //second parameter for a newline
		Serial.println(F("Flag set, please save settings and reboot interface"));
		termSetFor( TERM_DEFAULT );
		showCLI();
		blinkLED( LEDyellow, 0, 1 );
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
			Serial.print(F("Debug Bell Mask: "));
			printMask( debugBellMask, numChannels );
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
		if ( debugMode ) {
			debugMode = false;
			termSetFor( TERM_DEBUG );
			Serial.println(F("Debug Mode OFF"));
			termSetFor( TERM_DEFAULT );
			showCLI();
			// blink the LED to indicate we got a valid command
			blinkLED( LEDyellow, 2, 7 );
			// Don't change the debug level here, remember it in case debugging is turned back on
		} //debugMode
		break;

	case 'Z':    // Z  = Set volatile (active) timers to 500ms for calibration, or 100ms if we aren't applying delays in the interface
		// Debug mode only
		Serial.println( char( commandByte ) );
		if ( debugMode ) {
			// Debug mode only
			termSetFor( TERM_DEBUG );
			Serial.print(F("Default active timers set to "));
			if( applyDelayTimers ) {
				setTimers( defaultDelayTimer );
				Serial.println(F("500ms"));
			}
			else {
				setTimers( 100 );
				Serial.println(F("100ms"));
			}
			termSetFor( TERM_DEFAULT );
			showCLI();
			// blink the LED to indicate we got a valid command
			blinkLED( LEDyellow, 2, 8 );
		}
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
				printMask( debugBellMask, numChannels ); // includes a CR
				// Prompt the user for a bell number to toggle on or off
				Serial.print(F(" -> Toggle bell value [1-"));
				Serial.print( numChannels );
				Serial.print(F(", 0=Done]: "));
				termSetFor( TERM_DEFAULT );
				readval = vtSerial.ReadLong(); // read integer ( expecting 1 - 12, 0 to finish)
				Serial.println("");
				// Toggle the channel bit in the debug mask by XOR-ing the current value it with 1
				// (remembering that bell numbers are 1-12, bits/channels are 0-11). Max 12 bits.
				toggleMaskBit( &debugBellMask, readval - 1, numChannels );
			} while ( readval > 0 && readval <= numChannels );
			// finish by showing the updated bell mask
			termSetFor( TERM_DEBUG );
			Serial.print(F("Debug Bell Mask: "));
			printMask( debugBellMask, numChannels );	  
			termSetFor( TERM_DEFAULT );
			blinkLED( LEDyellow, 2, 10 );
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
		for ( i = 0; i < numChannels; i++ ) {
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

	Serial.println(F(" -> [Q] - Set simulator quirks mode"));
	Serial.print(F(" -> [#] - Set number of active channels (1->"));
	Serial.print(maxNumChannels); //hardware maximum
	Serial.println(F(")"));
	Serial.println(F(" -> [B] - Set debounce timer (1ms->20ms)"));
	Serial.println(F(" -> [E] - Enable/Disable a sensor"));
	Serial.println(F(" -> [X] - Toggle apply delay timers flag"));
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

/*
*********************************************************************************************
*                                   Function printMask()                                    *
*********************************************************************************************
*/

// Print a mask (e.g. debugMask or enabledSensorMask) as fixed and spaced width binary, LSB
// (usually treble) first, showing a fixed number of bits only.
void printMask( word thisMask, int places ) {
	int i;
	for ( i = 0; i < places; i++ ) {
		// Print the value of the bits.
		Serial.print( bitRead( thisMask, i ) );
		Serial.print(F(" "));
	}
	Serial.println(""); //new line
}

/*
*********************************************************************************************
*                                Function toggleMaskBit()                                   *
*********************************************************************************************
*/

// Toggle the value of the specified bit in a mask by XOR-ing it with 1, e.g. to Enable or
// disable a sensor or debug a bell. Bits are passed as 0 to 15, if you need to convert from
// a bell number, do it before passing the bit here. Pass the mask as a pointer so the
// original data gets updated. Don't bother trying to toggle a bit >maxBits.
boolean toggleMaskBit( word *thisMask, int thisBit, int maxBits ) {
	if ( thisBit >= 0 && thisBit < maxBits ) {
		bitWrite( *thisMask, thisBit, ( bitRead ( *thisMask, thisBit ) ^ 1 ));
		return true;
	}
	else
	{
		return false;
	}
}


/*
*********************************************************************************************
*                                 Function enableSensors()                                  *
*********************************************************************************************
*/

// Run through the enabledSensorMask, and set the state machine for each sensor to be
// WAIT_FOR_INPUT or SENSOR_DISABLED based on the bit value (1 = enabled, 0 = disabled).
void enableSensors( word thisMask, int maxBits ) {
	int i;
	for ( i = 0; i < maxBits; i++ ) {
		if ( bitRead( thisMask, i ) == 1 ) {
			// Enable the sensor
			bellMachineState[i] = WAIT_FOR_INPUT;
		}
		else
		{
			// Disable the sensor
			bellMachineState[i] = SENSOR_DISABLED;
		}
	}

}

/*
*********************************************************************************************
*                           Function checkValidSimulatorType()                              *
*********************************************************************************************
*/

// Check that the simulator type supplied by the user (or found in EEPROM) is valid,
// by seeing if it exists in the simOneChar field of simulatorNames[].

boolean checkValidSimulatorType( char testchar ) {

	int i;
	for ( i = 0; i < numSimulatorNames; i++) {
		if (testchar == simulatorNames[i].simOneChar) {
			return true;
			// No need to go any further down the list
			break;
		}
	}

	return false;
}

/*
*********************************************************************************************
*                             Function printSimulatorTypeName()                             *
*********************************************************************************************
*/

// Passed the char code for the simulator type, prints a textual representation of that type.

void printSimulatorTypeName( char thisType ) {
	
	boolean found;
	found = false;
	int i;
	for ( i = 0; i < numSimulatorNames; i++) {
		if (thisType == simulatorNames[i].simOneChar) {
			Serial.print( simulatorNames[i].simLongName );
			found = true;
			break;
		}
	}
	
	if ( ! found ) {
		// It wasn't in the array.
		Serial.print(F("Unknown"));
	}
	
}

/*
*********************************************************************************************
*                                  Function printTrueFalse                                  *
*********************************************************************************************
*/

// Passed the flag, print a textual representation of TRUE or FALSE, with an optional newline.

void printTrueFalse( boolean flag, boolean newline ) {
	
	if ( flag ) {
		Serial.print(F("TRUE"));
	}
	else {
		Serial.print(F("FALSE"));
	}
	
	if ( newline ) {
		Serial.println("");
	}

}


