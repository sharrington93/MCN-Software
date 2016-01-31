/*
 * Init.c
 *
 *  Created on: Oct 30, 2013
 *      Author: Nathan
 */

#include "all.h"


user_ops_struct user_ops;
user_data_struct user_data;

void Initialize()
{
	OperationsSetup();
	DataSetup();
	CANSetup();
	ClockSetup();
	StartPowerDownInt();			//start power down interrupt, this will change state to PowerDown if necessary
	StopWatchSetUp(10);
}

void OperationsSetup()
{
	//todo USER: OperationsSetup()
	//add here and ops.h
	SetupSystemOperations();
}

void DataSetup()
{
	//todo USER: DataSetup()
	//add here and data.h
	user_data.CellTemp1.U32 = 0;
	user_data.CellTemp2.U32 = 0;
	user_data.CellTemp3.U32 = 0;
	user_data.CellTemp4.U32 = 0;
	user_data.CellTemp5.U32 = 0;
	user_data.CellTemp6.U32 = 0;
	user_data.CellTemp7.U32 = 0;
	user_data.CellTemp8.U32 = 0;
	user_data.CellTemp9.U32 = 0;
	user_data.CellTemp10.U32 = 0;
	user_data.CellTemp11.U32 = 0;
	user_data.CellTemp12.U32 = 0;
	user_data.CellTemp13.U32 = 0;
	user_data.CellTemp14.U32 = 0;
	user_data.CellTemp15.U32 = 0;
	user_data.CellTemp16.U32 = 0;
	user_data.CellTemp17.U32 = 0;
	user_data.CellTemp18.U32 = 0;
	user_data.BIM1.U32 = 0;
	user_data.BIM2.U32 = 0;
	user_data.BIM3.U32 = 0;
	user_data.BIM4.U32 = 0;
	user_data.BIM5.U32 = 0;
	user_data.throttle_percent.U32 = 0;
	user_data.RPM.U32 = 0;
	user_data.max_cell_temp.U32 = 0;
	user_data.battery_limit.U32 = 0;
	user_data.rpm_limit.U32 = 0;
	user_data.status_limit.U32 = 0;
	user_data.throttle_lock.U32 = 0;
	user_data.driver_control_limits.U32 = 0;
}

