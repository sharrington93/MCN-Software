/*
 * SensorCov().c
 *
 *  Created on: Oct 30, 2013
 *      Author: Nathan
 */

#include "all.h"

extern DSPfilter A0filter;
extern DSPfilter A1filter;
extern DSPfilter A2filter;
extern DSPfilter A3filter;
extern DSPfilter A4filter;
extern DSPfilter A5filter;
extern DSPfilter A6filter;
extern DSPfilter A7filter;
extern DSPfilter B0filter;
extern DSPfilter B1filter;
extern DSPfilter B2filter;
extern DSPfilter B3filter;
extern DSPfilter B4filter;
extern DSPfilter B5filter;
extern DSPfilter B6filter;
extern DSPfilter B7filter;
extern DSPfilter GPIO19filter;
extern DSPfilter GPIO26filter;

user_ops_struct ops_temp;
user_data_struct data_temp;

int max = 2000, min = 2000;
float r_th;
float v_in;

void SensorCov()
{
	SensorCovInit(4);
	while (sys_ops.State == STATE_SENSOR_COV)
	{
		LatchStruct();
		SensorCovMeasure();
		UpdateStruct();
		FillCANData();
	}
	SensorCovDeInit();
}

void SensorCovInit()
{
	//todo USER: SensorCovInit()
	SystemSensorInit(SENSOR_COV_STOPWATCH);
	initDSPfilter(&A0filter, ALPHA_SYS);
	initDSPfilter(&A1filter, ALPHA_SYS);
	initDSPfilter(&A2filter, ALPHA_SYS);
	initDSPfilter(&A3filter, ALPHA_SYS);
	initDSPfilter(&A4filter, ALPHA_SYS);
	initDSPfilter(&A5filter, ALPHA_SYS);
	initDSPfilter(&A6filter, ALPHA_SYS);
	initDSPfilter(&A7filter, ALPHA_SYS);
	initDSPfilter(&B0filter, ALPHA_SYS);
	initDSPfilter(&B1filter, ALPHA_SYS);
	initDSPfilter(&B2filter, ALPHA_SYS);
	initDSPfilter(&B3filter, ALPHA_SYS);
	initDSPfilter(&B4filter, ALPHA_SYS);
	initDSPfilter(&B5filter, ALPHA_SYS);
	initDSPfilter(&B6filter, ALPHA_SYS);
	initDSPfilter(&B7filter, ALPHA_SYS);
	ConfigGPIOSensor(410, 10000, 26, 0, 2);
	ConfigGPIOSensor(410, 10000, 19, 0, 2);

	ConfigDAC();
}

void ConfigDAC()
{
	EALLOW;
	// CS
	GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0;         // GPIO
	GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;          // output
	GpioCtrlRegs.GPAQSEL1.bit.GPIO0 = 0;        //Synch to SYSCLKOUT only
	GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1; 			//disable pull up
	GpioDataRegs.GPASET.bit.GPIO0 = 1;			// Set CS high

	//MSB

	GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 0;         // GPIO
	GpioCtrlRegs.GPADIR.bit.GPIO20 = 1;          // output
	GpioCtrlRegs.GPAQSEL2.bit.GPIO20 = 0;        //Synch to SYSCLKOUT only
	GpioCtrlRegs.GPAPUD.bit.GPIO20 = 1; 		//disable pull up

	GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0;         // GPIO
	GpioCtrlRegs.GPADIR.bit.GPIO11 = 1;          // output
	GpioCtrlRegs.GPAQSEL1.bit.GPIO11 = 0;        //Synch to SYSCLKOUT only
	GpioCtrlRegs.GPAPUD.bit.GPIO11 = 1; 		//disable pull up

	GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0;         // GPIO
	GpioCtrlRegs.GPADIR.bit.GPIO9 = 1;          // output
	GpioCtrlRegs.GPAQSEL1.bit.GPIO9 = 0;        //Synch to SYSCLKOUT only
	GpioCtrlRegs.GPAPUD.bit.GPIO9 = 1; 			//disable pull up

	GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 0;         // GPIO
	GpioCtrlRegs.GPADIR.bit.GPIO5 = 1;          // output
	GpioCtrlRegs.GPAQSEL1.bit.GPIO5 = 0;        //Synch to SYSCLKOUT only
	GpioCtrlRegs.GPAPUD.bit.GPIO5 = 1; 			//disable pull up

	GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 0;         // GPIO
	GpioCtrlRegs.GPADIR.bit.GPIO18 = 1;          // output
	GpioCtrlRegs.GPAQSEL2.bit.GPIO18 = 0;        //Synch to SYSCLKOUT only
	GpioCtrlRegs.GPAPUD.bit.GPIO18 = 1; 		//disable pull up

	GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 0;         // GPIO
	GpioCtrlRegs.GPADIR.bit.GPIO17 = 1;          // output
	GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 0;        //Synch to SYSCLKOUT only
	GpioCtrlRegs.GPAPUD.bit.GPIO17 = 1; 		//disable pull up

	GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 0;         // GPIO
	GpioCtrlRegs.GPADIR.bit.GPIO8 = 1;          // output
	GpioCtrlRegs.GPAQSEL1.bit.GPIO8 = 0;        //Synch to SYSCLKOUT only
	GpioCtrlRegs.GPAPUD.bit.GPIO8 = 1; 			//disable pull up

	GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 0;         // GPIO
	GpioCtrlRegs.GPADIR.bit.GPIO25 = 1;          // output
	GpioCtrlRegs.GPAQSEL2.bit.GPIO25 = 0;        //Synch to SYSCLKOUT only
	GpioCtrlRegs.GPAPUD.bit.GPIO25 = 1; 		//disable pull up

	GpioCtrlRegs.GPBMUX1.bit.GPIO44 = 0;         // GPIO
	GpioCtrlRegs.GPBDIR.bit.GPIO44 = 1;          // output
	GpioCtrlRegs.GPBQSEL1.bit.GPIO44 = 0;        //Synch to SYSCLKOUT only
	GpioCtrlRegs.GPBPUD.bit.GPIO44 = 1; 		//disable pull up

	GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 0;         // GPIO
	GpioCtrlRegs.GPADIR.bit.GPIO16 = 1;          // output
	GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 0;        //Synch to SYSCLKOUT only
	GpioCtrlRegs.GPAPUD.bit.GPIO16 = 1; 		//disable pull up

	GpioCtrlRegs.GPBMUX1.bit.GPIO41 = 0;         // GPIO
	GpioCtrlRegs.GPBDIR.bit.GPIO41 = 1;          // output
	GpioCtrlRegs.GPBQSEL1.bit.GPIO41 = 0;        //Synch to SYSCLKOUT only
	GpioCtrlRegs.GPBPUD.bit.GPIO41 = 1; 		//disable pull up

	GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0;         // GPIO
	GpioCtrlRegs.GPADIR.bit.GPIO6 = 1;          // output
	GpioCtrlRegs.GPAQSEL1.bit.GPIO6 = 0;        //Synch to SYSCLKOUT only
	GpioCtrlRegs.GPAPUD.bit.GPIO6 = 1; 			//disable pull up

	//LSB
	EDIS;
}


void SensorCovMeasure()
{
	#define R1 10000.0 //Before ADC, Ohms
	#define R2 20000.0
	#define V5 5.08
	#define B 1568.583480 //Ohm

	SensorCovSystemInit();

	//todo USER: Sensor Conversion
	//update data_temp and ops_temp
	//use stopwatch to catch timeouts
	//waiting should poll isStopWatchComplete() to catch timeout and throw StopWatchError

	//data_temp.MotorVelocity.F32;

	PerformSystemChecks();
}

void LatchStruct()
{
	LatchSystemStruct();
	ops_temp = user_ops;
	data_temp = user_data;
}

void UpdateStruct()
{
	SaveOpStates();
	user_data = data_temp;
	//todo USER: UpdateStruct
	//update with node specific op changes

	//if ops is not changed outside of sensor conversion copy temp over, otherwise don't change

	//Change bit is only set by ops changes outside of SensorCov.


	DetermineOpStates();
}

void SensorCovDeInit()
{
	//todo USER: SensorCovDeInit()
	SystemSensorDeInit();
}
