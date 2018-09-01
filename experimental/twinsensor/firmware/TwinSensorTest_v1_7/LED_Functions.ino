/*
Twin Sensor Test v1.7 Beta
Signal LED Functions

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
*                                    Function blinkLED()                                    *
*********************************************************************************************
*/

/*
Signal statuses using the LED(s), zero or more long flashes followed by zero or more short
flashes. We can't use the serial port for debugging when running live.
*/

void blinkLED( int led, int x, int y) {


	// duration of flashes in ms
	int longflash=250;
	int shortflash=75;

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

}

/*
*********************************************************************************************
*                                  Function strikeLED()                                     *
*********************************************************************************************
*/

/*
Use the LED to signal strikes. Turn on when rendezvous is acheived and the srike is not
being supressed, turn off when the pulse is sent.
*/

void strikeLED( boolean ledOn ) {

	if ( ledOn ) {
		digitalWrite(LED, HIGH);   
	}
	else { 
		digitalWrite(LED, LOW);   
	}

}

/*
*********************************************************************************************
*                                    Function ledBlinkMode()                                *
*********************************************************************************************
*/

/*
This function is called to set up blinking mode (setblinking = true), and the speed
(period = time in ms). When turning blinking off, the period parameter is not used and can
be set to zero. See also the processLed() function.
*/

void ledBlinkMode( boolean setblinking, unsigned long period ) {
	if ( setblinking ) {
		//turn on LED blinking
		ledBlinkState = true;
		ledBlinkPeriod = period;
		digitalWrite( LED, HIGH );
		ledNextStateChangeTime = millis() + period;
	}
	else
	{
		//turn off LED blinking
		ledBlinkState = false;
		digitalWrite( LED, LOW );
	}
}

/*
*********************************************************************************************
*                                     Function processLed()                                *
*********************************************************************************************
*/

/*
Process the blinking LED non-blocking in the background - call this function on each
iteration of loop(), and any other closed input loops. Does nothing if the LED is not
blinking (which will be the usual state), so minimal processing overhead. If the LED is
supposed to be blinking then this function checks whether the the state is due to change.
*/

void processLed( void ) {
	if ( ledBlinkState ) {
		//blinking is on, is it time to change state?
		if ( millis() > ledNextStateChangeTime ) {
			//toggle the LED states by reading the output pin.
			digitalWrite( LED, !digitalRead( LED ) );
			//update the time of the next change of state
			ledNextStateChangeTime = millis() + ledBlinkPeriod;
		}
	}
	// no else - nothing to do if the LED is not blinking
}