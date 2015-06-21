/*
 * clock.c
 *
 *  Created on: Nov 12, 2013
 *      Author: Nathan
 */
#include "all.h"

clock_struct Clock_Ticks = CLOCK_TICKS_CLEAR;
unsigned int index = 0;
unsigned short nextSound;
int speed;

void ClockSetup()
{
	SystemClockSetup();
	InitializeCpuTimer2(CLOCK_PERIOD);
	StartCpuTimer2();
}

void PrepareNextSound()
{
	int i = 0;
	nextSound = soundFile[index];
	while(i < 12)
	{
		int temp = (nextSound & (1 << i));
		temp = temp >> (i);
		if((nextSound & (1 << i)) >> (i) == 0)
		{
			switch(i)
			{
			case 0:
				GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;
				break;
			case 1:
				GpioDataRegs.GPBCLEAR.bit.GPIO41 = 1;
				break;
			case 2:
				GpioDataRegs.GPACLEAR.bit.GPIO16 = 1;
				break;
			case 3:
				GpioDataRegs.GPBCLEAR.bit.GPIO44 = 1;
				break;
			case 4:
				GpioDataRegs.GPACLEAR.bit.GPIO25 = 1;
				break;
			case 5:
				GpioDataRegs.GPACLEAR.bit.GPIO8 = 1;
				break;
			case 6:
				GpioDataRegs.GPACLEAR.bit.GPIO17 = 1;
				break;
			case 7:
				GpioDataRegs.GPACLEAR.bit.GPIO18 = 1;
				break;
			case 8:
				GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;
				break;
			case 9:
				GpioDataRegs.GPACLEAR.bit.GPIO9 = 1;
				break;
			case 10:
				GpioDataRegs.GPACLEAR.bit.GPIO11 = 1;
				break;
			case 11:
				GpioDataRegs.GPACLEAR.bit.GPIO20 = 1;
				break;
			default:
				break;
			}
		}
		else
		{
			switch(i)
			{
			case 0:
				GpioDataRegs.GPASET.bit.GPIO6 = 1;
				break;
			case 1:
				GpioDataRegs.GPBSET.bit.GPIO41 = 1;
				break;
			case 2:
				GpioDataRegs.GPASET.bit.GPIO16 = 1;
				break;
			case 3:
				GpioDataRegs.GPBSET.bit.GPIO44 = 1;
				break;
			case 4:
				GpioDataRegs.GPASET.bit.GPIO25 = 1;
				break;
			case 5:
				GpioDataRegs.GPASET.bit.GPIO8 = 1;
				break;
			case 6:
				GpioDataRegs.GPASET.bit.GPIO17 = 1;
				break;
			case 7:
				GpioDataRegs.GPASET.bit.GPIO18 = 1;
				break;
			case 8:
				GpioDataRegs.GPASET.bit.GPIO5 = 1;
				break;
			case 9:
				GpioDataRegs.GPASET.bit.GPIO9 = 1;
				break;
			case 10:
				GpioDataRegs.GPASET.bit.GPIO11 = 1;
				break;
			case 11:
				GpioDataRegs.GPASET.bit.GPIO20 = 1;
				break;
			default:
				break;
			}
		}
		i++;
	}
	index++;
	if(index >= 41384)
	{
		index = 0;
	}
}

void SendNextSound()
{
	GpioDataRegs.GPACLEAR.bit.GPIO0 = 1; // Toggle CS low
	GpioDataRegs.GPASET.bit.GPIO0 = 1; // Toggle CS back high after ~16 ns
}

// Connected to INT13 of CPU (use MINT13 mask):
__interrupt void INT13_ISR(void)     // INT13 or CPU-Timer1
{
	 //***********************************WARNING!!********************************************\\
	//BE CAREFUL YOU NEED TO ALLOW NESTING FOR ANY INTERRUPT THAT MIGHT HAPPEN IN THIS INTERRUPT\\

	EINT;		//enable all interrupts

	ClockHeartbeat(user_ops.UserFlags.all);

	RestartCPUTimer1();
	DINT;
}

// Connected to INT14 of CPU (use MINT14 mask):
// ISR can be used by the user.
__interrupt void INT14_ISR(void)     // INT14 or CPU-Timer2
{
	//***********************************WARNING!!********************************************\\
	//BE CAREFUL YOU NEED TO ALLOW NESTING FOR ANY INTERRUPT THAT MIGHT HAPPEN IN THIS INTERRUPT\\

	 EINT;		//enable all interrupts

	//todo USER: Define Clock ISR


	if(user_data.MotorVelocity.F32 < 20)
	{
		speed = EIGHT_THOUSAND_HZ;
	}
	else if(user_data.MotorVelocity.F32 < 375)
	{
		speed = NINE_THOUSAND_HZ;
	}
	else if(user_data.MotorVelocity.F32 < 750)
	{
		speed = TEN_HUNDRED_HZ;
	}
	else if(user_data.MotorVelocity.F32 < 1125)
	{
		speed = ELEVEN_HUNDRED_HZ;
	}
	else if(user_data.MotorVelocity.F32 < 1500)
	{
		speed = TWELVE_HUNDRED_HZ;
	}
	else if(user_data.MotorVelocity.F32 < 1875)
	{
		speed = THIRTEEN_HUNDRED_HZ;
	}
	else if(user_data.MotorVelocity.F32 < 2250)
	{
		speed = FOURTEEN_HUNDRED_HZ;
	}
	else if(user_data.MotorVelocity.F32 < 2625)
	{
		speed = FIFTEEN_HUNDRED_HZ;
	}
	else if(user_data.MotorVelocity.F32 < 3000)
	{
		speed = SIXTEEN_HUNDRED_HZ;
	}
	else
	{
		speed = SIXTEEN_HUNDRED_HZ;
	}
	// 8 KHz 0 MPH
	// 16 KHz 120 MPH

	if (Clock_Ticks.DataOut == speed)
	{
		PrepareNextSound();
		SendNextSound();
		Clock_Ticks.DataOut = 0;
	}

	Clock_Ticks.DataOut++;


	RestartCpuTimer2();
	DINT;

}

