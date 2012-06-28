#include <p18f4620.h>
#include "main.h"
#include "lnet.h"

unsigned char lnetIncomingRaw[22];
unsigned char lnetMinutes = 88;
unsigned char lnetHours = 88;
unsigned char lnetHoursShadow = 0; // for hourly beeps
unsigned char lnet24HourTime = 0;
unsigned char lnetConnected = 0;
unsigned char lnetControllerModel = 0;
volatile unsigned char rxWriteIndex;

//-----------------------------------------------------------------------------
// checksumGood - runs a checksum on an LNET page and returns TRUE or FALSE
unsigned char checksumGood(void)
{
	signed int temp_hold = 0;		// Zero our checksum buffer
	unsigned char loop_count;
	
	for(loop_count = 4; loop_count < 20; loop_count++)		// Generate a checksum and compare it with the one that was sent
	{
		temp_hold += lnetIncomingRaw[loop_count];		// Add all data together
	}
	temp_hold &= 0x00FF;		// Truncate MSB
	temp_hold ^= 0xFF;			// One's complement
	temp_hold++;				// Two's complement
	temp_hold &= 0x00FF;		// Truncate MSB again, in case checksum is zero
	
	if(temp_hold == lnetIncomingRaw[20])		// Compare calculated checksum with received checksum
	{
		return(1);
	}
	else
	{
		return(0);
	}
}

//-----------------------------------------------------------------------------
// unstuff_Lnet - gets usable data out of an LNET page
unsigned int unstuff_Lnet(unsigned char unstuff_index)
{
	signed int temp_hold;
	
	temp_hold = 0;
	temp_hold = lnetIncomingRaw[unstuff_index];
	temp_hold = temp_hold << 8;
	temp_hold |= lnetIncomingRaw[unstuff_index - 1];

	return temp_hold;
}

//-----------------------------------------------------------------------------
// servicePage - does a checksum on a new page and extracts the time
void servicePage(void)
{
	unsigned char lnetCurrentPage;

	if(checksumGood)
	{
		lnetCurrentPage = lnetIncomingRaw[3];

		if(lnetCurrentPage == 0)
			lnetControllerModel = unstuff_Lnet(15);

		if(lnetControllerModel==7)		// make sure we're connected to RTU
		{
			lnetTimeoutCounter = 0;
			lnetConnected = TRUE;

			if(lnetCurrentPage == 5)
				lnetHours = unstuff_Lnet(19);

			if(lnetCurrentPage == 6)
				lnetMinutes = unstuff_Lnet(5);

			if(lnetCurrentPage == 19)
				lnet24HourTime = unstuff_Lnet(17);
		}
	}

	return;
}	

//-----------------------------------------------------------------------------
// serviceRx - spins an LNET page into lnetIncomingRaw[]
// executed by the UART1 RX interrupt (main.c)
void serviceRx(void)
{
	unsigned char temp_hold;


	temp_hold = RCREG;

	if(temp_hold == 0xFB)
	{
		rxWriteIndex = 0;
		LNET_ON;
	}
	
	lnetIncomingRaw[rxWriteIndex] = temp_hold;

	if(rxWriteIndex>20)
	{
		if(lnetIncomingRaw[21]==0xFE) servicePage();
		rxWriteIndex=0;
		LNET_OFF;
	}	
	else
		rxWriteIndex++;
	
	return;
}	
