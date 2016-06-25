/*
Twin Sensor Test v1.7 Beta
EEPROM Functions

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

/*
*********************************************************************************************
*                                 Function saveToEEPROM()                                   *
*********************************************************************************************
*/

// Save the EEPROM locations.
// 0 - Strike Timeout 0
// 1 - Strike Timeout 1
// 2 - Rendezvous Timeout 0
// 3 - Rendezvous Timeout 1
// 4 - Debounce Timer
// (5 - Serial Port Speed)
// 6 - Bell Direction
// 7-10 - Bell Minimum Delta (long)
// 11-14 - Speed Factor (float)


#ifdef USE_ATMEGA382P	

void saveToEEPROM( void )
{
	float tempValue;
	long tempDeltaTime;

	termSetFor( TERM_CONFIRM );
	Serial.println(F("Saving..."));

	if ( EEPROM.read( 0 ) != byte( sensorStrikeTimeout[0] / 10 ) ) {
		EEPROM.write( 0, byte( sensorStrikeTimeout[0] / 10 ) );
	}
	Serial.println(F("Strike 0..."));
	
	if ( EEPROM.read( 1 ) != byte( sensorStrikeTimeout[1] / 10 ) ) {
		EEPROM.write( 1, byte( sensorStrikeTimeout[1] / 10 ) );
	}
	Serial.println(F("Strike 1..."));

	if ( EEPROM.read( 2 ) != byte( sensorRendezvousTimeout[0] ) ) {
		EEPROM.write( 2, byte( sensorRendezvousTimeout[0] ) );
	}
	Serial.println(F("Rendezvous 0..."));
	
	if ( EEPROM.read( 3 ) != byte( sensorRendezvousTimeout[1] ) ) {
		EEPROM.write( 3, byte( sensorRendezvousTimeout[1] ) );
	}
	Serial.println(F("Rendezvous 1..."));
	
	if ( EEPROM.read( 4 ) != byte( sensorDebounceTimeout ) ) {
		EEPROM.write( 4, byte( sensorDebounceTimeout ) );
	}
	Serial.println(F("Debounce..."));
	
	// Serial port speed is saved to location 5 by CLI P option.
	
	// bellDirection is also saved by setDirection();
	if ( EEPROM.read( 6 ) != bellDirection ) {
		EEPROM.write( 6, byte( bellDirection ) );
	}
	Serial.println(F("Direction..."));

	// NB this uses EEPROM locations 7-10 inclusive (4 bytes)
	// Bell min delta is also saved by processButton()
	EEPROM.get( 7, tempDeltaTime );
	if ( tempDeltaTime != bellMinDelta ) {
		EEPROM.put( 7, bellMinDelta );
	}
	Serial.println(F("Minimum delta..."));

	// NB this uses EEPROM locations 11-14 inclusive (4 bytes)
	EEPROM.get( 11, tempValue );
	if ( tempValue != speedFactor ) {
		EEPROM.put( 11, speedFactor );
	}
	Serial.println(F("Speed factor..."));

	Serial.println(F("Done!"));

	termSetFor( TERM_DEFAULT );

}
#endif

/*
*********************************************************************************************
*                                Function loadFromEEPROM()                                  *
*********************************************************************************************
*/

// Load the EEPROM locations.

void loadFromEEPROM( void )
{
	// No point printing messages, the serial port isn't started yet...

#ifdef USE_ATMEGA382P	

	// Load the strike timeouts from EEPROM 0 & 1, converting the cs byte value in EEPROM to ms.
	// Cast the byte value read into a long so we can add it to millis().
	sensorStrikeTimeout[0] = long( EEPROM.read(0) ) * 10;
	sensorStrikeTimeout[1] = long( EEPROM.read(1) ) * 10;
	// no need to set a sane value, any byte value up to 255 is allowed.
	
	// Load the rendevous timeouts from EEPROM 2 & 3. If the value is <1 or >255, set it to a default.
	// Cast the byte value read into a long so we can add it to millis().
	sensorRendezvousTimeout[0] = long( EEPROM.read(2) );
	sensorRendezvousTimeout[1] = long( EEPROM.read(3) );
	// no need to set a sane value, any byte value up to 255 is allowed.
	
	// initialise the debounce timer from EEPROM. If the value is <1 or >20, set it to default.
	// Cast the byte value read into a long so we can add it to millis().
	sensorDebounceTimeout = long( EEPROM.read(4) );
	// but the EEPROM value may not be set to a sensible value! Seed a sane value.
	if ( sensorDebounceTimeout < 1 || sensorDebounceTimeout > maxDebounceTimeout ) {
		sensorDebounceTimeout = defaultDebounceTimeout;
	}

	// initialise the serial port speed from EEPROM. If the value is <1 or >2, set it to
	// default. Cast the byte value read into a long for Serial.begin.
	serialSpeed = int( EEPROM.read(5) );
	// but the EEPROM value may not be set to a sensible value! Seed a sane value.
	if ( serialSpeed < 0 || serialSpeed > 2 ) {
		serialSpeed = defaultSerialSpeed;
	}
	
#endif
	
	// initialise the bell direction from  EEPROM. If the value is not 0 or 1, set it to 0.
	bellDirection = EEPROM.read(6);
	// but the EEPROM value may not be set to a sensible value! Seed a sane value.
	if ( ! ( bellDirection == 0 || bellDirection == 1 ) ) {
		bellDirection = 0; //A first = handstroke
	}	
	
	// NB this uses EEPROM locations 7-10 inclusive (4 bytes)
	EEPROM.get( 7, bellMinDelta );
	// but the EEPROM value may not be set to a sensible value! Seed a sane (but completely arbitrary) value.
	if ( bellMinDelta < 1 || bellMinDelta > maxBellMinDelta ) {
		bellMinDelta = defaultBellMinDelta;
	}	

#ifdef USE_ATMEGA382P
	
	// NB this uses EEPROM locations 11-14 inclusive (4 bytes)
	EEPROM.get( 11, speedFactor );
	// but the EEPROM value may not be set to a sensible value! Seed a sane value.
	// Speed factos <1 don't make sense.
	if ( speedFactor < 1 || speedFactor > maxSpeedFactor ) {
		speedFactor = defaultSpeedFactor;
	}	
	
#endif	
	
}
