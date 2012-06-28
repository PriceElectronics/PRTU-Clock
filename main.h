#ifndef MAIN_H
#define MAIN_H

void main(void);

void InterruptHandlerHigh(void);

/********** Circuit board I/O control ***********/

#define BLINK_OFF (LATAbits.LATA5 = 0)		//PORTB,5 OFF
#define BLINK_ON (LATAbits.LATA5 = 1)			//PORTB,5 ON

#define LNET_OFF (LATBbits.LATB2 = 0)
#define LNET_ON (LATBbits.LATB2 = 1)

#define AM_OFF (LATCbits.LATC5 = 0)
#define AM_ON (LATCbits.LATC5 = 1)

#define PM_OFF (LATEbits.LATE2 = 0)
#define PM_ON (LATEbits.LATE2 = 1)

#define SEG_A_OFF (LATDbits.LATD0 = 0)		//PORTD,0 OFF
#define SEG_A_ON (LATDbits.LATD0 = 1)			//PORTD,0 ON

#define SEG_B_OFF (LATDbits.LATD1 = 0)		//PORTD,1 OFF
#define SEG_B_ON (LATDbits.LATD1 = 1)			//PORTD,1 ON

#define SEG_C_OFF (LATDbits.LATD2 = 0)		//PORTD,2 OFF
#define SEG_C_ON (LATDbits.LATD2 = 1)			//PORTD,2 ON

#define SEG_D_OFF (LATDbits.LATD3 = 0)		//PORTD,3 OFF
#define SEG_D_ON (LATDbits.LATD3 = 1)			//PORTD,3 ON

#define SEG_E_OFF (LATDbits.LATD4 = 0)		//PORTD,4 OFF
#define SEG_E_ON (LATDbits.LATD4 = 1)			//PORTD,4 ON

#define SEG_F_OFF (LATDbits.LATD5 = 0)		//PORTD,5 OFF
#define SEG_F_ON (LATDbits.LATD5 = 1)			//PORTD,5 ON

#define SEG_G_OFF (LATDbits.LATD6 = 0)		//PORTD,6 OFF
#define SEG_G_ON (LATDbits.LATD6 = 1)			//PORTD,6 ON

#define SEG_DP_OFF (LATDbits.LATD7 = 0)		//PORTD,7 OFF
#define SEG_DP_ON (LATDbits.LATD7 = 1)			//PORTD,7 ON

#define CLEAR_DIGIT (LATD = 0)

#define SEG_1_GND_OFF (LATCbits.LATC0 = 0)		//PORTC,0 OFF
#define SEG_1_GND_ON (LATCbits.LATC0 = 1)			//PORTC,0 ON

#define SEG_2_GND_OFF (LATCbits.LATC1 = 0)		//PORTC,1 OFF
#define SEG_2_GND_ON (LATCbits.LATC1 = 1)			//PORTC,1 ON

#define SEG_3_GND_OFF (LATCbits.LATC2 = 0)		//PORTC,2 OFF
#define SEG_3_GND_ON (LATCbits.LATC2 = 1)			//PORTC,2 ON

#define SEG_4_GND_OFF (LATCbits.LATC3 = 0)		//PORTC,3 OFF
#define SEG_4_GND_ON (LATCbits.LATC3 = 1)			//PORTC,3 ON

#define COLON_ON (LATB |= 0x03) 					// LATB0:1 on
#define COLON_OFF (LATB &= 0xFC) 					// LATB0:1 off

#define BEEP_BEEP_OFF (LATEbits.LATE1 = 0)		//PORTE,1 OFF
#define BEEP_BEEP_ON ((PORTE) |= 1 << (1))			//PORTE,1 ON

#define FALSE 0
#define TRUE 1

extern unsigned int lnetTimeoutCounter;

#endif
