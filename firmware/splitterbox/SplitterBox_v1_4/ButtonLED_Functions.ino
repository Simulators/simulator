/*
Splitter Box v1.4 Beta
Button & Signal LED Functions

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
*                                    Function ledBlinkMode()                                *
*********************************************************************************************
*/

/*
Status is signalled by a 2-pin bicolour LED, driven between a pair of output pins and showing
three aspects: Red, Green, or blinking. This function is called to set up blinking mode
(setblinking = true), and the speed (period = buttonDuration of each colour in msec). When
turning blinking off, the period parameter is not used and can be set to zero. See also the
processLeds() function.
*/

void ledBlinkMode( boolean setblinking, unsigned long period ) {
	if ( setblinking ) {
		//turn on LED blinking, start with red aspect on
		ledBlinkState = true;
		ledBlinkPeriod = period;
		digitalWrite( ledRed, HIGH );
		digitalWrite( ledGreen, LOW );
		ledNextStateChangeTime = millis() + period;
	}
	else
	{
		//turn off LED blinking
		ledBlinkState = false;
		digitalWrite( ledRed, LOW );
		digitalWrite( ledGreen, LOW );
	}
}

/*
*********************************************************************************************
*                                     Function processLeds()                                *
*********************************************************************************************
*/

/*
Process the blinking LED non-blocking in the background - call this function on each
iteration of loop(). Does nothing if the LED is not blinking (which will be the usual state),
so minimal processing overhead. If the LED is supposed to be blinking then this function
checks whether the the state is due to change.
*/

void processLeds( void ) {
	if ( ledBlinkState ) {
		//blinking is on, is it time to change state?
		if ( millis() > ledNextStateChangeTime ) {
			//toggle the LED states by reading the output pins.
			digitalWrite( ledRed, !digitalRead( ledRed ) );
			digitalWrite( ledGreen, !digitalRead( ledGreen ) );
			//update the time of the next change of state
			ledNextStateChangeTime = millis() + ledBlinkPeriod;
		}
	}
	// no else - nothing to do if the LED is not blinking
}

/*
*********************************************************************************************
*                                    Function blinkLED()                                    *
*********************************************************************************************
*/

/*
Signal statuses using the bicolour LEDs, zero or more long flashes followed
by zero or more short flashes. We can't use the serial port for debugging.
*/

void blinkLED( int led, int x, int y) {

	// buttonDuration of flashes in ms
	int longflash=250;
	int shortflash=75;

	//make sure the LEDs are turned off
	digitalWrite( ledRed, LOW );
	digitalWrite( ledGreen, LOW );

	// long flashes...
	while (x > 0) {
		digitalWrite(led, HIGH);
		delay(longflash);
		digitalWrite(led, LOW);
		delay(longflash);
		x--;
	}

	// ...then short flashes
	while (y > 0) {
		digitalWrite(led, HIGH);
		delay(shortflash);
		digitalWrite(led, LOW);
		delay(longflash); // So you can see the short flashes
		y--;
	}

	//remember to set the LED state appropriately again after calling blinkLED!

}

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

	if (digitalRead( buttonPin ) == HIGH) {
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
			if ( debugMode ) {
				portUSB[0]->print(F("Button duration: "));
				portUSB[0]->println( buttonDuration );
			}
			if ( buttonDuration < buttonMinimumPressTime ) {
				//too short, return error value
				return 99;
			}
			else if ( buttonDuration <= buttonShortPressTime ) {
				//not more than the maximum length of a short press, return short press 1
				return 1;
			}
			else {
				//more than maximum length of a short press, return long press 2
				return 2;
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
				return 98;
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
A short press toggles between MODE_PASSTHROUGH and MODE_SHARED, or exits MODE_CONFIG and set
back to MODE_PASSTHROUGH. A long press enters MODE_CONFIG.
*/

void processButton(int button) {
	
	switch(button) {
		
	case 0:
		//nothing to see here, bail out immediately
		break;
		
	case 1:		
		if (operatingMode == MODE_CONFIG || operatingMode == MODE_SHARED ) {
			//A short press in MODE_CONFIG reverts to MODE_PASSTHROUGH.
			//A short press in MODE_SHARED toggles to MODE_PASSTHROUGH.
			//Cancel blinking and set the red LED
			ledBlinkMode( false, 0 );
			digitalWrite( ledRed, HIGH );
			digitalWrite( ledGreen, LOW );
			operatingMode = MODE_PASSTHROUGH;
			if ( debugMode ) {
				portUSB[0]->println(F("Set MODE_PASSTHROUGH"));
			}
			serialFlushBuffers();
		}
		else if ( operatingMode == MODE_PASSTHROUGH ) {
			//A short press in MODE_PASSTHROUGH toggles to MODE_SHARED
			digitalWrite( ledRed, LOW );
			digitalWrite( ledGreen, HIGH );
			operatingMode = MODE_SHARED;
			if ( debugMode ) {
				portUSB[0]->println(F("Set MODE_SHARED"));
			}
			serialFlushBuffers();
		}
		break;
		
	case 2:
		if (operatingMode != MODE_CONFIG) {
			//A long press enables MODE_CONFIG
			ledBlinkMode( true, 500 );
			operatingMode = MODE_CONFIG;
			if ( debugMode ) {
				portUSB[0]->println(F("Set MODE_CONFIG"));
			}
			serialFlushBuffers();
		}
		break;
		
	default:
		if ( debugMode ) {
			portUSB[0]->print(F("Error: "));
			portUSB[0]->println( button );
		}		

		//no other button values currently make sense
		
	}	// switch buttonValue
}

/*
*********************************************************************************************
*                                 Function serialFlushBuffers()                             *
*********************************************************************************************
*/

// When changing operating modes, flush the receive buffers on the hardware serial port and
// USB A. The other USB ports are never read.

void serialFlushBuffers()
{
	while ( Serial.read() >= 0 )
	; // do nothing
	while ( portUSB[0]->read() >= 0 )
	; // do nothing
}

