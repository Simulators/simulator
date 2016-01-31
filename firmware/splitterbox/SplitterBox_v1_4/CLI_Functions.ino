/*
Splitter Box v1.4 Beta
Serial CLI Functions

Copyright 2015-2016 Andrew J Instone-Cowie.

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
*                               Function indexToPortName()                                  *
*********************************************************************************************
*/

//Find the USB port name (A-F) for the supplied index number (0-6).
//Used by the CLI to display non-numeric port names (letter A-F,X).

char indexToPortName( int portindex )
{
	if( portindex < numPorts ) {
		return(portNames[portindex]);
	}
	else
	{
		return('X'); //error value
	}
}

/*
*********************************************************************************************
*                               Function portNameToIndex()                                  *
*********************************************************************************************
*/

//Find the USB port index number (0-5) for the supplied name (letter A-F).
//Used by the CLI to convert a port name to its index position.

int portNameToIndex( char portname )
{
	int found = -1;
	int i;
	for ( i = 0; i < numPorts; i++) {
		if (portname == portNames[i]) {
			found = i;
			break;
		}
	}
	return(found); //-1 on error
}

/*
*********************************************************************************************
*                               Function signalNameToIndex()                                  *
*********************************************************************************************
*/

//Find the Targets[] index number (0-20) for the supplied signal name (1-90ETABCDWXYZ).
//Used by the CLI to convert a signal name to its index position.

int signalNameToIndex( char signalname )
{
	int found = -1;
	int i;
	for ( i = 0; i < numTargets; i++) {
		if (signalname == Targets[i].inputChar) {
			found = i;
			break;
		}
	}
	return(found); //-1 on error
}

/*
*********************************************************************************************
*                            Function checkValidMappingChar()                               *
*********************************************************************************************
*/

//Check that the new mapping character supplied by the user (or found in EEPROM) is valid,
//by seeing if it exists in the list validMappedChars[].

int checkValidMappingChar( char testchar)
{

	//The mapped char should be listed in the array validMappedChars[]
	int i;
	//scan the validMappedChars[]
	for ( i = 0; i < sizeof( validMappedChars ) - 1; i++ ) {
		if( testchar == validMappedChars[i] ) {
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
*                              Function showActiveMapping()                                 *
*********************************************************************************************
*/

//Show the active mapping for a given index value in Targets[].

void showActiveMapping( int targetindex )
{
	portUSB[0]->println(F("Active Mapping:"));
	portUSB[0]->print(F(" - Signal:\t"));
	portUSB[0]->println( Targets[targetindex].inputChar );
	if( debugMode ) {
		//Dump the raw port indexes in debug mode
		portUSB[0]->print(F(" - Index:\t"));
		portUSB[0]->println( Targets[targetindex].targetSerialPort );
	}
	portUSB[0]->print(F(" - Port:\t"));
	portUSB[0]->println( indexToPortName( Targets[targetindex].targetSerialPort) );
	portUSB[0]->print(F(" - Mapped:\t"));
	portUSB[0]->println( Targets[targetindex].mappedChar );
}

/*
*********************************************************************************************
*                                  Function dumpMapping()                                   *
*********************************************************************************************
*/

//Does for active settings what dumpEEPROM() does for EEPROM settings.

void dumpMapping( void )
{
	//loop counter
	int i;
	
	//What are the active settings?
	portUSB[0]->println(F("Active Mapping:"));

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
			portUSB[0]->print( Targets[i].targetSerialPort );
			portUSB[0]->print(F(" "));
		}
		portUSB[0]->println(""); //new line
	}
	
	//Dump the port indexes mapped to names
	portUSB[0]->print(F(" - Port:\t"));
	for ( i = 0; i < numTargets; i++ ) {
		portUSB[0]->print( indexToPortName( Targets[i].targetSerialPort) );
		portUSB[0]->print(F(" "));
	}
	portUSB[0]->println(""); //new line

	//Dump the mapped chars
	portUSB[0]->print(F(" - Mapped:\t"));
	for ( i = 0; i < numTargets; i++ ) {
		portUSB[0]->print( Targets[i].mappedChar );
		portUSB[0]->print(F(" "));
	}
	portUSB[0]->println(""); //new line

}

/*
*********************************************************************************************
*                                   Function dumpData()                                     *
*********************************************************************************************
*/

// Dump current configuration data to the USB A port.

void dumpData( void ) {

	// Position the cursor and clear the screen.
	termClear();

	// generic loop counter
	int i;
	
	// What version of software are we running?
	termSetFor( TERM_HEADING );
	portUSB[0]->print(F("Splitter Box Version: "));
	portUSB[0]->print( majorVersion );
	portUSB[0]->print(F("."));
	portUSB[0]->println( minorVersion );
	termSetFor( TERM_DEFAULT );

	// What are the active mappings?
	dumpMapping();

	// What are the EEPROM mappings?
	dumpEEPROM();

	// Show debug mode status 
	portUSB[0]->print(F("Debug Mode: "));
	if ( debugMode ) { 
		portUSB[0]->println(F("ON"));
	}
	else
	{
		portUSB[0]->println(F("OFF"));
	}

	portUSB[0]->print(F("Free Memory: "));
	portUSB[0]->println( freeMemory() );  

	#ifdef USE_CRO
	portUSB[0]->print(F("CRO Timing Pin Enabled: "));
	portUSB[0]->println( CROpin );  
	#endif
}

/*
*********************************************************************************************
*                                   Function showCLI()                                      *
*********************************************************************************************
*/

// Display the CLI prompt to the USB A serial port.
void showCLI( void ) {

	// If you call showCLI(), you need to supply the carriage return later, e.g. after
	// you have echoed the keypress.

	// Set the terminal modes for the CLI.
	termSetFor( TERM_CLI );

	// Print the the CLI
	portUSB[0]->print(F(" : M/L/S/D/d/H/? "));

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

	// This function is passed the incoming byte from the USB A serial buffer.

	// generic loop counter
	int i;

	// generic scratch variable for vtSerial.ReadLong
	int readval;

	switch ( commandByte ) {

	case '?':    // ?  = Dump values to USB A for debugging
		portUSB[0]->println( char( commandByte ) );
		dumpData();
		showCLI();
		break;

	case 'M':    // M  = Set the mapping
		// prompt the user for an inbound signal
		// show the current port and map for that signal
		// prompt for a new port (check validity)
		// prompt for a new mapped char (check validity)
		// update the active map for that signal
		
		portUSB[0]->println( char( commandByte ) );
		
		char readSignal;
		int signalIndex;
		readSignal = 0; //nothing entered
		termSetFor( TERM_INPUT );
		// Prompt the user for an inbound signal to configure
		portUSB[0]->print(F(" -> Inbound signal [1-90ETABCDWXYZ]: "));
		termSetFor( TERM_DEFAULT );
		while (readSignal == 0) {
			if ( portUSB[0]->available() ) {
				readSignal = toupper(portUSB[0]->read());
				portUSB[0]->println(readSignal);
			}
			processLeds(); //while we are waiting for input
		}
		signalIndex = signalNameToIndex(readSignal);
		
		// If it's a sane signal value, show the current active mapping
		if( signalIndex != -1 ) {
			//What are the active settings?
			showActiveMapping(signalIndex);
			
			// prompt for a new port (check validity)
			char readNewPort;
			int newPortIndex;
			readNewPort = 0; //nothing entered
			termSetFor( TERM_INPUT );
			// Prompt the user for a new target USB port
			portUSB[0]->print(F(" -> New USB Port [A-F,-]: "));
			termSetFor( TERM_DEFAULT );
			while (readNewPort == 0) {
				if ( portUSB[0]->available() ) {
					readNewPort = toupper(portUSB[0]->read());
					portUSB[0]->println(readNewPort);
				}
				processLeds(); //while we are waiting for input
			}
			
			newPortIndex = portNameToIndex(readNewPort);
			
			if( newPortIndex != -1 ) {
				if( debugMode ) {
					portUSB[0]->print(F("Valid new port: "));
					portUSB[0]->println(readNewPort);
				}
				
				// prompt for a new mapped char (check validity)	   
				char readNewMapping;
				readNewMapping = 0; //nothing entered
				termSetFor( TERM_INPUT );
				// Prompt the user for a new target mapped character
				portUSB[0]->print(F(" -> New Mapping [1-90ETABCDWXYZ]: "));
				termSetFor( TERM_DEFAULT );
				while (readNewMapping == 0) {
					if ( portUSB[0]->available() ) {
						readNewMapping = toupper(portUSB[0]->read());
						portUSB[0]->println(readNewMapping);
					}
					processLeds(); //while we are waiting for input
				}
				
				if( checkValidMappingChar(readNewMapping) ) {
					if( debugMode ) {
						portUSB[0]->print(F("Valid new mapping: "));
						portUSB[0]->println(readNewMapping);
					}
					
					//update the mapping entry in Targets[].
					Targets[signalIndex].targetSerialPort = newPortIndex;
					Targets[signalIndex].mappedChar = readNewMapping;
					termSetFor( TERM_CONFIRM );
					portUSB[0]->println(F("Active mapping updated"));
					termSetFor( TERM_DEFAULT );
					showActiveMapping(signalIndex);
				}
				else
				{
					termSetFor( TERM_DEBUG );
					portUSB[0]->println(F("Invalid mapping"));
					termSetFor( TERM_DEFAULT );
				}
				
			} // if newPortIndex !=1
			else
			{
				termSetFor( TERM_DEBUG );
				portUSB[0]->println(F("Invalid port"));
				termSetFor( TERM_DEFAULT );
			}	
			
		} // if signalIndex != -1  
		else
		{
			termSetFor( TERM_DEBUG );
			portUSB[0]->println(F("Invalid signal"));
			termSetFor( TERM_DEFAULT );
		}	
		
		showCLI();
		break; 
		
	case 'L':    // L  = Load settigs from EEPROM
		portUSB[0]->println( char( commandByte ) );
		
		if ( loadFromEEPROM() ) {
			termSetFor( TERM_CONFIRM );
			portUSB[0]->println(F("Settings loaded from EEPROM"));
		}
		else
		{
			termSetFor( TERM_DEBUG );
			portUSB[0]->println(F("Invalid EEPROM data"));
		}
		termSetFor( TERM_DEFAULT );
		showCLI();
		break;
		
	case 'S':    // S  = Save settings to EEPROM as bytes
		portUSB[0]->println( char( commandByte ) );
		saveToEEPROM();
		termSetFor( TERM_CONFIRM );
		portUSB[0]->println(F("Settings saved to EEPROM"));
		termSetFor( TERM_DEFAULT );
		showCLI();
		break;
		
	case 'D':    // D  = Set debug mode ON
		portUSB[0]->println( char( commandByte ) );
		// Turn on debug mode
		debugMode = true;
		termSetFor( TERM_DEBUG );
		portUSB[0]->println(F("Debug Mode ON"));
		termSetFor( TERM_DEFAULT );
		showCLI();
		break;
		
	case 'd':    // d  = Set debug mode OFF
		portUSB[0]->println( char( commandByte ) );
		debugMode = false;
		termSetFor( TERM_DEBUG );
		portUSB[0]->println(F("Debug Mode OFF"));
		termSetFor( TERM_DEFAULT );
		showCLI();
		break;

	case 'H':    // H  = Help
		portUSB[0]->println( char( commandByte ) );
		showCLIHelp();
		showCLI();
		break;
		
	default:
		// So this isn't a valid CLI command, echo it as a char, and throw the data away.
		portUSB[0]->println( char( commandByte ) );
		showCLI();
		
	} //switch commandByte

}

/*
*********************************************************************************************
*                                 Function showCLIHelp()                                    *
*********************************************************************************************
*/

// Display the CLI help text.
void showCLIHelp(void) {

	// Position the cursor and clear the screen.
	termClear();

	// Keep it short, this is all static literal data!
	termSetFor( TERM_HEADING );
	portUSB[0]->println(F("CLI Commands:"));
	termSetFor( TERM_DEFAULT );
	portUSB[0]->println(F(" -> [M] - Configure USB port mappings"));
	portUSB[0]->println(F(" -> [L] - Load settings from EEPROM"));
	portUSB[0]->println(F(" -> [S] - Save settings to EEPROM"));
	portUSB[0]->println(F(" -> [D] - Turn debug mode ON"));
	portUSB[0]->println(F(" -> [d] - Turn debug mode OFF"));
	portUSB[0]->println(F(" -> [H] - Display this help text"));
	portUSB[0]->println(F(" -> [?] - Display current settings"));

}
