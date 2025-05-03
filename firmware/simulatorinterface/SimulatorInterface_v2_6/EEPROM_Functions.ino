/*
Simulator Interface v2.6
EEPROM Functions

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
*                                 Function saveToEEPROM()                                   *
*********************************************************************************************
*/

// Save the following EEPROM locations:
// 	Location  17    : Simulator Type (A,B,R,X)
// 	Location  18    : Number of channels (bell pins) active & to be scanned
// 	Location  19    : Debounce Timer (in ms)
// 	Location  21    : enabledSensorMask (lo byte)
// 	Location  22    : enabledSensorMask (hi byte)
// 	Location  23    : debugBellMask (lo byte)
// 	Location  24    : debugBellMask (hi byte)
//  Location  25    : applyDelayTimers (boolean)

// Don't save the following:
// 	Locations 12-15 : Reserved for future Bells 13-16 Delay Timers
// 	Location  16    : Accidental Status (#,b) - Not supported yet
// 	Location  20	: Serial port speed - Saved by the P option and requires a reset

//  Save under certain circumstances: 
// 	Locations 0-11  : Bells 1-12 Delay Timers (in cs) - Saved when received

void saveToEEPROM( void )
{
	termSetFor( TERM_CONFIRM );
	
	// Only save the byte if different from the current value, to reduce EEPROM write wear	

	// Only save the delay timers here if delays are NOT being applied by the interface.
	// If delays are being applied by the interface, then the timers are saved when received
	// from the simulator software. When delays are not being applied by the interface, the
	// delay timers are used as Guard Timer, so don't get received from the PC, but do need
	// to be saved.
	if( ! applyDelayTimers ) {
		int i;
		for ( i = 0; i < 12; i++ ) {
			if ( EEPROM.read(i) * 10 != bellStrikeDelay[i] ) {
				EEPROM.write( i, ( bellStrikeDelay[i] / 10 ) );
			}
		}
		Serial.println(F("Delay timers saved to EEPROM"));
	}					

	if ( EEPROM.read( 17 ) != byte( simulatorType ) ) {
		EEPROM.write( 17, byte( simulatorType ) ); // Save simulatorType (char) to location 17
	}
	Serial.println(F("Simulator type saved to EEPROM"));
	
	if ( EEPROM.read( 18 ) != byte( numChannels ) ) {
		EEPROM.write( 18, byte( numChannels ) ); // Save numChannels (int) to location 18
	}
	Serial.println(F("Active channels saved to EEPROM"));
	
	if ( EEPROM.read( 19 ) != byte( bellDebounceDelay ) ) {
		EEPROM.write( 19, byte( bellDebounceDelay ) ); // Save bellDebounceDelay to location 19
	}
	Serial.println(F("Debounce timer saved to EEPROM"));
	
	if ( EEPROM.read(21) != lowByte( enabledSensorMask ) ) {
		EEPROM.write( 21, lowByte( enabledSensorMask ) );
	}
	if ( EEPROM.read(22) != highByte( enabledSensorMask ) ) {
		EEPROM.write( 22, highByte( enabledSensorMask ) );
	}
	Serial.println(F("Enabled sensors saved to EEPROM"));
	
	if ( debugMode ) {
		if ( EEPROM.read(23) != lowByte( debugBellMask ) ) {
			EEPROM.write( 23, lowByte( debugBellMask ) );
		}
		if ( EEPROM.read(24) != highByte( debugBellMask ) ) {
			EEPROM.write( 24, highByte( debugBellMask ) );
		}
		Serial.println(F("Debug mask saved to EEPROM"));
	}
	
	if ( EEPROM.read( 25 ) != byte( applyDelayTimers ) ) {
		EEPROM.write( 25, byte( applyDelayTimers ) ); // Save applyDelayTimers to location 25
	}
	Serial.println(F("Apply delay timers flag saved to EEPROM"));
	
	termSetFor( TERM_DEFAULT );

}

/*
*********************************************************************************************
*                                Function loadFromEEPROM()                                  *
*********************************************************************************************
*/

// Load the following EEPROM locations:
// 	Locations 0-11  : Bells 1-12 Delay Timers (in cs)
// 	Location  17    : Simulator Type (A,B,R,V,X)
// 	Location  18    : Number of channels (bell pins) active & to be scanned
// 	Location  19    : Debounce Timer (in ms)
// 	Location  20    : Serial port speed (as an index into serialSpeeds[])
// 	Location  21    : enabledSensorMask (lo byte)
// 	Location  22    : enabledSensorMask (hi byte)
//	Location  23    : debugBellMask (lo byte)
// 	Location  24    : debugBellMask (hi byte)
//  Location  25    : applyDelayTimers (boolean)

// Don't load the following:
// 	Locations 12-15 : Reserved for future Bells 13-16 Delay Timers
// 	Location  16    : Accidental Status (#,b) - Not supported yet


void loadFromEEPROM( void )
{
	// No point printing messages, the serial port isn't started yet...

	// generic loop counter
	int i;
	
	// Initialise the apply delay timers flag from EEPROM. Do this first so we can use it later in this function	
	applyDelayTimers = boolean( EEPROM.read(25) );
	// Trying to set a sane value doesn't work, as any non-zero value is boolean TRUE!
	
	for ( i = 0; i < 12; i++ ) {
		// Load the strike delays from EEPROM, converting the cs byte value in EEPROM to ms.
		// Hardcoded 12 because the MBI protocol requires 12 values.
		bellStrikeDelay[i] = long( EEPROM.read(i) ) * 10;
	}

	// initialise the simulator type from EEPROM. If the value is not in the valid list, set
	// it to A for Abel.
	simulatorType = char( EEPROM.read(17) );
	// but the EEPROM value may not be set to a sensible value! Seed a sane value.
	if ( ! checkValidSimulatorType( simulatorType ) ) {
		simulatorType = 'A';
	}

	// initialise the number of active channels from EEPROM. If the value is <1 or >max, set
	// it to the maximum (currently 12). Cast the byte value read into an int.
	numChannels = int( EEPROM.read(18) );
	// but the EEPROM value may not be set to a sensible value! Seed a sane value.
	if ( numChannels < 1 || numChannels > maxNumChannels ) {
		numChannels = maxNumChannels;
	}

	// initialise the debounce timer from EEPROM. If the value is <1 or >20, set it to default.
	// Cast the byte value read into a long so we can add it to millis().
	bellDebounceDelay = long( EEPROM.read(19) );
	// but the EEPROM value may not be set to a sensible value! Seed a sane value.
	if ( bellDebounceDelay < 1 || bellDebounceDelay > maxDebounceDelay ) {
		bellDebounceDelay = defaultDebounceDelay;
	}

	// initialise the serial port speed from EEPROM. If the value is <1 or >2, set it to
	// default. Cast the byte value read into a long for Serial.begin.
	serialSpeed = int( EEPROM.read(20) );
	// but the EEPROM value may not be set to a sensible value! Seed a sane value.
	if ( serialSpeed < 0 || serialSpeed > 2 ) {
		serialSpeed = defaultSerialSpeed;
	}
	
	// Initialise the enabled sensor mask from EEPROM, assembing the word from the high and
	// low bytes.
	enabledSensorMask = word( EEPROM.read(22), EEPROM.read(21) ); //hi, lo
	// but the EEPROM value may not be set to a sensible value! Seed a sane value.
	if ( enabledSensorMask < 0 || enabledSensorMask > 4095 ) {
		enabledSensorMask = 4095; // first 12 bits all set on
	}

	// Initialise the debug bell mask from EEPROM, assembing the word from the high and
	// low bytes.	
	debugBellMask = word( EEPROM.read(24), EEPROM.read(23) ); //hi, lo
	// but the EEPROM value may not be set to a sensible value! Seed a sane value.
	if ( enabledSensorMask < 0 || enabledSensorMask > 4095 ) {
		enabledSensorMask = 4095; // first 12 bits all set on
	}

}
