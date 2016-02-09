/*
One Bell Simulator Interface v1.3 Beta
EEPROM Functions

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
*                                 Function saveToEEPROM()                                   *
*********************************************************************************************
*/

// Save the following EEPROM locations:
// 	Location  17    : Simulator Type (A,B,R,X)
// 	Location  19    : Debounce Timer (in ms)

// Don't save the following (mostly N/A to One Bell Interface):
// 	Locations 0-11  : Bells 1-12 Delay Timers (in cs) - Saved when received
// 	Locations 12-15 : Reserved for future Bells 13-16 Delay Timers
// 	Location  16    : Accidental Status (#,b) - Not supported yet
// 	Location  18    : Number of channels (bell pins) active & to be scanned
// 	Location  21    : enabledSensorMask (lo byte)
// 	Location  22    : enabledSensorMask (hi byte)
// 	Location  23    : debugBellMask (lo byte)
// 	Location  24    : debugBellMask (hi byte)
// 	Location  20	: Serial port speed - Saved by the P option and requires a reset

void saveToEEPROM( void )
{

	// Only save the byte if different from the current value, to reduce EEPROM write wear	

	if ( EEPROM.read( 17 ) != byte( simulatorType ) ) {
		EEPROM.write( 17, byte( simulatorType ) ); // Save simulatorType (char) to location 17
	}

	if ( EEPROM.read( 19 ) != byte( bellDebounceDelay ) ) {
		EEPROM.write( 19, byte( bellDebounceDelay ) ); // Save bellDebounceDelay to location 19
	}
	mySerial.println(F("Saved"));
	
}

/*
*********************************************************************************************
*                                Function loadFromEEPROM()                                  *
*********************************************************************************************
*/

// Load the following EEPROM locations:
// 	Locations 0-11  : Bells 1-12 Delay Timers (in cs)
// 	Location  17    : Simulator Type (A,B,R,V,X)
// 	Location  19    : Debounce Timer (in ms)

// Don't load the following (mostly N/A to One Bell Interface):
// 	Locations 12-15 : Reserved for future Bells 13-16 Delay Timers
// 	Location  16    : Accidental Status (#,b) - Not supported yet
// 	Location  18    : Number of channels (bell pins) active & to be scanned
// 	Location  20    : Serial port speed (as an index into serialSpeeds[])
// 	Location  21    : enabledSensorMask (lo byte)
// 	Location  22    : enabledSensorMask (hi byte)
//	Location  23    : debugBellMask (lo byte)
// 	Location  24    : debugBellMask (hi byte)

void loadFromEEPROM( void )
{
	// No point printing messages, the serial port isn't started yet...

	// generic loop counter
	int i;
	
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

	// initialise the debounce timer from EEPROM. If the value is <1 or >20, set it to default.
	// Cast the byte value read into a long so we can add it to millis().
	bellDebounceDelay = long( EEPROM.read(19) );
	// but the EEPROM value may not be set to a sensible value! Seed a sane value.
	if ( bellDebounceDelay < 1 || bellDebounceDelay > maxDebounceDelay ) {
		bellDebounceDelay = defaultDebounceDelay;
	}

}
