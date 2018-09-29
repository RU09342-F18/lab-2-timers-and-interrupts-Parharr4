#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                     // Stop watchdog timer
  UCSCTL4 = SELA_0;                          // Crystal Oscillator
  P1DIR |= BIT0;                       // LED output
  P4DIR |= BIT7;                       // LED output
  TA0CCR0 = 12000;                      // Sets TA0CCR0 interrupt
  TA1CCR0 = 64000;                      // Sets TA1CCR0 interrupt
  TA0CTL = TASSEL_1 + MC_1 + ID_1;                     // ACLK, ACLK
  TA1CTL = TASSEL_1 + MC_1 + ID_1;                     // ACLK, ACLK
  TA0CCTL0 = CCIE;                              // TA0CCR0 interrupt enabled
  TA1CCTL0 = CCIE;                              // TA1CCR1 interrupt enabled

  __enable_interrupt();                         // Enable the interrupt
}
#pragma vector=TIMER1_A0_VECTOR                 // Interrupt when Timer hits TA1CCR0
__interrupt void Timer1_A1(void)
{
    P1OUT ^= BIT0;                              // P1.0 LED toggle
}
#pragma vector=TIMER0_A0_VECTOR                 // Interrupt when Timer hits TA0CCR0
__interrupt void Timer0_A0(void)
{
    P4OUT ^= BIT7;                              // P1.6LED toggle
}
