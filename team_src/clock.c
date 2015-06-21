/*
 * clock.c
 *
 *  Created on: Nov 12, 2013
 *      Author: Nathan
 */
#include "all.h"

clock_struct Clock_Ticks = CLOCK_TICKS_CLEAR;


void ClockSetup()
{
	SystemClockSetup();
	InitializeCpuTimer2(CLOCK_PERIOD);
	StartCpuTimer2();
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

	 /*
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
		//PrepareNextSound();
		//SendNextSound();
		Clock_Ticks.DataOut = 0;
	}
	*/
	Clock_Ticks.DataOut++;


	RestartCpuTimer2();
	DINT;

}

