/*****************************************
* @title	main.c dfslkjafdsjlkfdsjlk;fsd
* @descrip	PRTU Clock
* @author	Jordan Hiebert
* @version	v1.00, 07-Jun-2011
******************************************/

// ***** Config bits *****
#pragma config OSC=HS, IESO=OFF, FCMEN=OFF
#pragma config WDT=OFF, PBADEN=OFF, BOREN=OFF
#pragma config MCLRE=ON, LPT1OSC=OFF
#pragma config DEBUG=OFF, XINST=OFF, LVP=OFF, STVREN=ON

#include <p18f4620.h>
#include "main.h"
#include "initialize.h"
#include "display.h"
#include "lnet.h"

unsigned int secondCounter = 0;
unsigned int lnetTimeoutCounter = 0;	// offset so timers don't run at the same time
unsigned int beepCounter = 0;

//-----------------------------------------------------------------------------
// main
void main(void)
{
	initPorts();
	initTimer1();
	initUART();

	while(1)
	{
		
		updateDigits();
		updateDisplay();


		if(beepCounter<115) beepCounter++;		// beeper off count
		else
		{
			beepCounter = 0;
			BEEP_BEEP_OFF;
		}


		if(secondCounter<1000) secondCounter++;		// 1 second tasks
		else
		{
			if(LATBbits.LATB0 == 0) COLON_ON;	// blink colon once per second
			else COLON_OFF;
			secondCounter = 0;
		}
		

		if(lnetTimeoutCounter<14580) lnetTimeoutCounter++;		// (lnet timeout 14.58 sec)
		else													// no overlap with 1 sec
		{
			LNET_OFF;
			lnetConnected = FALSE;
			PM_OFF;
			lnetHours = 88;
			lnetMinutes = 88;
		}

		// tasks that execute once per second are located in secTasks()
		
		while(TMR1H < 0x09);
		while(TMR1L < 0xC4);  // wait for 1 ms to elapse

		TMR1H = 0;
		TMR1L = 0; // reset tmr1 registers
	}
	
	return;
}

//===== INTERRUPTS ============================================================

//----------------------------------------------------------------------------
// High priority interrupt vector

#pragma code InterruptVectorHigh = 0x08
void
InterruptVectorHigh (void)
{
  _asm
    goto InterruptHandlerHigh //jump to interrupt routine
  _endasm
}

//----------------------------------------------------------------------------
// High priority interrupt routine

#pragma code
#pragma interrupt InterruptHandlerHigh

void
InterruptHandlerHigh ()
{
  if (PIR1bits.RCIF)
    {
		PIR1bits.RCIF = 0;            //clear interrupt flag - happens at the end of the service UART1_Rx
		serviceRx();

    }
}

//----------------------------------------------------------------------------
