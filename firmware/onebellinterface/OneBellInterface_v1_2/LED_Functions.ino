/*
One Bell Simulator Interface v1.2 Beta
Signal LED Functions

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
*                                    Function blinkLED()                                    *
*********************************************************************************************
*/

/*
Signal statuses using a the LED, zero or more long flashes followed
by zero or more short flashes. We can't use the serial port for debugging.

1 long & N short = MBI protocol commands
2 long & N short = Arduino config commands (EEPROM or volatile)
0 long & 1 short = CLI keypress (status, etc)
3 long & 0 short = Serial Data Error
*/

void blinkLED( int led, int x, int y) {

	/*
Don't blink the LED at all for Beltower, because it will sometimes send two commands in
quick succession and delay causes it to complain that the box is not responding. The
exact timeout is not specified in the protocol, and the value in the code is unknown.
The original approach of supressing blinks after delay data is received no longer works,
because Beltower now sometimes retrieves the timer values twice in quick succession, so
now we just don't bother with the signal LED at all for Beltower. Hey ho.
*/

	if (EEPROM.read(17) == 'B') {
		// Beltower - suppress signal LED blinks altogether because of timing issues
		return;
	}

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

