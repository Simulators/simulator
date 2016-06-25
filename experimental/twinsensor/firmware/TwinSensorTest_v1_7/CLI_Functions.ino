/*
Twin Sensor Test v1.7 Beta
Serial CLI Functions

Copyright 2016 Andrew J Instone-Cowie.

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

#ifdef USE_ATMEGA382P

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
	
	//temp scratch variable for EEPROM.get()
	unsigned long tempDeltaTime;
	float tempSpeedFactor;
	
	// What version of software are we running?
	termSetFor( TERM_HEADING );
	Serial.print(F("Software Version: "));
	Serial.print( majorVersion );
	Serial.print(F("."));
	Serial.println( minorVersion );
	termSetFor( TERM_DEFAULT );

	// What are the active & EEPROM the debounce timer values? 
	Serial.print(F("Active Debounce Timeout (ms): "));
	Serial.println( sensorDebounceTimeout );
	Serial.print(F("EEPROM Debounce Timeout (ms): "));
	Serial.println( EEPROM.read(4) );

	// What are the active & EEPROM rendezvous timer values?
	Serial.print(F("Active Rendezvous Timeouts (ms): "));
	for ( i = 0; i < numSensors; i++ ) {
		// Dump the timer values.
		Serial.print( sensorRendezvousTimeout[i] );
		Serial.print(F(" "));
	}
	Serial.println(""); //new line
	Serial.print(F("EEPROM Rendezvous Timeouts (ms): "));
	Serial.print( EEPROM.read(2) );
	Serial.print(F(" "));
	Serial.println( EEPROM.read(3) );
	
	// What are the active & EEPROM strike timeout values?
	Serial.print(F("Active Strike Timeouts (ms): "));
	for ( i = 0; i < numSensors; i++ ) {
		// Dump the timer values.
		Serial.print( sensorStrikeTimeout[i] );
		Serial.print(F(" "));
	}
	Serial.println(""); //new line
	Serial.print(F("EEPROM Strike Timeouts (ms): "));
	Serial.print( EEPROM.read(0) * 10 );
	Serial.print(F(" "));
	Serial.println( EEPROM.read(1) * 10);

	// What are the active & EEPROM bell direction settings?
	Serial.print(F("Active Bell Direction: "));
	Serial.println( sensorChar[ bellDirection ] );
	Serial.print(F("EEPROM Bell Direction: "));
	Serial.println( sensorChar[ EEPROM.read(6) ] );
	
	// What are the active & EEPROM bell minimum delta times?
	Serial.print(F("Active Minimum Delta (ms): "));
	Serial.println( bellMinDelta );
	Serial.print(F("EEPROM Minimum Delta (ms): "));
	EEPROM.get( 7, tempDeltaTime );
	Serial.println( tempDeltaTime );
	
	// What are the active & EEPROM speed factors?
	Serial.print(F("Active Speed Factor: "));
	Serial.println( speedFactor );
	Serial.print(F("EEPROM Speed Factor: "));
	EEPROM.get( 11, tempSpeedFactor );
	Serial.println( tempSpeedFactor );
	
	// What is the active backstrokeCutoffDelta time (calculated only)
	Serial.print(F("Backstroke CutOff Delta (ms): "));
	Serial.println( backstrokeCutoffDelta );
	
	// What are the most recent sensor values?
	Serial.print(F("Current Sensor Inputs (1=HIGH, 0=LOW): "));
	for ( i = 0; i < numSensors; i++ ) {
		// Dump the last read values.
		Serial.print( sensorLastValue[i] );
		Serial.print(F(" "));
	}
	Serial.println(""); //new line

	// What is the configured serial port speed(indexed in EEPROM 5)? 
	Serial.print(F("Serial Port Speed: "));
	serialSpeed = int( EEPROM.read(5) );
	// setup sets a default 2400 if the EEPROM value is bad...
	if ( serialSpeed < 0 || serialSpeed > 2 ) {
		serialSpeed = defaultSerialSpeed;
	}
	Serial.println( serialSpeeds[serialSpeed] );  
	
	// Show debug mode status 
	Serial.print(F("Debug Mode: "));
	if ( debugMode ) { 
		Serial.println(F("ON"));
		Serial.print(F("Debug Flags Mask: "));
		printMask( debugFlagsMask, maxDebugFlags );
		Serial.println(F("Debug Flags Set: "));
		printDebugFlagsSet();
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
	Serial.print(F(" : B/R/T/W/M/F/S/P/O/o/D/"));

	if ( debugMode )
	{
		// Print the debug mode options - in this version all debug options
		// are available at any debug level.
		Serial.print(F("d/0-9/L/"));
	}

	// Print the trailing part of the CLI
	Serial.print(F("H/? "));

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

	// generic scratch variables for vtSerial.ReadLong/ReadFloat
	int readval;
	float readfloat;

	switch ( commandByte ) {

	case '?':    // ?  = Dump values to serial for debugging
		Serial.println( char( commandByte ) );
		dumpData();
		showCLI();
		// blink the LED to indicate we got a valid command
		// just a quick blink so as not to slow the CLI down too much when cycling
		blinkLED( LED, 0, 1 ); //one quick
		break;
		
	case 'B':    // B  = Set the debounce timeout value (ms)
		Serial.println( char( commandByte ) );
		readval = 0; // Set the value to be read deliberately out of range.
		do {
			processLed();
			termSetFor( TERM_INPUT );
			Serial.print(F(" -> Enter debounce timeout [1-20ms]: "));
			termSetFor( TERM_DEFAULT );
			readval = vtSerial.ReadLong();       // read integer
			Serial.println("");
		} while ( readval < 1 || readval > maxDebounceTimeout );
		sensorDebounceTimeout = readval;
		termSetFor( TERM_CONFIRM );
		Serial.print(F("Debounce Timeout: "));
		Serial.print( sensorDebounceTimeout );
		Serial.println(F("ms"));
		termSetFor( TERM_DEFAULT );
		showCLI();
		blinkLED( LED, 0, 1 );
		break;

	case 'R':    // R  = Set the rendezvous timeout value (1-255ms)
		Serial.println( char( commandByte ) );
		for ( i = 0; i < numSensors; i++ ) {
			readval = 0; // Set the value to be read deliberately out of range.
			do {
				processLed();
				termSetFor( TERM_INPUT );
				Serial.print(F(" -> Enter rendezvous timeout "));
				Serial.print( i );
				Serial.print(F(" [1-255ms]: "));
				termSetFor( TERM_DEFAULT );
				readval = vtSerial.ReadLong();       // read integer
				Serial.println("");
			} while ( readval < 1 || readval > 255 );
			sensorRendezvousTimeout[i] = readval;
			termSetFor( TERM_CONFIRM );
			Serial.print(F("Rendezvous Timeout "));
			Serial.print( i );
			Serial.print(F(" : "));
			Serial.print( sensorRendezvousTimeout[i] );
			Serial.println(F("ms"));
			termSetFor( TERM_DEFAULT );
		}
		showCLI();
		blinkLED( LED, 0, 1 );
		break;

	case 'T':    // T  = Set the strike timeout values (1-2500ms)
		Serial.println( char( commandByte ) );
		for ( i = 0; i < numSensors; i++ ) {
			readval = 0; // Set the value to be read deliberately out of range.
			do {
				processLed();
				termSetFor( TERM_INPUT );
				Serial.print(F(" -> Enter strike timeout "));
				Serial.print( i );
				Serial.print(F(" [1-2500ms]: "));
				termSetFor( TERM_DEFAULT );
				readval = vtSerial.ReadLong();       // read integer
				Serial.println("");
			} while ( readval < 1 || readval > 2500 );
			sensorStrikeTimeout[i] = ( ( readval / 10) * 10 ); //force to 10ms multiples
			termSetFor( TERM_CONFIRM );
			Serial.print(F("Strike Timeout "));
			Serial.print( i );
			Serial.print(F(" : "));
			Serial.print( sensorStrikeTimeout[i] );
			Serial.println(F("ms"));
			termSetFor( TERM_DEFAULT );
		}
		showCLI();
		blinkLED( LED, 0, 1 );
		break;	
		
	case 'M':    // M  = Set (override) the sensor minimum delta time (ms)
		Serial.println( char( commandByte ) );
		readval = 0; // Set the value to be read deliberately out of range.
		do {
			processLed();
			termSetFor( TERM_INPUT );
			Serial.print(F(" -> Enter minimum sensor delta time [1-100ms]: "));
			termSetFor( TERM_DEFAULT );
			readval = vtSerial.ReadLong();       // read integer
			Serial.println("");
		} while ( readval < 1 || readval > maxBellMinDelta );
		bellMinDelta = readval;
		// recalculate the backstroke cutoff point since one of the components changed
		backstrokeCutoffDelta = speedFactor * bellMinDelta;
		termSetFor( TERM_CONFIRM );
		Serial.print(F("Minimum Delta Time: "));
		Serial.print( bellMinDelta );
		Serial.println(F("ms"));
		Serial.print(F("Backstroke CutOff Delta (ms): "));
		Serial.println( backstrokeCutoffDelta );		
		termSetFor( TERM_DEFAULT );
		showCLI();
		blinkLED( LED, 0, 1 );
		break;
		
	case 'F':    // F  = Set the speed factor
		Serial.println( char( commandByte ) );
		readfloat = 0; // Set the value to be read deliberately out of range.
		do {
			processLed();
			termSetFor( TERM_INPUT );
			Serial.print(F(" -> Enter speed factor (1.0-10.0): "));
			termSetFor( TERM_DEFAULT );
			readfloat = vtSerial.ReadFloat();       // read float
			Serial.println("");
		} while ( readfloat < 1 || readfloat > maxSpeedFactor );
		// A factor <1 doesn't make sense, the bell would have to speed up when lowered
		speedFactor = readfloat;
		// recalculate the backstroke cutoff point since one of the components changed
		backstrokeCutoffDelta = speedFactor * bellMinDelta;
		termSetFor( TERM_CONFIRM );
		Serial.print(F("Speed factor: "));
		Serial.println( speedFactor );
		Serial.print(F("Backstroke CutOff Delta (ms): "));
		Serial.println( backstrokeCutoffDelta );
		termSetFor( TERM_DEFAULT );
		showCLI();
		blinkLED( LED, 0, 1 );
		break;
		
	case 'W':    // W  = Set (toggle) wheel direction 
		Serial.println( char( commandByte ) );
		if ( bellDirection == 0 ) {
			// Toggle to 1
			bellDirection = 1;
		}
		else
		{
			// Toggle to 0
			bellDirection = 0;
		}
		termSetFor( TERM_CONFIRM );
		Serial.print(F("Direction "));
		Serial.println( sensorChar[ bellDirection ] );
		termSetFor( TERM_DEFAULT );
		showCLI();
		blinkLED( LED, 0, 1 );
		break;
		
	case 'S':    // S  = Save settings to EEPROM as bytes
		Serial.println( char( commandByte ) );
		saveToEEPROM();
		showCLI();
		// blink the LED to indicate we got a valid command
		blinkLED( LED, 0, 1 );
		break;

	case 'P':    // P  = Set the serial port speed
		Serial.println( char( commandByte ) );
		readval = 9; // Set the value to be read deliberately out of range. (0 is valid value)
		do {
			processLed();
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
		if ( EEPROM.read( 5 ) != byte( serialSpeed ) ) {
			EEPROM.write( 5, byte( serialSpeed ) ); // Save serialSpeed to location 5
		}
		Serial.println(F("Serial speed set in EEPROM, please reboot sensor"));
		termSetFor( TERM_DEFAULT );
		showCLI();
		// blink the LED to indicate we got a valid command
		blinkLED( LED, 0, 1 ); 
		break;

	case 'o':    // o = Simulate short button press
		Serial.println( char( commandByte ) );
		processButton( BUTTON_SHORT );
		showCLI();
		break;

	case 'O':    // O = Simulate long button press
		Serial.println( char( commandByte ) );
		processButton( BUTTON_LONG );
		showCLI();
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
			blinkLED( LED, 0, 1 );
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
					processLed();
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
			blinkLED( LED, 0, 1 ); //one quick
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
			blinkLED( LED, 0, 1 );
			// Don't change the debug level here, remember it in case debugging is turned back on
		} //debugMode
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
			blinkLED( LED, 0, 1 ); //one quick
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
		blinkLED( LED, 0, 1 ); //one quick
		break;
		
	case 'H':    // H  = Help
		Serial.println( char( commandByte ) );
		showCLIHelp();
		showCLI();
		// just a quick blink so as not to slow the CLI down too much
		blinkLED( LED, 0, 1 ); //one quick
		break;
		
	default:
		// We don't know what this is, echo it as a char, flash the LED, and throw the data away.
		// Note than any other bytes that were read into the buffer are never looked at either.
		Serial.println( char( commandByte ) );
		showCLI();
		blinkLED( LED, 3, 0 );
		
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

	Serial.println(F(" -> [B] - Set debounce timer (1ms->20ms)"));
	Serial.println(F(" -> [R] - Set rendezvous timers (1ms->255ms)"));
	Serial.println(F(" -> [T] - Set strike delay timers (1ms->2500ms)"));
	Serial.println(F(" -> [W] - Set wheel handstroke direction"));
	Serial.println(F(" -> [M] - Set minimum sensor delta time (1ms->100ms)"));
	Serial.println(F(" -> [F] - Set speed factor for backstroke suppression"));
	Serial.println(F(" -> [S] - Save settings in EEPROM"));
	Serial.println(F(" -> [P] - Set serial port speed in EEPROM"));
	Serial.println(F(" -> [o] - Simulate short prog button press"));
	Serial.println(F(" -> [O] - Simulate long prog button press"));
	Serial.println(F(" -> [D] - Turn debug mode ON or change debug flags"));
	Serial.println(F(" -> [d] - Turn debug mode OFF"));
	Serial.println(F(" -> [0-9] - Print debug markers (debug mode only)"));
	Serial.println(F(" -> [L] - Display debug levels help text (debug mode only)"));
	Serial.println(F(" -> [H] - Display this help text"));
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
void printMask( word thisMask, int places )
{
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
boolean toggleMaskBit( word *thisMask, int thisBit, int maxBits )
{
	if ( thisBit >= 0 && thisBit < maxBits ) {
		bitWrite( *thisMask, thisBit, ( bitRead ( *thisMask, thisBit ) ^ 1 ));
		return true;
	}
	else
	{
		return false;
	}
}

#endif


