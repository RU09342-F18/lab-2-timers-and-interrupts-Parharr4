#include <msp430.h> 


/**
 * main.c
 */
void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;
    P1DIR = BIT0; //
    P2REN = BIT1; //pull up resistor
    P2OUT = BIT1; //LED
    P2IE = BIT1; //trigger is button
    __enable_interrupt();
}
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    P1OUT ^= BIT0;
    P2IFG = ~BIT1;
}
