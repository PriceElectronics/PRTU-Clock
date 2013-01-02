/*
http://stackoverflow.com/questions/7167645/how-do-i-create-a-new-git-branch-from-an-old-commit
Used git branch newBranch oldeBranch
*/
#include <p18f4620.h>
#include "main.h"
#include "lnet.h"

struct {
	int thousands;
	int hundreds;
	int tens;
	int ones;
} theDisplay;

int displayState = 0;

//-----------------------------------------------------------------------------
// showDigit - turns on segments depending on what digit is to be displayed
void showDigit(int theDigit)
{
	switch(theDigit)
	{
		case 0 : 
			SEG_A_ON;
			SEG_B_ON;
			SEG_C_ON;
			SEG_D_ON;
			SEG_E_ON;
			SEG_F_ON;
			break;	
		case 1 :
			SEG_B_ON;
			SEG_C_ON;
			break;
		case 2 :
			SEG_A_ON;
			SEG_B_ON;
			SEG_D_ON;
			SEG_E_ON;
			SEG_G_ON;
			break;
		case 3 :
			SEG_A_ON;
			SEG_B_ON;
			SEG_C_ON;
			SEG_D_ON;
			SEG_G_ON;
			break;
		case 4 :
			SEG_B_ON;
			SEG_C_ON;
			SEG_F_ON;
			SEG_G_ON;
			break;
		case 5 :
			SEG_A_ON;
			SEG_C_ON;
			SEG_D_ON;
			SEG_F_ON;
			SEG_G_ON;
			break;
		case 6 :
			SEG_A_ON;
			SEG_C_ON;
			SEG_D_ON;
			SEG_E_ON;
			SEG_F_ON;
			SEG_G_ON;
			break;
		case 7 :
			SEG_A_ON;
			SEG_B_ON;
			SEG_C_ON;
			break;
		case 8 :
			SEG_A_ON;
			SEG_B_ON;
			SEG_C_ON;
			SEG_D_ON;
			SEG_E_ON;
			SEG_F_ON;
			SEG_G_ON;
			break;
		case 9 :
			SEG_A_ON;
			SEG_B_ON;
			SEG_C_ON;
			SEG_D_ON;
			SEG_F_ON;
			SEG_G_ON;
			break;
		case 40 :	//display an 'P'
			SEG_A_ON;
			SEG_B_ON;
			SEG_E_ON;
			SEG_F_ON;
			SEG_G_ON;
			break;
		case 41 :	//display an 'd'
			SEG_B_ON;
			SEG_C_ON;
			SEG_D_ON;
			SEG_E_ON;
			SEG_G_ON;
			break;
		case 42 :	//display an 'r'
			SEG_E_ON;
			SEG_G_ON;
			break;
		case 43 :	//display an 'P'
			SEG_A_ON;
			SEG_B_ON;
			SEG_E_ON;
			SEG_F_ON;
			SEG_G_ON;
			break;
		case 44 :	//display an 'n'
			SEG_C_ON;
			SEG_E_ON;
			SEG_G_ON;
			break;
		case 45 :	//display an 'b'
			SEG_C_ON;
			SEG_D_ON;
			SEG_E_ON;
			SEG_F_ON;
			SEG_G_ON;
			break;
		case 46 :	//display an 'A'
			SEG_A_ON;
			SEG_B_ON;
			SEG_C_ON;
			SEG_E_ON;
			SEG_F_ON;
			SEG_G_ON;
			break;
		case 47 :	//display an 'L'
			SEG_D_ON;
			SEG_E_ON;
			SEG_F_ON;
			break;
		case 48 :	//display an 'E'
			SEG_A_ON;
			SEG_D_ON;
			SEG_E_ON;
			SEG_F_ON;
			SEG_G_ON;
			break;
		case 49 :	//display an 'C'
			SEG_A_ON;
			SEG_D_ON;
			SEG_E_ON;
			SEG_F_ON;
			break;
		case 50 :	//display a Blank
			break;
		case 51 :	//display L3 high decimal point
			SEG_C_ON;
			break;
		case 52 :	//display 't'
			SEG_D_ON;
			SEG_E_ON;
			SEG_F_ON;
			SEG_G_ON;
			break;
		case 53 :	//display an 'F'
			SEG_A_ON;
			SEG_E_ON;
			SEG_F_ON;
			SEG_G_ON;
			break;
		default: /*ERROR!*/ break;
	}	
	return;
}

//-----------------------------------------------------------------------------
// updateDigits - chops up the current time and puts it into the display struct
// executed from main()
void updateDigits(void)
{
	unsigned char displayHours;

	if(lnetConnected)
	{
		if(lnetHours!=88)
		{
			if(lnet24HourTime || lnetHours < 12)
			{
				if(lnetHours==0 && lnet24HourTime==FALSE) displayHours = 12;
				else displayHours = lnetHours;
				PM_OFF;
			}
			else
			{
				if(lnetHours==12) displayHours = lnetHours;
				else displayHours = lnetHours-12;
				PM_ON;
			}
		}
		else displayHours = lnetHours;
	}
	else displayHours = lnetHours;
	
	theDisplay.thousands = (int)(displayHours/10);
	theDisplay.hundreds = (displayHours%10);
	theDisplay.tens = (int)(lnetMinutes/10);
	theDisplay.ones = (lnetMinutes%10);

	if(lnetHours != lnetHoursShadow)
	{
		lnetHoursShadow = lnetHours;
		BEEP_BEEP_ON;
	}
	
	return;
}

//-----------------------------------------------------------------------------
// updateDisplay - updates one digit per execution, runs every 1ms
// executed from main()
void updateDisplay(void)
{
	switch(displayState)
	{
		case 0:
			SEG_4_GND_OFF;
			CLEAR_DIGIT;
			if(theDisplay.thousands != 0)
			{
				SEG_1_GND_ON;
				showDigit(theDisplay.thousands);
			}
			break;
		case 1:
			SEG_1_GND_OFF;	
			CLEAR_DIGIT;
			SEG_2_GND_ON;
			showDigit(theDisplay.hundreds);
			break;
		case 2:
			SEG_2_GND_OFF;
			CLEAR_DIGIT;
			SEG_3_GND_ON;
			showDigit(theDisplay.tens);
			break;
		case 3:
			SEG_3_GND_OFF;
			CLEAR_DIGIT;
			SEG_4_GND_ON;
			showDigit(theDisplay.ones);
			break;
		default:
			break;
	}
	
	if(displayState<3) displayState++;
	else displayState = 0;
	
	return;
}
