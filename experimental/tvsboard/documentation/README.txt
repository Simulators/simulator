An experimental daughter board for the Simulator Interface Board.

One of the shortcomings of the original Simulator Interface Board is the lack of
TVS protection against induced voltage spikes on the signal and power supply lines between
the Sensor Heads and the Simulator Interface.

This experimental board provides TVS protection for these connections in the form of
a daughter board which can be mounted on the Simulator Interface Board sensor connector,
and provides protected connections for the sensors.

The board is mounted onto the Simulator Interface Board with two male-to-female M3 threaded
nylon spacers, 12mm long, and suitable nylon M3 pan head screws and nuts.

The component used is the USB6B1 data line protection device from TI, which provides diode
bridge clamping at 6V for two data lines and supply rails. A total of 6 devices are required
for a 12-bell simulator. The SO-8 package can be hand soldered with a very fine tip iron
and good magnification.

Alternative multi-line or through-hole mount equivalent devices have not been identified.

Acknowledgement: The idea is not novel, the Bagley SBI uses the same approach (and the same
component).

AIC
25/6/2016