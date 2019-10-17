#include <msp430.h>

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;       // disable watchdog timer


    P1DIR |= BIT0;  // Set P1.0 (Pin 1, Bit 0) as the output pin
    P1REN |= BIT3;  //enable internal resistor
    P1OUT |= BIT3;  //sets resistor to pull up

    while(1)
    {
        //Program begins with the LED as a logic 1
        //Button pressed = toggle LED
        //Button released, LED will stay on or off depending


        if((P1IN & BIT3)!=BIT3) //if Pin1 and Bit 3 aren't equal to Bit3 the LED will toggle
        {
            P1OUT ^= BIT0;
            __delay_cycles(100000);
        }
    }

}
