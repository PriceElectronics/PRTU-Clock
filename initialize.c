//multiple comments
#include <p18f4620.h>

//-----------------------------------------------------------------------------
// initPorts - does a checksum on a new page and extracts the time
void initPorts(void)
{
// ***** SETUP TRISA *****
	
	ADCON1bits.PCFG = 0xFF;

	PORTA=0;

	TRISAbits.TRISA0 = 1; //thermistor
	TRISAbits.TRISA1 = 1; //ana1
	TRISAbits.TRISA2 = 1; //ana2
	TRISAbits.TRISA3 = 1; //sw1
	TRISAbits.TRISA4 = 1; //sw2
	TRISAbits.TRISA5 = 1; //sw3
	TRISAbits.TRISA6 = 1; //osc
	TRISAbits.TRISA7 = 1; //osc
	
	PORTA=0;

// ***** SETUP TRISB *****
	
	PORTB=0;

	TRISBbits.TRISB0 = 0; //colon top LED
	TRISBbits.TRISB1 = 0; //colon bottom LED
	TRISBbits.TRISB2 = 0; //spare led 2
	TRISBbits.TRISB3 = 1; //J18 - con 1 - spare
	TRISBbits.TRISB4 = 0; //J20 - con 1 - spare
	TRISBbits.TRISB5 = 0; //J19 - con 1 - spare
	TRISBbits.TRISB6 = 1; //debug enable sets this to INPUT (ICD2)
	TRISBbits.TRISB7 = 1; //debug enable sets this to INPUT (ICD2)

	PORTB=0;

// ***** SETUP TRISC *****
	
	PORTC=0;

	TRISCbits.TRISC0 = 0; //G1
	TRISCbits.TRISC1 = 0; //G2 
	TRISCbits.TRISC2 = 0; //G3
	TRISCbits.TRISC3 = 0; //G4
	TRISCbits.TRISC4 = 0; //stat therm gnd
	TRISCbits.TRISC5 = 0; //rx LED
	TRISCbits.TRISC6 = 0; //TX
	TRISCbits.TRISC7 = 1; //RX

	PORTC=0;
	
// ***** SETUP TRISC *****
	
	PORTD=0;
	
	TRISDbits.TRISD0 = 0; //seg A
	TRISDbits.TRISD1 = 0; //seg B
	TRISDbits.TRISD2 = 0; //seg C
	TRISDbits.TRISD3 = 0; //seg D
	TRISDbits.TRISD4 = 0; //seg E
	TRISDbits.TRISD5 = 0; //seg F
	TRISDbits.TRISD6 = 0; //seg G
	TRISDbits.TRISD7 = 0; //seg DP

	PORTD=0;

// ***** SETUP TRISE *****
	
	PORTE=0;
	
	TRISEbits.TRISE0 = 0; //spare led 1
	TRISEbits.TRISE1 = 0; //BEEP_BEEP
	TRISEbits.TRISE2 = 0; //TX LED

	PORTE=0;

	return;

}

//-----------------------------------------------------------------------------
// initTimer1 - sets up Timer1 for main loop 1ms
void initTimer1(void)
{
	PIE1bits.TMR1IE = 0;
	PIR1bits.TMR1IF = 0;
	
	T1CON = 0;
//	T1CONbits.RD16 = 1;
	T1CONbits.TMR1ON = 1;
	
	return;
}

//-----------------------------------------------------------------------------
// initUART - sets up UART1 for 1200 baud LNET
void initUART(void)
{
	// disable TX and RX interrupts and set for 1200 baud
	
	TXSTA = 0;
	RCSTA = 0;
	BAUDCON = 0;
	
	SPBRG = 129;

	RCSTAbits.SPEN = 1;
	
	PIE1bits.TXIE = 0;
	PIR1bits.TXIF = 0;
	PIE1bits.RCIE = 1;
	PIR1bits.RCIF = 0;	
	
	RCSTAbits.CREN = 1;
	
	INTCONbits.GIE = 1;
	INTCONbits.PEIE = 1;
	
	return;
}
