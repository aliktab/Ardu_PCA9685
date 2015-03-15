Arduino Library for the PCA9685 chip (used Arduino I2C Master Library).

The PCA9685 is an I2C-bus controlled 16-channel LED controller optimized for LCD
Red/Green/Blue/Amber (RGBA) color backlighting applications. Each LED output has its
own 12-bit resolution (4096 steps) fixed frequency individual PWM controller that operates
at a programmable frequency from a typical of 40 Hz to 1000 Hz with a duty cycle that is
adjustable from 0 % to 100 % to allow the LED to be set to a specific brightness value.
All outputs are set to the same PWM frequency.

PCA9685 data-sheet can be found here: http://www.adafruit.com/datasheets/PCA9685.pdf

It uses I2C library for communication with PCA9685 chip. You have to initialize I2c 
instance on your own. Somehow like that:

// Initialize I2C interface.
I2c.begin();
I2c.setSpeed(true);

You can use the same I2c instance for cummunication with more then one chip at the same time.
