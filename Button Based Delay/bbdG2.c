#include <msp430.h> 


/**
 * credit to Alex Marino for BUtton_Down interrupt
 */

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;                   // Stop watchdog timer
    BCSCTL3 = LFXT1S_2;                         // internal oscillator
    P1DIR &= ~BIT3;                             // P1.3 as input (Button)
    P1IE |=  BIT3;                              // P1.3 interrupt enabled
    P1IES |= BIT3;                              // button high/low edge determined
    P1IFG &= ~BIT3;                             // flag cleared
    P1OUT &= ~BIT0;                             // green LED
    P1DIR |= (BIT0 + BIT6);                     // green and red LED output
    TA0CCTL0 = CCIE;                            // TA0CCR0 interrupt enabled
    TA0CCR0 = 5000;                             // set interrupt value of TA0CCR0
    TA0CTL = TASSEL_1 + MC_1;                   // enable ACLK

  __enable_interrupt();                         // Enable the interrupt
}

//Interrupt for initial LED1 button blink
#pragma vector =TIMER0_A0_VECTOR
__interrupt void TIMER0_A1(void)
{

    P1OUT ^= BIT0;              //LED1

}
//Interrupt for when the button is pressed
#pragma vector =PORT1_VECTOR
__interrupt void Button_down(void)
{
    if (P1IES & BIT3)                       //If falling edge and button Pressed
    {
        P1IES &=~BIT1;                      //Rising Edge
        TACTL=TACLR;                        //Clears timer
        TA0CTL = TASSEL_1 + ID_3 + MC_2;    //ACLK, Divides by 3, Continuous Mode
        P1OUT |= BIT6;
    }

    else //When button is let go
    {
        P1OUT &= ~BIT6;                      //LED2 Turned Off
        TA0CTL = MC_0;                       //Turns off Timer
        TA0CCR0 = TA0R;                     //Set Capture and Compare Register to counter value
        TACTL |= TACLR;                     //Clears timer
        TA0CTL = TASSEL_1 + ID_3 + MC_1;    //ACLK, Divides by 3, Up Mode
        P1IES |= BIT3;                      //Detects Falling Edge
    }

    P1IFG &= ~BIT3;                         //Clears Interrupt Flag
}
