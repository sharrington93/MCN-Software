/*
 * data.h
 *
 *  Created on: Oct 30, 2013
 *      Author: Nathan
 */

#ifndef DATA_H_
#define DATA_H_

typedef union CANFLOAT
{
	float F32;
	unsigned long U32;
} canfloat;

typedef struct USER_DATA
{
	canfloat DC_DC_temp;
	int frame_fault;
	canfloat v12_shunt;
	canfloat wheel_speed;
	canfloat rear_brake;
	canfloat rear_susp;
	canfloat v1_5;
	canfloat v2_3;
	canfloat v3_3;
	canfloat v12;
	canfloat v12_standby;
} user_data_struct;

#endif /* DATA_H_ */
