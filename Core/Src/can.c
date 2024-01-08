#include"main.h"

union BitGroup_TypeDef g_CanMcuEvent;
union BitGroup_TypeDef g_CanBmsEvent;
union BitGroup_TypeDef g_CanBms1Event;

MCU_FAULT_TypeDef g_McuFaultInfor;
MCU_RUNINFOR_TypeDef  g_McuRunInfor;
MCU_POWEROUT_TypeDef g_McuPowerOut;
MCU_SYSINFOR1_TypeDef  g_McuSysInfor1;
MCU_SYSINFOR2_TypeDef  g_McuSysInfor2;
MCU_FUNSWCH_TypeDef g_McuFunSwitch;


BMS_RT_STATUS1_TypeDef g_BmsRtStatus1;
BMS_RT_STATUS2_TypeDef g_BmsRtStatus2;
BMS_RT_STATUS3_TypeDef g_BmsRtStatus3;


BMS_CELLVOLT1_TypeDef g_BmsCellVolt1;
BMS_CELLVOLT2_TypeDef g_BmsCellVolt2;
BMS_CELLVOLT3_TypeDef g_BmsCellVolt3;
BMS_CELLVOLT4_TypeDef g_BmsCellVolt4;
BMS_CELLVOLT5_TypeDef g_BmsCellVolt5;
BMS_CELLVOLT6_TypeDef g_BmsCellVolt6;

BMS_RTTEMP_TypeDef g_BmsRtTemp;

BMS_SYSINFOR_TypeDef g_BmsSysInfor;

VCU_WDG_TypeDef g_Vcu_0x00632;
VCU_WDG_REFRESH_TypeDef g_Vcu_0x00633;

CAN_TXSTATE_TypeDef g_CanTransmitState;


void CanRamInit(void)
{
	g_CanMcuEvent.BYTE=0;
	g_CanBmsEvent.BYTE=0;
	g_CanBms1Event.BYTE=0;

	memset((uint8_t*)&g_McuFaultInfor,0x00,8);
	memset((uint8_t*)&g_McuRunInfor,0x00,8);
	memset((uint8_t*)&g_McuPowerOut,0x00,8);
	memset((uint8_t*)&g_McuSysInfor1,0x00,8);
	memset((uint8_t*)&g_McuSysInfor2,0x00,8);
	memset((uint8_t*)&g_McuFunSwitch,0x00,8);

	memset((uint8_t*)&g_BmsRtStatus1,0x00,8);
	memset((uint8_t*)&g_BmsRtStatus2,0x00,8);
	memset((uint8_t*)&g_BmsRtStatus3,0x00,8);

	memset((uint8_t*)&g_BmsCellVolt5,0x00,8);
	memset((uint8_t*)&g_BmsCellVolt5,0x00,8);
	memset((uint8_t*)&g_BmsCellVolt5,0x00,8);
	memset((uint8_t*)&g_BmsCellVolt5,0x00,8);
	memset((uint8_t*)&g_BmsCellVolt5,0x00,8);
	memset((uint8_t*)&g_BmsCellVolt5,0x00,8);

	memset((uint8_t*)&g_BmsRtTemp,0x00,8);
	
	memset((uint8_t*)&g_BmsSysInfor,0x00,8);

	memset((uint8_t*)&g_CanTransmitState,0x00,sizeof(g_CanTransmitState));

}

void CanMcuParse(uint32_t id,uint8_t *data,uint8_t len)
{

	switch(id)
	{
		case 0x01806E502:
			memcpy((uint8_t*)&g_McuSysInfor1,data,len);
			McuSysInfor1Event=TRUE;
			break;
		case 0x01806E503:
			memcpy((uint8_t*)&g_McuSysInfor2,data,len);
			McuSysInfor2Event=TRUE;
			break;
		case 0x01806E600:
			memcpy((uint8_t*)&g_McuFaultInfor,data,len);
			McuFaultEvent=TRUE;
			break;
		case 0x01806E601:
			memcpy((uint8_t*)&g_McuRunInfor,data,len);
			McuRunInforEvent=TRUE;
			break;
		case 0x01806E602:
			memcpy((uint8_t*)&g_McuPowerOut,data,len);
			McuPwrOutEvent=TRUE;
			break;
		}

	
}

void CanBmsParse(uint32_t id,uint8_t *data,uint8_t len)
{
	switch(id)
	{
		case 0x01806E516:
			memcpy((uint8_t*)&g_BmsSysInfor,data,len);
			BmsSysInforEvent=TRUE;
			break;
		case 0x01806E610:
			memcpy((uint8_t*)&g_BmsRtStatus1,data,len);
			BmsRtState1Event=TRUE;
			break;
		case 0x01806E611:
			memcpy((uint8_t*)&g_BmsRtStatus2,data,len);
			BmsRtState2Event=TRUE;
			break;
		case 0x01806E612:
			memcpy((uint8_t*)&g_BmsRtStatus3,data,len);
			BmsRtState3Event=TRUE;
			break;
		case 0x01806E613:
			memcpy((uint8_t*)&g_BmsCellVolt1,data,len);
			BmsCellVolt1Event=TRUE;
			break;
		case 0x01806E614:
			memcpy((uint8_t*)&g_BmsCellVolt2,data,len);
			BmsCellVolt2Event=TRUE;
			break;
		case 0x01806E615:
			memcpy((uint8_t*)&g_BmsCellVolt3,data,len);
			BmsCellVolt3Event=TRUE;
			break;
		case 0x01806E616:
			memcpy((uint8_t*)&g_BmsCellVolt4,data,len);
			BmsCellVolt4Event=TRUE;
			break;
		case 0x01806E617:
			memcpy((uint8_t*)&g_BmsCellVolt5,data,len);
			BmsCellVolt5Event=TRUE;
			break;
		case 0x01806E618:
			memcpy((uint8_t*)&g_BmsCellVolt6,data,len);
			BmsCellVolt6Event=TRUE;
			break;	
		case 0x01806E620:
			memcpy((uint8_t*)&g_BmsRtTemp,data,len);
			BmsRtTempEvent=TRUE;
			break;
		}
	
}

void CanTransmit(uint32_t id,uint8_t *data,uint8_t len)
{
	can_trasnmit_message_struct transmit_message;
	
	can_struct_para_init(CAN_TX_MESSAGE_STRUCT, &transmit_message);
    transmit_message.tx_sfid = 0x00;
    transmit_message.tx_efid = id;
    transmit_message.tx_ft = CAN_FT_DATA;
    transmit_message.tx_ff = CAN_FF_EXTENDED;
    transmit_message.tx_dlen = 8;
	memcpy(transmit_message.tx_data,data,len);
	can_message_transmit(CAN0, &transmit_message);
}
void CanProc(void)
{
	uint16_t temp16;
	uint32_t temp32;
    int16_t tempInt16;
	uint8_t *p_u8;
	uint32_t power;
		
    if(HAL_GetTick()-g_CanTransmitState.t1000ms>=1000)
    {
    	g_CanTransmitState.t1000ms=HAL_GetTick();

		g_Vcu_0x00633.Heartbeat=1;
		g_Vcu_0x00633.Wdgrefresh=1;
		CanTransmit(0x1806E633,(uint8_t*)&g_Vcu_0x00633,8);
    	}

	if(McuFaultEvent)
	{
		McuFaultEvent=FALSE;
		tempInt16=g_McuFaultInfor.ContrlTemp-40;
		GattSetData(LIST_DTA,DTA_CTMP,(uint8_t*)&tempInt16);
		
		tempInt16=g_McuFaultInfor.MotorTemp-40;
		GattSetData(LIST_DTA,DTA_MTPM,(uint8_t*)&tempInt16);

		SetDashBoardData(LIST_gearlevel,g_McuFaultInfor.GearState);
		SetDashBoardData(LIST_reverse,g_McuFaultInfor.ReverseState);

		SetDashBoardData(LIST_check,g_McuFaultInfor.BrakeState);
		SetDashBoardData(LIST_electrical,g_McuFaultInfor.MotorBlock_fault|g_McuFaultInfor.MotorHall_fault
			|g_McuFaultInfor.MotorOverTemp_fault|g_McuFaultInfor.MotorPhaseLost_fault);
		SetDashBoardData(LIST_handle,g_McuFaultInfor.Throttle_fault);
		SetDashBoardData(LIST_Ecu,0);
		if(g_McuFaultInfor.PauseDisableStae)
			SetDashBoardData(LIST_parking,TRUE);
		else
			SetDashBoardData(LIST_parking,FALSE);
		
		}
	
	if(McuRunInforEvent)
	{
		temp16=(g_McuRunInfor.MotorSpeedH<<8)|g_McuRunInfor.MotorSpeedL;
		GattSetData(LIST_DTA,DTA_MTRD,(uint8_t*)&temp16);
		SetDashBoardData(LIST_speed, (uint16_t)temp16*0.0129); // *0.01294

		temp16=(g_McuRunInfor.TyreSpeedH<<8)|g_McuRunInfor.TyreSpeedL;
		GattSetData(LIST_DTA,DTA_TSPD,(uint8_t*)&temp16);

		temp16=(g_McuRunInfor.RtVoltageH<<8)|g_McuRunInfor.RtVoltageL;
		temp16=temp16/10;
		GattSetData(LIST_DTA,DTA_RVLT,(uint8_t*)&temp16);

		tempInt16=(int16_t)((g_McuRunInfor.RtCurrentH<<8)|g_McuRunInfor.RtCurrentL);
		//tempInt16=tempInt16/10;
		//tempInt16-=2000;
		tempInt16*=100;
		GattSetData(LIST_DTA,DTA_RCUR,(uint8_t*)&tempInt16);
		
		McuRunInforEvent=FALSE;
		}
	if(McuPwrOutEvent)
	{

		McuRunInforEvent=FALSE;
		}
	if(McuSysInfor1Event)
	{
		temp16=(g_McuSysInfor1.RateMaxInputCurtH<<8)|g_McuSysInfor1.RateMaxInputCurtL;
		temp16=temp16/10;
		GattSetData(LIST_DTA,DTA_RMAX,(uint8_t*)&temp16);
		McuSysInfor1Event=FALSE;
		}
	if(McuSysInfor2Event)
	{
		McuSysInfor2Event=FALSE;

		temp16=(g_McuSysInfor2.MaxSpeedSetH<<8)|g_McuSysInfor2.MaxSpeedSetL;
		GattSetData(LIST_DTA,DTA_CMXS,(uint8_t*)&temp16);

		temp16=(g_McuSysInfor2.MaxInputCurtSetH<<8)|g_McuSysInfor2.MaxInputCurtSetL;
		GattSetData(LIST_DTA,DTA_CMXC,(uint8_t*)&temp16);
		}

	if(BmsRtState1Event)
	{
		temp32=(g_BmsRtStatus1.RealtimeVoltageH<<8)+g_BmsRtStatus1.RealtimeVoltageL;
		temp32*=100;

		GattSetData(LIST_DTA,DTA_PCKV,(uint8_t*)&temp32);

		SetDashBoardData(LIST_volts,(uint8_t)(temp32/1000));
		
		tempInt16=(int16_t)((g_BmsRtStatus1.RealtimeCurrentH<<8)+g_BmsRtStatus1.RealtimeCurrentL);

		tempInt16-=2000;
		tempInt16*=100;
		
		GattSetData(LIST_DTA,DTA_PCKC,(uint8_t*)&tempInt16);
		if(tempInt16>0)
		{	power=temp32/100*tempInt16/100/100;
			temp16=power;
			GattSetData(LIST_DTA,DTA_BATP,(uint8_t*)&temp16);
			GattSetData(LIST_DTA,DTA_INPP,(uint8_t*)&temp16);
			temp16=0;
			GattSetData(LIST_DTA,DTA_OUTP,(uint8_t*)&temp16);
			}
		else if(tempInt16<0)
		{	power=temp32/100*-tempInt16/100/100;
			temp16=0;
			GattSetData(LIST_DTA,DTA_BATP,(uint8_t*)&temp16);
			GattSetData(LIST_DTA,DTA_INPP,(uint8_t*)&temp16);
			temp16=power;
			GattSetData(LIST_DTA,DTA_OUTP,(uint8_t*)&temp16);
			}
		else
		{
			temp16=0;
			GattSetData(LIST_DTA,DTA_BATP,(uint8_t*)&temp16);
			GattSetData(LIST_DTA,DTA_INPP,(uint8_t*)&temp16);
			GattSetData(LIST_DTA,DTA_OUTP,(uint8_t*)&temp16);
		}

		temp16=g_BmsRtStatus1.ChargingMosOn;
		GattSetData(LIST_DTA,DTA_CMOS,(uint8_t*)&temp16);
		temp16=g_BmsRtStatus1.DisChargeMosOn;
		GattSetData(LIST_DTA,DTA_DMOS,(uint8_t*)&temp16);

		p_u8=(uint8_t*)&g_BmsRtStatus1;
		temp16=p_u8[0]|(p_u8[1]<<8);
		temp16&=0x3ffc;
		GattSetData(LIST_DTA,DTA_PPST,(uint8_t*)&temp16);

		temp16=p_u8[0]&0x03;
		GattSetData(LIST_DTA,DTA_PMCS,(uint8_t*)&temp16);
		BmsRtState1Event=FALSE;
		}
	if(BmsRtState2Event)
	{

		temp16=g_BmsRtStatus2.Soc;
		GattSetData(LIST_DTA,DTA_RSOC,(uint8_t*)&temp16);

		SetDashBoardData(LIST_soc,(uint8_t)temp16);
		BmsRtState2Event=FALSE;
		}
	if(BmsRtState3Event)
	{
		temp16=(g_BmsRtStatus3.CycleNumbH<<8)+g_BmsRtStatus3.CycleNumbL;
		GattSetData(LIST_DTA,DTA_ACYC,(uint8_t*)&temp16);

		temp16=(g_BmsRtStatus3.FullBatCapH<<8)+g_BmsRtStatus3.FullBatCapL;
		temp16/=100;
		GattSetData(LIST_DTA,DTA_FCCP,(uint8_t*)&temp16);

		temp16=(g_BmsRtStatus3.RemainBatCapH<<8)+g_BmsRtStatus3.RemainBatCapL;
		temp16/=100;
		GattSetData(LIST_DTA,DTA_RCAP,(uint8_t*)&temp16);
		BmsRtState3Event=FALSE;
		}
	if(BmsCellVolt1Event)
	{
		temp16=(g_BmsCellVolt1.CellVoltage1H<<8)+g_BmsCellVolt1.CellVoltage1L;
		GattSetData(LIST_DIA,DIA_CV01,(uint8_t*)&temp16);
		temp16=(g_BmsCellVolt1.CellVoltage2H<<8)+g_BmsCellVolt1.CellVoltage2L;
		GattSetData(LIST_DIA,DIA_CV02,(uint8_t*)&temp16);
		temp16=(g_BmsCellVolt1.CellVoltage3H<<8)+g_BmsCellVolt1.CellVoltage3L;
		GattSetData(LIST_DIA,DIA_CV03,(uint8_t*)&temp16);
		temp16=(g_BmsCellVolt1.CellVoltage4H<<8)+g_BmsCellVolt1.CellVoltage4L;
		GattSetData(LIST_DIA,DIA_CV04,(uint8_t*)&temp16);
		
		BmsCellVolt1Event=FALSE;
		}
	if(BmsCellVolt2Event)
	{
		temp16=(g_BmsCellVolt2.CellVoltage5H<<8)+g_BmsCellVolt2.CellVoltage5L;
		GattSetData(LIST_DIA,DIA_CV05,(uint8_t*)&temp16);
		temp16=(g_BmsCellVolt2.CellVoltage6H<<8)+g_BmsCellVolt2.CellVoltage6L;
		GattSetData(LIST_DIA,DIA_CV06,(uint8_t*)&temp16);
		temp16=(g_BmsCellVolt2.CellVoltage7H<<8)+g_BmsCellVolt2.CellVoltage7L;
		GattSetData(LIST_DIA,DIA_CV07,(uint8_t*)&temp16);
		temp16=(g_BmsCellVolt2.CellVoltage8H<<8)+g_BmsCellVolt2.CellVoltage8L;
		GattSetData(LIST_DIA,DIA_CV08,(uint8_t*)&temp16);
		McuSysInfor1Event=FALSE;
		}
	if(BmsCellVolt3Event)
	{
		temp16=(g_BmsCellVolt3.CellVoltage9H<<8)+g_BmsCellVolt3.CellVoltage9L;
		GattSetData(LIST_DIA,DIA_CV09,(uint8_t*)&temp16);
		temp16=(g_BmsCellVolt3.CellVoltage10H<<8)+g_BmsCellVolt3.CellVoltage10L;
		GattSetData(LIST_DIA,DIA_CV10,(uint8_t*)&temp16);
		temp16=(g_BmsCellVolt3.CellVoltage11H<<8)+g_BmsCellVolt3.CellVoltage11L;
		GattSetData(LIST_DIA,DIA_CV11,(uint8_t*)&temp16);
		temp16=(g_BmsCellVolt3.CellVoltage12H<<8)+g_BmsCellVolt3.CellVoltage12L;
		GattSetData(LIST_DIA,DIA_CV12,(uint8_t*)&temp16);
		BmsCellVolt3Event=FALSE;
		}
	if(BmsCellVolt4Event)
	{
		temp16=(g_BmsCellVolt4.CellVoltage13H<<8)+g_BmsCellVolt4.CellVoltage13L;
		GattSetData(LIST_DIA,DIA_CV13,(uint8_t*)&temp16);
		temp16=(g_BmsCellVolt4.CellVoltage14H<<8)+g_BmsCellVolt4.CellVoltage14L;
		GattSetData(LIST_DIA,DIA_CV14,(uint8_t*)&temp16);
		temp16=(g_BmsCellVolt4.CellVoltage15H<<8)+g_BmsCellVolt4.CellVoltage15L;
		GattSetData(LIST_DIA,DIA_CV15,(uint8_t*)&temp16);
		temp16=(g_BmsCellVolt4.CellVoltage16H<<8)+g_BmsCellVolt4.CellVoltage16L;
		GattSetData(LIST_DIA,DIA_CV16,(uint8_t*)&temp16);
		BmsCellVolt4Event=FALSE;
	}
	if(BmsCellVolt5Event)
	{
		temp16=(g_BmsCellVolt5.CellVoltage17H<<8)+g_BmsCellVolt5.CellVoltage17L;
		GattSetData(LIST_DIA,DIA_CV17,(uint8_t*)&temp16);
		temp16=(g_BmsCellVolt5.CellVoltage18H<<8)+g_BmsCellVolt5.CellVoltage18L;
		GattSetData(LIST_DIA,DIA_CV18,(uint8_t*)&temp16);
		temp16=(g_BmsCellVolt5.CellVoltage19H<<8)+g_BmsCellVolt5.CellVoltage19L;
		GattSetData(LIST_DIA,DIA_CV19,(uint8_t*)&temp16);
		temp16=(g_BmsCellVolt5.CellVoltage20H<<8)+g_BmsCellVolt5.CellVoltage20L;
		GattSetData(LIST_DIA,DIA_CV20,(uint8_t*)&temp16);
		BmsCellVolt5Event=FALSE;
		}

	if(BmsCellVolt6Event)
	{
		temp16=(g_BmsCellVolt6.CellVoltage21H<<8)+g_BmsCellVolt6.CellVoltage21L;
		GattSetData(LIST_DIA,DIA_CV21,(uint8_t*)&temp16);
		temp16=(g_BmsCellVolt6.CellVoltage22H<<8)+g_BmsCellVolt6.CellVoltage22L;
		GattSetData(LIST_DIA,DIA_CV22,(uint8_t*)&temp16);
		temp16=(g_BmsCellVolt6.CellVoltage23H<<8)+g_BmsCellVolt6.CellVoltage23L;
		GattSetData(LIST_DIA,DIA_CV23,(uint8_t*)&temp16);
		//temp16=(g_BmsCellVolt6.CellVoltage24H<<8)+g_BmsCellVolt6.CellVoltage24L;
		//GattSetData(LIST_DIA,DIA_CV23,(uint8_t*)&temp16);
		BmsCellVolt6Event=FALSE;
		}
	if(BmsRtTempEvent)
	{
		int rt_temp=0;
		BmsRtTempEvent=FALSE;

		rt_temp=g_BmsRtTemp.BmsTemperature1-40;
		GattSetData(LIST_DIA,DIA_TEMP1,(uint8_t*)&rt_temp);
		rt_temp=g_BmsRtTemp.BmsTemperature2-40;
		GattSetData(LIST_DIA,DIA_TEMP2,(uint8_t*)&rt_temp);
		rt_temp=g_BmsRtTemp.BmsTemperature3-40;
		GattSetData(LIST_DIA,DIA_TEMP3,(uint8_t*)&rt_temp);
		rt_temp=g_BmsRtTemp.BmsTemperature4-40;
		GattSetData(LIST_DIA,DIA_TEMP4,(uint8_t*)&rt_temp);
		rt_temp=g_BmsRtTemp.BmsTemperature7-40;
		GattSetData(LIST_DIA,DIA_TEMP5,(uint8_t*)&rt_temp);
		rt_temp=g_BmsRtTemp.BmsTemperature8-40;
		GattSetData(LIST_DIA,DIA_TEMP6,(uint8_t*)&rt_temp);
		}
	if(BmsSysInforEvent)
	{
		BmsSysInforEvent=FALSE;
		} 
}




