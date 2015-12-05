/* 	Author: 	Evan Glazer
	School:		University of Central Florida
	Class:		EGN3211 Engineering Analysis and Computation
	Program:	mainCCS.c
	Write a program for the MSP430 using Energia that will place an interrupt on the push2 button to blink either the red or green LED in one of 
        two particular patterns for each color LED.  The first time the button is pushed the red LED should turn on for 1 second and then turn off.  */
        
#include <msp430g2553.h>
#define pin0mask (0x01 << 0)
#define pin3mask (0x01 << 3)
#define pin6mask (0x01 << 6)

int main(void)
{
      // Variables
      int pushed = 0; // flag to tell us when we've handled a button event
      int blinkMode = 0; // toggle of modes
      int blinkMask = pin0mask; // which light we need to blink
      
      // stop watchdog timer
      WDTCTL = WDTPW + WDTHOLD; 
      // configure pins 0,6 on port 1 as output pins
      P1DIR = pin0mask | pin6mask;
      // make sure green (pin 6) is turned off
      P1OUT &= ~pin6mask; 
     
     // infinite loop
     for( ; ; )
      {
      
        // this can cause a delay in length
        for( int j = 0; j < 10000; j++ )
        {
          
          if((P1IN & pin3mask ) == 0)
          {
            // check to see if we don't try to handle this press again
            if(!pushed)
            {
                pushed = 1;
                blinkMode = (blinkMode + 1)%4;
            }
            // blink red bit 0 only    
            if(blinkMode == 0)
            {
                blinkMask = pin0mask;
                P1OUT &= ~pin6mask;
            }
            // blink green pin 6 only 
            else if(blinkMode == 1)
            {
                blinkMask = pin6mask;
                P1OUT &= ~pin0mask;
            }
            // blink both together 
            else if(blinkMode == 2)
            {
                blinkMask = pin0mask|pin6mask;
                P1OUT |= pin0mask|pin6mask;
            }
            // blink both alternately
            else
            {
                blinkMask = pin0mask|pin6mask;
                P1OUT &= ~pin0mask;
                P1OUT |= pin6mask;
            }
            }
        }
            else
            {
               pushed = 0;
            }
    }
        P1OUT ^= blinkMask;
} 