/*
  One Bell Simulator Interface v1.1 Beta
  Debug Functions
  
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
 *                                Function isDebugFlagSet()                                  *
 *********************************************************************************************
*/

// If debugging is enabled, if any of the specified bits are set in the debugLevelMask,
// return TRUE. Otherwise return FALSE. debugFlagsMask is global, so no need to pass them in
// via the function. We only call this if we are known to be in debug mode already.

// The flags parameter is either a single bit value (1/2/4/8/etc), or more than one value
// ORd together in the invocation of the function.

boolean	isDebugFlagSet( int flags ) {

  if ( debugFlagsMask & flags ) {
    // One or more of the specified flags are set.
    return true;
  }
  else
  {
    return false;
  }
	
}

/*
 *********************************************************************************************
 *                               Function printDebugFlagName()                               *
 *********************************************************************************************
*/

// Passed the numeric debug flag bit number, prints a textual representation of that debug
// flag, followed by a newline.

void printDebugFlagName( int level ) {
  
  // So this is reasonably horrible, but as I can't do F() globally,
  // this will have to do to get the text version into flash...	
  switch ( level ) {
  case 0: // DEBUG_PULSE_TIMER
    mySerial.print(F("PULSE_TIMER"));
    break;
  case 1: // DEBUG_SHOW_MISFIRES
    mySerial.print(F("SHOW_MISFIRES"));
    break;
  case 2: // DEBUG_SHOW_DEBOUNCE
    mySerial.print(F("SHOW_DEBOUNCE"));
    break;
  default: // Some other debugLevel value
    mySerial.print(F("Invalid"));
    break;
  }
		
}

/*
 *********************************************************************************************
 *                                Function printDebugMask()                                  *
 *********************************************************************************************
*/

// Print a debugMask as fixed and spaced width binary, LSB first, showing
// a fixed number of bits only
void printDebugMask( int value, int places )
{
  int i;
  for ( i = 0; i < places; i++ ) {
    // Print the value of the bits.
    mySerial.print( bitRead( value, i ) );
	mySerial.print(F(" "));
  }
  mySerial.println(""); //new line
}

/*
 *********************************************************************************************
 *                             Function printDebugFlagsSet()                                 *
 *********************************************************************************************
*/

// List the debug flags which are currently set in debugFlagsMask, as a space separated list
void printDebugFlagsSet( void ) {
  int i;
  for ( i = 0; i < maxDebugFlags; i++ ) {
    // Print the value of the bits.
	if ( bitRead( debugFlagsMask, i ) ) {
	  // The bit is set
	  mySerial.print("\t");
      printDebugFlagName( i );
	  mySerial.println("");
	}
  }
}
