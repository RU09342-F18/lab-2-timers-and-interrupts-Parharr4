#include <msp430.h> 


void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;   //disables watchdog timer
    P1DIR = BIT6;               //
    P2REN = BIT1;               // pull up Resistor
    P2OUT = BIT1;               // green LED
    P2IE = BIT1;                //button becomes trigger
    __enable_interrupt();
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)   //interrupt function
{
    P1OUT ^= BIT6;              //toggles LED
    P1IFG = ~BIT3;
}
