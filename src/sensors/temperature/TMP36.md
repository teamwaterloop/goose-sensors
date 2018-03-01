For the TMP36 sensor, there are three leads:
One of the outside leads is a 2.7-5.5V input (use 3.3V), the other outside is ground, and the middle is the signal.

The scale variable (0.0048828) is equal to 5/1024.
The sensors gives a reading between 0 and 1023, so by scaling it by 5/1024,
we're finding what voltage of a 5V (Arduino Mega 2560 operates at 5V) range it is at.
The final result minuses .5 from its reading because it measures from -50 to 125 celsius instead of 0 to 175 celsius.
(3.3V input gives a more accurate reading than 5V)

For example, a sample of 143 from TMP36 translates into a celsius reading of 19.82 degrees.