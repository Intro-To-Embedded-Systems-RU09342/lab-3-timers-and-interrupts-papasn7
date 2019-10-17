# Button Based Delay
The goal of this lab is to use a button to control the blink rate of the LED. The blink rate of the LED matches the length of time you hold the button down. 
The only problem is it is easy to get an overflow on the timer and holding it for too long will result in a fast blink rate.

The difference between the two is that the FR6989 has to have is default high impedance state disabled, as well as you have to enable the pullup resistor of the FR6989 for the button.