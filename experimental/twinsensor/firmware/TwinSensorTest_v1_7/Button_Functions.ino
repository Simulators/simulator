/*
Twin Sensor Test v1.7 Beta
Button functions.

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
*                                    Function scanButton()                                *
*********************************************************************************************
*/

/*
Read the state of the mode change button, and determine the length of the button press.
Returns:
	0 - No press
	1 - Short press (up to shortButtonPressTime)
	2 - Long press (more than shortButtonPressTime)
	99 - Error (shorter than buttonMinimumPressTime)
	98 - Error (addition press within buttonGuardTime)

This function is called on every iteration of loop(), and fed into processButton().
*/

int scanButton(void) {

	if (digitalRead( progButton ) == HIGH) {
		//the button is not pressed
		if ( !buttonPressPending ) {
			//false = nothing happening, bail out as quickly as possible
			return 0;
		}
		else
		{
			//press pending == true, the button just came up
			buttonPressPending = false;
			buttonPressEndTime = millis();
			//how long was the press?
			buttonDuration = buttonPressEndTime - buttonPressStartTime;

#ifdef USE_ATMEGA382P

			if ( debugMode && isDebugFlagSet( DEBUG_BUTTON ) ) {
				Serial.print(F("Button duration: "));
				Serial.println( buttonDuration );
			}

#endif

			if ( buttonDuration < buttonMinimumPressTime ) {
				//too short, return error value
				return BUTTON_TOO_SHORT;
			}
			else if ( buttonDuration <= buttonShortPressTime ) {
				//not more than the maximum length of a short press, return short press 1
				return BUTTON_SHORT;
			}
			else {
				//more than maximum length of a short press, return long press 2
				return BUTTON_LONG;
			}
		} 
	}
	else
	{
		//The button is down, did it only just go down?
		if ( buttonPressPending ) {
			//true = we already saw the button go down
			//do nothing - continue to wait for button to be released
			return 0;
		}
		else
		{
			//false, we noticed that the button just went down
			//is it too soon for another press?
			if ( millis() > buttonPressEndTime + buttonGuardTime ) {
				buttonPressPending = true;
				buttonPressStartTime = millis();
				return 0;
			}
			else
			{
				//too soon after the last press, return error
				buttonPressPending = false;
				return BUTTON_TOO_EARLY;
			}
		}
	}
}

/*
*********************************************************************************************
*                                   Function processButton()                                *
*********************************************************************************************
*/

/*
Takes the output from scanButton() and does something with it.
A short press enables direction learning or cancels all learning, a long press toggles enables
delta time learning (a short press turns it off. Note that the two learning modes are mutually
exclusive, so enabling one cancels the other.
*/

void processButton(int button) {
	
	unsigned long tempDeltaTime; //temp scratch variable for EEPROM.get()
	
	switch(button) {
		
	case 0:
		//nothing to see here, bail out immediately
		break;
		
	case BUTTON_SHORT:	
		// Turn on learnDirection, or cancel all learning modes and turn off the LED
		if ( learnDirection || learnMinDelta ) {
			// a learning mode is enabled, so cancel both and turn off the blinking LED
			// Note that this means a short press will cancel learnMinDelta WITHOUT SAVING
			// VALUES, i.e. it cancels the process. This is consistent with learnDirection
			// which is also cancelled without change by a short press.
			learnDirection = false;
			learnMinDelta = false;
			ledBlinkMode( false, 0 );
			// (bellDirection is saved to EEPROM in the setDirection() function)
			

#ifdef USE_ATMEGA382P

			if ( debugMode && isDebugFlagSet( DEBUG_BUTTON ) ) {
				Serial.println(F("Learning OFF"));
			}

#endif			

		}
		else 
		{
			// no learning mode enabled, so enable direction learning, when true blink LED fast
			learnDirection = true;
			learnMinDelta = false; //mutually exclusive, should never be enabled here anyway
			ledBlinkMode( true, 100 );

#ifdef USE_ATMEGA382P

			if ( debugMode && isDebugFlagSet( DEBUG_BUTTON ) ) {
				Serial.println(F("Direction Learning ON"));
			}

#endif

		} //learnDirection || learnMinDelta
		break;
		
	case BUTTON_LONG:
		// Turn learnMinDelta on if it's off, cancelling learnDirection, when true blink LED slowly
		// Save the bellMinDelta to EEPROM if it's changed on termination of learnMinDelta
		if ( learnMinDelta ) {
			// Turn learnMinDelta off, saving EEPROM values if necessary
			// first check if we need to update the bellMinDelta time from data gathered
			// while learnMinDelta was enabled.
			bellMinDelta = trackedMinDelta;
			// recalculate the backstroke cutoff point since one of the components changed
			backstrokeCutoffDelta = speedFactor * bellMinDelta;
			// NB this uses EEPROM locations 7-10 inclusive (4 bytes)
			EEPROM.get( 7, tempDeltaTime );
			if ( tempDeltaTime != bellMinDelta ) {
				EEPROM.put( 7, bellMinDelta );
			}
			
#ifdef USE_ATMEGA382P

			if ( debugMode && isDebugFlagSet( DEBUG_BUTTON ) ) {
				Serial.print(F("Bell Min Delta now "));
				Serial.println( bellMinDelta );
			} //debugMode
			
#endif

			learnMinDelta = false;
			ledBlinkMode( false, 0 );
		}		
		else
		{
			// Turn on learnMinDelta, cancel learnDirection, slow blink the LED
			learnMinDelta = true;
			// reset the tracker value to an infeasibly large value
			trackedMinDelta = 10000; //10s
			learnDirection = false; //mutually exclusive
			ledBlinkMode( true, 800 );
			
#ifdef USE_ATMEGA382P
			
			if ( debugMode && isDebugFlagSet( DEBUG_BUTTON ) ) {
				Serial.println(F("Delta Learning ON"));
			}
			
#endif

		} //learnMinDelta
		break;

#ifdef USE_ATMEGA382P

	case BUTTON_TOO_SHORT:
		if ( debugMode && isDebugFlagSet( DEBUG_BUTTON ) ) {
			Serial.println(F("Error: Button too short"));
		}
		break;

	case BUTTON_TOO_EARLY:
		if ( debugMode && isDebugFlagSet( DEBUG_BUTTON ) ) {
			Serial.println(F("Error: Button too early"));
		}
		break;
		
	default:
		if ( debugMode && isDebugFlagSet( DEBUG_BUTTON ) ) {
			Serial.print(F("Error: "));
			Serial.println( button );
		}
		
#endif
		//no other button values currently make sense
		
	}	// switch buttonValue
}

/*
*********************************************************************************************
*                                   Function setDirection()                                 *
*********************************************************************************************
*/

/*
Passed the value of a sensor (0 or 1), sets the value of the bellDirection flag appropriately,
saves the value to EEPROM, disables the flashing LED, and disables learnDirection mode.
- bellDirection==0 means sensor A triggers first at handstroke.
- bellDirection==1 means sensor B triggers first at handstroke.
*/

void setDirection( byte sensorValue ) {
	
	// sanity check that function was called in the right place
	if ( learnDirection && ( sensorValue == 0 || sensorValue == 1 ) ) {
		// direction learning mode is enabled, and we have a sane sensor value
		bellDirection = sensorValue;
		learnDirection = false;
		ledBlinkMode( false, 0 );
		
		if ( EEPROM.read( 6 ) != bellDirection ) {
			EEPROM.write( 6, byte( bellDirection ) );
		}
		
#ifdef USE_ATMEGA382P

		if ( debugMode && isDebugFlagSet( DEBUG_BUTTON ) ) {
			Serial.print(F("Direction "));
			Serial.println( sensorChar[ bellDirection ] );
		} //debugMode

#endif
		
	} //learnDirection

}

/*
*********************************************************************************************
*                                  Function trackMinDelta()                                 *
*********************************************************************************************
*/

/*
Passed the delta time for a swing, keeps track on the rolling minimum value (i.e. maximum
speed of the bell). 
*/

void trackMinDelta(long deltaTime) {
	
	//trackedMinDelta is a global variable, so its updated value is preserved across calls 
	
	// sanity check that function was called in the right place
	if ( learnMinDelta ) {
		if ( deltaTime < trackedMinDelta ) {
			// update the rolling minimum value
			trackedMinDelta = deltaTime;
			
#ifdef USE_ATMEGA382P
			
			if ( debugMode && isDebugFlagSet( DEBUG_BUTTON ) ) {
				Serial.print(F("Tracked delta  "));
				Serial.println( trackedMinDelta );
			} //debugMode

#endif

		} //deltaTime

	} //learnMinDelta

}
