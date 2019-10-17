#include <msp430.h>     // header file for MSP430

/* static volatile int enable_blink is used so the compiler should not perform optimizations which
 * cache the value of the variable. It forces the compiler to
 * generate code which always goes to memory to read the value stored in the variable.
 */
static volatile int enable_blink = 0;;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // stop watchdog timer (WDT)

    P1REN |= BIT1;                          // Enables internal resistor
    P1DIR |= BIT0;                          // Set P1.0 (Port 1, Bit 0) as the output pin
    P1OUT |= BIT1;                          // Set resistor to pull up
    P1IE |= BIT1;                           // Enable interrupts for button/switch (P1.1)
    P1IES |= BIT1;                          // Enable interrupts for button/switch (P1.1) at rising edge of clock
    P1IFG &= ~BIT1;                         // Clears interrupt flag for P1.1

    __enable_interrupt();                   // Function to enable interrupts

    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings
                                            // Without this line of code (line 31), none of the ports
                                            // such as buttons and LEDs can be used

    while(1)
    {
        if (enable_blink == 1)              // If the button is pressed by the user
        {
            P1OUT ^= BIT0;                      // The LED will toggle at a set rate
            __delay_cycles(100000);
        }
    }

}

// Function to make interrupts work
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)           // Button Interrupt for Port 1 (P1.3)
{
    enable_blink ^= 1;                   // Enable blink
    P1IFG &= ~BIT1;                       // Clears interrupt flag for P1.3
}
