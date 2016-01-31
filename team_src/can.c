/*
 * can.c
 *
 *  Created on: Nov 12, 2013
 *      Author: Nathan
 */
#include "all.h"

struct ECAN_REGS ECanaShadow;

/*
 * Function responsible for initializing the CAN module.
 *
 * For simple CAN setup the function CreateCANMailbox can be used to specify user
 * mailboxes.
 */
void CANSetup()
{
	//System specific CAN setup
	SystemCANInit(&ECanaShadow);

	EALLOW;
	//MBOX 0 - 1
	CommandBoxInit(COMMAND_ID);   // Mbox 0
	HeartbeatBoxInit(HEARTBEAT_ID); // Mbox 1
	/*
	* todo USER: Node specifc CAN setup
	* create mailbox for all Receive and transmit IDs
	* MBOX2 - MBOX31
    *
	* CreateCANMailbox(int mailboxNum, int IDE, int AME, int AAM, int DLC, int STDMSGID, int Mode)
	*/

	//adc TRANSMIT
	//CreateCANMailbox(2,0,0,1,8,ADC_ID,0);
	//gp_button TRANSMIT
	//CreateCANMailbox(3,0,0,1,8,GP_BUTTON_ID,0);


	CreateCANMailbox(CellTemp1_BOX, 0, 0, 1, 8, CellTemp1_ID, 1);
	CreateCANMailbox(CellTemp2_BOX, 0, 0, 1, 8, CellTemp2_ID, 1);
	CreateCANMailbox(CellTemp3_BOX, 0, 0, 1, 8, CellTemp3_ID, 1);
	CreateCANMailbox(CellTemp4_BOX, 0, 0, 1, 4, CellTemp4_ID, 1);
	CreateCANMailbox(CellTemp5_BOX, 0, 0, 1, 8, CellTemp5_ID, 1);
	CreateCANMailbox(CellTemp6_BOX, 0, 0, 1, 8, CellTemp6_ID, 1);
	CreateCANMailbox(CellTemp7_BOX, 0, 0, 1, 8, CellTemp7_ID, 1);
	CreateCANMailbox(CellTemp8_BOX, 0, 0, 1, 8, CellTemp8_ID, 1);
	CreateCANMailbox(CellTemp9_BOX, 0, 0, 1, 8, CellTemp9_ID, 1);
	CreateCANMailbox(CellTemp10_BOX, 0, 0, 1, 8, CellTemp10_ID, 1);
	CreateCANMailbox(CellTemp11_BOX, 0, 0, 1, 8, CellTemp11_ID, 1);
	CreateCANMailbox(CellTemp12_BOX, 0, 0, 1, 4, CellTemp12_ID, 1);
	CreateCANMailbox(CellTemp13_BOX, 0, 0, 1, 8, CellTemp13_ID, 1);
	CreateCANMailbox(CellTemp14_BOX, 0, 0, 1, 8, CellTemp14_ID, 1);
	CreateCANMailbox(CellTemp15_BOX, 0, 0, 1, 8, CellTemp15_ID, 1);
	CreateCANMailbox(CellTemp16_BOX, 0, 0, 1, 8, CellTemp16_ID, 1);
	CreateCANMailbox(CellTemp17_BOX, 0, 0, 1, 8, CellTemp17_ID, 1);
	CreateCANMailbox(CellTemp18_BOX, 0, 0, 1, 8, CellTemp18_ID, 1);
	CreateCANMailbox(RPM_BOX, 0, 0, 1, 8, RPM_ID, 1);
	CreateCANMailbox(BIM1_BOX, 0, 0 , 1, 8, BIM1_ID, 1);
	CreateCANMailbox(BIM2_BOX, 0, 0 , 1, 8, BIM2_ID, 1);
	CreateCANMailbox(BIM3_BOX, 0, 0 , 1, 8, BIM3_ID, 1);
	CreateCANMailbox(BIM4_BOX, 0, 0 , 1, 8, BIM4_ID, 1);
	CreateCANMailbox(BIM5_BOX, 0, 0 , 1, 8, BIM5_ID, 1);



    EDIS;
    FinishCANInit();
}

char FillCAN(unsigned int Mbox)
{
	CopyMCToShadow(&ECanaShadow);

	//Try to fill heartbeat. If not heartbeat mailbox, see if it's a user mailbox
	if(FillHeartbeat(Mbox, user_ops.UserFlags.all) != 1)
	{
		//todo USER: setup for all transmit MBOXs
		//InsertCANMessage(int Mbox, unsigned int MDH, unsigned int MDL)
		switch (Mbox)
		{
		case DriverControl_BOX:
			InsertCANMessage(DriverControl_BOX, user_data.driver_control_limits.U32, user_data.driver_control_limits.U32);
		case DriverThrottle_BOX:
			InsertCANMessage(DriverThrottle_BOX, user_data.throttle_percent.U32, user_data.throttle_percent.U32);
		default:
			return 0;
		}
	}
	else
	{
		return 1;
	}
}

void FillCANData()
{
	//todo USER: use FillCAN to put data into correct mailboxes
	FillCAN(CellTemp1_BOX);
	FillCAN(CellTemp2_BOX);
	FillCAN(CellTemp3_BOX);
	FillCAN(CellTemp4_BOX);
	FillCAN(CellTemp5_BOX);
	FillCAN(CellTemp6_BOX);
	FillCAN(CellTemp7_BOX);
	FillCAN(CellTemp8_BOX);
	FillCAN(CellTemp9_BOX);
	FillCAN(CellTemp10_BOX);
	FillCAN(CellTemp11_BOX);
	FillCAN(CellTemp12_BOX);
	FillCAN(CellTemp13_BOX);
	FillCAN(CellTemp14_BOX);
	FillCAN(CellTemp15_BOX);
	FillCAN(CellTemp16_BOX);
	FillCAN(CellTemp17_BOX);
	FillCAN(CellTemp18_BOX);
	FillCAN(BIM1_BOX);
	FillCAN(BIM2_BOX);
	FillCAN(BIM3_BOX);
	FillCAN(BIM4_BOX);
	FillCAN(BIM5_BOX);
	FillCAN(DriverControl_BOX);
	FillCAN(DriverThrottle_BOX);
	FillCAN(RPM_BOX);
}

// INT9.6
__interrupt void ECAN1INTA_ISR(void)  // eCAN-A
{
	Uint32 ops_id;
	Uint32 dummy;
  	unsigned int mailbox_nr;
  	mailbox_nr = getMailboxNR();
  	//todo USER: Setup ops command
  	//CAN RECEIVE
  	switch (mailbox_nr)
  	{
  	case COMMAND_BOX:
  		ReadCommand();
  	case CellTemp1_BOX:
  		user_data.CellTemp1.U32 = ECanaMboxes.MBOX2.MDL.all;
  	case CellTemp2_BOX:
  	  	user_data.CellTemp2.U32 = ECanaMboxes.MBOX3.MDL.all;
  	case CellTemp3_BOX:
  	  	user_data.CellTemp3.U32 = ECanaMboxes.MBOX4.MDL.all;
  	case CellTemp4_BOX:
  	  	user_data.CellTemp4.U32 = ECanaMboxes.MBOX5.MDL.all;
  	case CellTemp5_BOX:
  	  	user_data.CellTemp5.U32 = ECanaMboxes.MBOX6.MDL.all;
  	case CellTemp6_BOX:
  	  	user_data.CellTemp6.U32 = ECanaMboxes.MBOX7.MDL.all;
  	case CellTemp7_BOX:
  	  	user_data.CellTemp7.U32 = ECanaMboxes.MBOX8.MDL.all;
  	case CellTemp8_BOX:
  	  	user_data.CellTemp8.U32 = ECanaMboxes.MBOX9.MDL.all;
  	case CellTemp9_BOX:
  	  	user_data.CellTemp9.U32 = ECanaMboxes.MBOX10.MDL.all;
  	case CellTemp10_BOX:
  	  	user_data.CellTemp10.U32 = ECanaMboxes.MBOX11.MDL.all;
  	case CellTemp11_BOX:
  	  	user_data.CellTemp11.U32 = ECanaMboxes.MBOX12.MDL.all;
  	case CellTemp12_BOX:
  	  	user_data.CellTemp12.U32 = ECanaMboxes.MBOX13.MDL.all;
  	case CellTemp13_BOX:
  	  	user_data.CellTemp13.U32 = ECanaMboxes.MBOX14.MDL.all;
  	case CellTemp14_BOX:
  	  	user_data.CellTemp14.U32 = ECanaMboxes.MBOX15.MDL.all;
  	case CellTemp15_BOX:
  	  	user_data.CellTemp15.U32 = ECanaMboxes.MBOX16.MDL.all;
  	case CellTemp16_BOX:
  	  	user_data.CellTemp16.U32 = ECanaMboxes.MBOX17.MDL.all;
  	case CellTemp17_BOX:
  	  	user_data.CellTemp17.U32 = ECanaMboxes.MBOX18.MDL.all;
  	case CellTemp18_BOX:
  	  	user_data.CellTemp18.U32 = ECanaMboxes.MBOX19.MDL.all;
  	case RPM_BOX:
  		user_data.RPM.U32 = ECanaMboxes.MBOX20.MDL.all;
  	case BIM1_BOX:
  		user_data.BIM1.U32 = ECanaMboxes.MBOX21.MDL.all;
  	case BIM2_BOX:
  	  	user_data.BIM2.U32 = ECanaMboxes.MBOX22.MDL.all;
  	case BIM3_BOX:
  	  	user_data.BIM3.U32 = ECanaMboxes.MBOX23.MDL.all;
  	case BIM4_BOX:
  	  	user_data.BIM4.U32 = ECanaMboxes.MBOX24.MDL.all;
  	case BIM5_BOX:
  	  	user_data.BIM5.U32 = ECanaMboxes.MBOX25.MDL.all;
  	}
  	//todo USER: Setup other reads

  	//To receive more interrupts from this PIE group, acknowledge this interrupt
  	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
}

// INT9.5
__interrupt void ECAN0INTA_ISR(void)   // eCAN-A
{

	// To receive more interrupts from this PIE group, acknowledge this interrupt
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
}
