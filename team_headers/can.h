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

#define COMMAND_ID 		0x3E8
#define HEARTBEAT_ID 	0x3E7

#define MOTOR_VELOCITY_ID 		0x403
#define MOTOR_VELOCITY_BOX 		2
#define MOTOR_VELOCITY_TRS 		TRS2




#endif /* CAN_H_ */
