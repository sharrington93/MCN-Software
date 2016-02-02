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


int max = 2000, min = 2000, i;
float r_th;
float throttle_ratio;
int RPM_ratio = 0;

//possible battery cell temperatures
static const int BAT_THROTTLE_TEMP[100] = {-30, -29, -28, -27, -26, -25, -24, -23, -22, -21, -20,
									-19, -18, -17, -16, -15, -14, -13, -12, -11, -10, -9,
									-8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6,
									 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,18, 19, 20,
									 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33,
									 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46,
									 47,48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60 , 61, 62, 63, 64, 65 ,66, 67 ,68 ,69};

//throttle percentages
static const int BAT_THROTTLE[32] = {100, 97, 94, 91, 88, 85, 82, 79,
							   76, 73, 70, 67, 64, 61, 58, 55, 52, 49, 46, 43, 40, 37, 34,
							   31, 28, 25, 20, 15, 10, 5, 0};

//array storing the battery temperatures
float BATT_CELL_TEMPS[18] = {user_data.CellTemp1.F32, user_data.CellTemp2.F32, user_data.CellTemp3.F32,
		                     user_data.CellTemp4.F32, user_data.CellTemp5.F32, user_data.CellTemp6.F32,
							 user_data.CellTemp7.F32, user_data.CellTemp8.F32, user_data.CellTemp9.F32,
							 user_data.CellTemp10.F32, user_data.CellTemp11.F32, user_data.CellTemp12.F32,
							 user_data.CellTemp13.F32, user_data.CellTemp14.F32, user_data.CellTemp15.F32,
							 user_data.CellTemp16.F32, user_data.CellTemp17.F32, user_data.CellTemp18.F32};

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
}

void SensorCovMeasure()
{
#define R1 10000.0 //Before ADC, Ohms
#define R2 20000.0
#define V5 5.08
#define B 1568.583480 //Ohm

	//initialize used variables
	int THROTTLE_LOOKUP = 0;
	int BIM_STATUS = 0;
	float MinMax = 0.0;
	throttle_ratio = (A7RESULT/4096.0) * 100;

	//*******************************************************************************************************
	//*                                           TODO                                                      *
	//*                 Create function that accesses all arrays and acts accordingly                       *
	//*                                                                                                     *
	//*******************************************************************************************************


	//loop looks through the battery temperature array and deterimines the maximum temperature
	for (i = 0; i < 18; i++){
		if (BATT_CELL_TEMPS[i] > user_data.max_cell_temp.F32){
			user_data.max_cell_temp.F32 = BATT_CELL_TEMPS[i];
		}
	}

	//loop looks up the maximum temperature value to the closest value in the BATT_THROTTLE_TEMP array
	for (i = 0; i < 100; i++){
		if ((user_data.max_cell_temp.F32 < BAT_THROTTLE_TEMP[i+1]) && (user_data.max_cell_temp.F32 >= BAT_THROTTLE_TEMP[i])){
			//stores this value to look up the coorosponding throttle percentage
			THROTTLE_LOOKUP = i;
			break;
		}
	}

	//lookup the corrosponding throttle percentage
	if (THROTTLE_LOOKUP <= 69){
		user_data.throttle_percent.U32 = BAT_THROTTLE[0];
	}
	else {
		//lookup corrosponding RPM
		user_data.throttle_percent.U32 = BAT_THROTTLE[THROTTLE_LOOKUP-69];
	}

	if ((user_data.RPM.U32 > 0) && (user_data.RPM.U32)){
		RPM_ratio = 100;
	}

	//Check for limmiting factor
	if (throttle_ratio < RPM_ratio) {
		MinMax = throttle_ratio;
	}
	else {
		MinMax = RPM_ratio;
	}

	// check if battery limmit is the limmiting factor
	if (((throttle_ratio > 1) && (throttle_ratio < 101)) && (throttle_ratio == MinMax)){
		user_data.battery_limit.U32 = 1;
	}
	//check if rpm is the limmiting factor
	else if (((throttle_ratio > 1) && (throttle_ratio < 101)) && (RPM_ratio == MinMax)){
	    user_data.rpm_limit.U32 = 1;
	}

	BIM_STATUS = user_data.BIM1.U32 + user_data.BIM2.U32 + user_data.BIM3.U32 + user_data.BIM4.U32 + user_data.BIM5.U32;

	if (BIM_STATUS == 5){
		user_data.status_limit.U32 = 1;
	}

	//sending the driver control limmits information
	int limits = 0;
	limits += user_data.status_limit.U32 << 3;
	limits += user_data.rpm_limit.U32 << 2;
	limits += user_data.battery_limit.U32 << 1;
	limits += user_data.throttle_lock.U32;

	ECanaMboxes.MBOX31.MDL.byte.BYTE0 = limits;
	user_data.driver_control_limits.U32 = ECanaMboxes.MBOX31.MDL.byte.BYTE0;

	int percent_out = 0;
	percent_out += user_data.throttle_percent.U32 >> 24;

	ECanaMboxes.MBOX20.MDH.byte.BYTE4 = percent_out;
	user_data.throttle_percent.U32 = ECanaMboxes.MBOX20.MDH.byte.BYTE4;

	SensorCovSystemInit();

	//todo USER: Sensor Conversion
	//update data_temp and ops_temp
	//use stopwatch to catch timeouts
	//waiting should poll isStopWatchComplete() to catch timeout and throw StopWatchError


	/*data_temp.coolant_flow.F32 = (GPIO26filter.filtered_value*0.283);

	data_temp.motor_coolant_temp.F32 = 70.0*(A4RESULT/4096.0);
	data_temp.motor_control_coolant_temp.F32 = (140.0*(A5RESULT/4096.0)) - 50;
	data_temp.radiator_coolant_temp.F32 = (140.0*(A0RESULT/4096.0)) - 50;
	*/

	/*v_in = 3.3*(A4RESULT/4096.0);
	r_th = -1.0*(R1*R2*v_in)/((-1.0*R2*V5)+(R1*v_in)+(R2*v_in));
	data_temp.motor_coolant_temp.F32 = (3435.0)/(log((r_th/0.0991912))) - 273.15;

	v_in = 3.3*(A5RESULT/4096.0);
	r_th = -1.0*(R1*R2*v_in)/((-1.0*R2*V5)+(R1*v_in)+(R2*v_in));
	data_temp.motor_control_coolant_temp.F32 = (3435.0)/(log((r_th/0.0991912))) - 273.15;

	v_in = 3.3*(A0RESULT/4096.0);
	r_th = -1.0*(R1*R2*v_in)/((-1.0*R2*V5)+(R1*v_in)+(R2*v_in));
	data_temp.radiator_coolant_temp.F32 = (3435.0)/(log((r_th/0.0991912))) - 273.15;

	v_in = 3.3*(B1RESULT/4096.0);
	r_th = -1.0*(R1*R2*v_in)/((-1.0*R2*V5)+(R1*v_in)+(R2*v_in));
	data_temp.motor_plate_temp_1.F32 = (3380.0)/(log((r_th/0.119286))) - 273.15;

	v_in = 3.3*(A1RESULT/4096.0);
	r_th = -1.0*(R1*R2*v_in)/((-1.0*R2*V5)+(R1*v_in)+(R2*v_in));
	data_temp.motor_plate_temp_2.F32 = (3380.0)/(log((r_th/0.119286))) - 273.15;

	v_in = 3.3*(B4RESULT/4096.0);
	r_th = -1.0*(R1*R2*v_in)/((-1.0*R2*V5)+(R1*v_in)+(R2*v_in));
	data_temp.ambient_temp.F32 = (3380.0)/(log((r_th/0.119286))) - 273.15;

	data_temp.motor_temp.F32 = (pow((B3RESULT/4096.0),2)*2380.13) + ((B3RESULT/4096.0)*940.533) - 232.125;

	v_in = 3.3*(A7RESULT/4096.0);
	data_temp.coolant_pressure_1.F32 = (37.5/V5)*(1.56*v_in) - 3.75;

	v_in = 3.3*(A3RESULT/4096.0);
	data_temp.coolant_pressure_2.F32 = (37.5/V5)*(1.56*v_in) - 3.75;

} */


	data_temp.gp_button = READGPBUTTON();
	/*
	if(A7RESULT > max)
	{
		max = A7RESULT;
	}
	if(A7RESULT < min)
	{
		min = A7RESULT;
	}
	*/
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
