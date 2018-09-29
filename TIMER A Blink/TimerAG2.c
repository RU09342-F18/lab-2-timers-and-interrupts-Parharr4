#include <msp430.h> 

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                     // Stop watchdog timer
  BCSCTL3 = LFXT1S_2;                           // Crystal Oscillator
  P1DIR |= BIT0;                       // LED output
  P1DIR |= BIT6;                       // LED output
  TA0CCR0 = 60000;                      // Sets TA0CCR0 interrupt
  TA1CCR0 = 10000;                      // Sets TA1CCR0 interrupt
  TA0CTL = TASSEL_1 + MC_1;                     // ACLK, ACLK
  TA1CTL = TASSEL_1 + MC_1;                     // ACLK, ACLK
  TA0CCTL0 = CCIE;                              // TA0CCR0 interrupt enabled
  TA1CCTL0 = CCIE;                              // TA1CCR1 interrupt enabled

  __enable_interrupt();                         // Enable the interrupt
}
#pragma vector=TIMER1_A0_VECTOR                 // Interrupt when Timer hits TA1CCR0
__interrupt void Timer_A1(void)
{
    P1OUT ^= BIT0;                              // P1.0 LED toggle
}
#pragma vector=TIMER0_A0_VECTOR                 // Interrupt when Timer hits TA0CCR0
__interrupt void Timer_A(void)
{
    P1OUT ^= BIT6;                              // P1.6LED toggle
}
