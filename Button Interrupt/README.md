# Button Interrupt
A button is used to interrupt an LED. This interrupt will either turn the LED on or off. Instead of using polling we use interrupts 
to enable to the switch between on and off state using the code below.
```c
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
}
```
The interrupt will be the code that is housed inside the method above.
