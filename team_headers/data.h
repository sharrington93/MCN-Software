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
	canfloat CellTemp1;
	canfloat CellTemp2;
	canfloat CellTemp3;
	canfloat CellTemp4;
	canfloat CellTemp5;
	canfloat CellTemp6;
	canfloat CellTemp7;
	canfloat CellTemp8;
	canfloat CellTemp9;
	canfloat CellTemp10;
	canfloat CellTemp11;
	canfloat CellTemp12;
	canfloat CellTemp13;
	canfloat CellTemp14;
	canfloat CellTemp15;
	canfloat CellTemp16;
	canfloat CellTemp17;
	canfloat CellTemp18;
	canfloat BIM1;
	canfloat BIM2;
	canfloat BIM3;
	canfloat BIM4;
	canfloat BIM5;
	canfloat throttle_percent;
	canfloat RPM;
	canfloat max_cell_temp;
	canfloat battery_limit;
	canfloat rpm_limit;
	canfloat status_limit;
	canfloat throttle_lock;
	canfloat driver_control_limits;
	char gp_button;
} user_data_struct;

#endif /* DATA_H_ */
