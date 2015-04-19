/*
 * can.h
 *
 *  Created on: Nov 13, 2013
 *      Author: Nathan
 */

#ifndef CAN_H_
#define CAN_H_

void CANSetup();
char FillCAN(unsigned int Mbox);
void FillCANData();
void FillSendCAN(unsigned int Mbox);
void ClearMailBoxes();
void BUS_OFF();

//todo USER: DEFINE IDs for all output
//           DEFINE mailboxes for all output except heartbeat and command
//			 Mailboxes and ID's 0 or 1 are reserved for system use.

//#define COMMAND_ID 			0x3E8
#define HEARTBEAT_ID 			307

#define CONTACTOR_BOX_ID 		303
#define CONTACTOR_BOX_BOX 		2
#define CONTACTOR_BOX_TRS 		TRS2

#define FRAME_FAULT_ID			305
#define FRAME_FAULT_BOX			3
#define FRAME_FAULT_TRS			TRS3

#define SHUNTS_ID				304
#define SHUNTS_BOX				4
#define SHUNTS_TRS				TRS4

#define REAR_WHEEL_SPEED_ID		301
#define REAR_WHEEL_SPEED_BOX	5
#define REAR_WHEEL_SPEED_TRS	TRS5

#define REAR_BRAKE_ID			306
#define REAR_BRAKE_BOX			6
#define REAR_BRAKE_TRS			RS6

#define REAR_SUSPENSION_ID		300
#define REAR_SUSPENSION_BOX		7
#define REAR_SUSPENSION_TRS		TRS7





#endif /* CAN_H_ */
