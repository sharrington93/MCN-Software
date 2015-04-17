/*
 * SensorCov.h
 *
 *  Created on: Oct 30, 2013
 *      Author: Nathan
 */

#ifndef SENSORCOV_H_
#define SENSORCOV_H_

void SensorCov();
void SensorCovInit();
void SensorCovMeasure();
void LatchStruct();
void UpdateStruct();
void SensorCovDeInit();

#define FULL_SCALE 		(4096*0.9)

/*
 * alpha = (1.0 - exp(-2.0 * PI * (CANFrequency / samplingFrequency))) * 2^16;
 */

#define ALPHA_REAR_SUSP				206
#define REAR_SUSP_VALUE				A7filter.filtered_value

#define ALPHA_REAR_BRAKE			206
#define REAR_BRAKE_VALUE			A3filter.filtered_value

#define ALPHA_12V_SHUNT				206
#define V12_SHUNT_VALUE				A1filter.filtered_value

#define ALPHA_1_5V					206
#define V1_5_VALUE					B6filter.filtered_value

#define ALPHA_2_3V					206
#define V2_3_VALUE					B4filter.filtered_value

#define ALPHA_3_3V					206
#define V3_3_VALUE					B3filter.filtered_value

#define ALPHA_12V					206
#define V12_VALUE					B0filter.filtered_value

#define ALPHA_DC_TEMP				206
#define DC_TEMP_VALUE				B2filter.filtered_value

#define ALPHA_12V_STANDBY			206
#define V12_STANDBY_VALUE			A0filter.filtered_value

#define ALPHA_WHEEL_SPEED			206
#define WHEEL_SPEED_VALUE			GPIO26filter.filtered_value

#define ALPHA_FRAME_FAULT			206
#define FRAME_FAULT_VALUE			GPIO19filter.filtered_value


#define SENSOR_COV_STOPWATCH 100000

#endif /* SENSORCOV_H_ */
