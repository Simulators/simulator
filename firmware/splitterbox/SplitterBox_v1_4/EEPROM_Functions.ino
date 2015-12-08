/*
Splitter Box v1.4 Beta
EEPROM Functions

Copyright 2015 Andrew J Instone-Cowie.

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

//Save the Targets[] active port indexes to EEPROM locations 0-19.
//Save the Targets[] mapped characters to EEPROM locations 20-39.

void saveToEEPROM( void )
{
	//loop counter
	int i;

	for ( i = 0; i < numTargets; i++ ) {
		// Only save the byte if different from the current value, to reduce EEPROM write wear
		if ( EEPROM.read(i) != Targets[i].targetSerialPort ) {
			EEPROM.write( i, byte( Targets[i].targetSerialPort ) ); // Save index (int) as byte
		}
		
		if ( EEPROM.read(i + numTargets) != Targets[i].mappedChar ) {
			EEPROM.write( (i + numTargets), byte( Targets[i].mappedChar ) ); // Save mapped (char) as byte
		}
	}

}

/*
*********************************************************************************************
*                                  Function dumpEEPROM()                                    *
*********************************************************************************************
*/

//Dump the EEPROM port indexes from locations 0-20.
//Dump the EEPROM mapped characters from locations 20-39.

void dumpEEPROM( void )
{
	//loop counter
	int i;
	
	portUSB[0]->println(F("EEPROM Mapping:"));

	//Print the input characters for reference
	portUSB[0]->print(F(" - Signal:\t"));
	for ( i = 0; i < numTargets; i++ ) {
		portUSB[0]->print( Targets[i].inputChar );
		portUSB[0]->print(F(" "));
	}
	portUSB[0]->println(""); //new line
	
	if( debugMode ) {
		//Dump the raw port indexes in debug mode
		portUSB[0]->print(F(" - Index:\t"));
		for ( i = 0; i < numTargets; i++ ) {
			portUSB[0]->print( (int) EEPROM.read(i) );
			portUSB[0]->print(F(" "));
		}
		portUSB[0]->println(""); //new line
	}
	
	//Dump the port indexes, cast to ints and mapped to names
	portUSB[0]->print(F(" - Port:\t"));
	for ( i = 0; i < numTargets; i++ ) {
		portUSB[0]->print( indexToPortName( (int) EEPROM.read(i) ) );
		portUSB[0]->print(F(" "));
	}
	portUSB[0]->println(""); //new line

	//Dump the mapped chars, cast to chars
	portUSB[0]->print(F(" - Mapped:\t"));
	for ( i = 0; i < numTargets; i++ ) {
		portUSB[0]->print( (char) EEPROM.read(i + numTargets) );
		portUSB[0]->print(F(" "));
	}
	portUSB[0]->println(""); //new line

}

/*
*********************************************************************************************
*                                Function loadFromEEPROM()                                  *
*********************************************************************************************
*/

//Load the EEPROM port indexes from locations 0-15.
//Load the EEPROM mapped characters from locations 16-31.
//Returns true if the data was loaded OK, false if there was an error.

boolean loadFromEEPROM( void )
{
	//loop counters
	int i;
	
	//error flag - we return the error flag, so false means a problem occured
	boolean loadedOK = true;

	for ( i = 0; i < numTargets; i++ ) {
		
		//The port should be < numPorts (so 0...6 on the prototype, port 6 (disabled) is a
		//valid thing to store in EEPROM.)
		int tempPort;
		tempPort = (int) EEPROM.read(i); // Cast byte to int
		if( tempPort < numPorts ) {
			//it's a valid port number, load the value into the Targets[] array.
			Targets[i].targetSerialPort = tempPort; 
		}
		else
		{
			loadedOK = false;
			if( debugMode ) {
				//invalid port number
				portUSB[0]->print(F("Load Error: Port "));	
				portUSB[0]->println(tempPort);
			}
		}
		
		//The mapped char should be listed in the array validMappedChars[]
		char tempChar;
		tempChar = (char) EEPROM.read( i + numTargets ); // Cast byte to char
		//scan the validMappedChars[]
		if( checkValidMappingChar( tempChar )) {
			Targets[i].mappedChar = tempChar;
		}
		else
		{
			loadedOK = false;
			if( debugMode ) {
				portUSB[0]->print(F("Load Error: Mapped "));	
				portUSB[0]->println(tempChar);
			}
		}			
	}	
	
	return loadedOK;
}
