/**
  ****************************(C)SWJTU_ROBOTCON****************************
  * @file       cybergear.c/h
  * @brief      С�׵��������
  * @note       
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     1-10-2023       ZDYukino        1. done
  *
  @verbatim
  =========================================================================
  =========================================================================
  @endverbatim
  ****************************(C)SWJTU_ROBOTCON****************************
  **/
#include <stdio.h>
#include <stdint.h>
#include "main.h"
#include "cybergear.h"
#include "SPI.h"
//#include "vofa.h"

CAN_RxHeaderTypeDef rxMsg;//���ͽ��սṹ��
CAN_TxHeaderTypeDef txMsg;//�������ýṹ��
uint8_t rx_data[8];       //��������
uint32_t Motor_Can_ID;    //�������ݵ��ID
uint8_t byte[4];          //ת����ʱ����
uint32_t send_mail_box = {0};//NONE
uint8_t SPIarr[12];  // ȫ�ֱ���

void SPI_AddTxMessage(int SPI, const CAN_TxHeaderTypeDef *pHeader, const uint8_t aData[]) {
    // �� ExtId ת��Ϊ�ĸ� uint8_t
    uint32_t extId = pHeader->ExtId;
    uint8_t extIdBytes[4];
    extIdBytes[0] = (extId >> 24) & 0xFF;
    extIdBytes[1] = (extId >> 16) & 0xFF;
    extIdBytes[2] = (extId >> 8) & 0xFF;
    extIdBytes[3] = extId & 0xFF;

    // �� ExtId �ָ����������� aData ƴ����һ��
    for (int i = 0; i < 4; i++) {
        SPIarr[i] = extIdBytes[i];
    }
    for (int i = 0; i < 8; i++) {
        SPIarr[i + 4] = aData[i];
    }
    printf("%d",SPI);
    if(SPI==0) sendSPIData(0, SPIarr);
    if(SPI==2) sendSPIData(2, SPIarr);
    // ��ӡ���ɵ�����
    printf("Generated array: ");
    for (int i = 0; i < 12; i++) {
        printf("0x%02X ", SPIarr[i]);
    }
    printf("\n");
}

#define can_txd() if(Motor->canx==0) SPI_AddTxMessage(0, &txMsg, tx_data);else if(Motor->canx==2) (SPI_AddTxMessage(2, &txMsg, tx_data));





//MI_Motor mi_motor[12];//Ԥ�ȶ���12��С�׵��

/**
  * @brief          ������ת4�ֽں���
  * @param[in]      f:������
  * @retval         4�ֽ�����
  * @description  : IEEE 754 Э��
  */
static uint8_t* Float_to_Byte(float f)
{
	unsigned long longdata = 0;
	longdata = *(unsigned long*)&f;       
	byte[0] = (longdata & 0xFF000000) >> 24;
	byte[1] = (longdata & 0x00FF0000) >> 16;                                                                                                                                                                                                         
	byte[2] = (longdata & 0x0000FF00) >> 8;
	byte[3] = (longdata & 0x000000FF);
	return byte;
}

/**
  * @brief          С�׵������16λ����ת����
  * @param[in]      x:16λ����
  * @param[in]      x_min:��Ӧ��������
  * @param[in]      x_max:��Ӧ��������
  * @param[in]      bits:����λ��
  * @retval         ���ظ���ֵ
  */
static float uint16_to_float(uint16_t x,float x_min,float x_max,int bits)
{
    uint32_t span = (1 << bits) - 1;
    float offset = x_max - x_min;
    return offset * x / span + x_min;
}

/**
  * @brief          С�׵�����͸���ת16λ����
  * @param[in]      x:����
  * @param[in]      x_min:��Ӧ��������
  * @param[in]      x_max:��Ӧ��������
  * @param[in]      bits:����λ��
  * @retval         ���ظ���ֵ
  */
static int float_to_uint(float x, float x_min, float x_max, int bits)
{
  float span = x_max - x_min;
  float offset = x_min;
  if(x > x_max) x=x_max;
  else if(x < x_min) x= x_min;
  return (int) ((x-offset)*((float)((1<<bits)-1))/span);
}

/**
  * @brief          д��������
  * @param[in]      Motor:��Ӧ���Ƶ���ṹ��
  * @param[in]      Index:д�������Ӧ��ַ
  * @param[in]      Value:д�����ֵ
  * @param[in]      Value_type:д�������������
  * @retval         none
  */
extern void Set_Motor_Parameter(MI_Motor *Motor,uint16_t Index,float Value,char Value_type){
	uint8_t tx_data[8];
	txMsg.ExtId = Communication_Type_SetSingleParameter<<24|Master_CAN_ID<<8|Motor->CAN_ID;
	tx_data[0]=Index;
	tx_data[1]=Index>>8;
	tx_data[2]=0x00;
	tx_data[3]=0x00;
	if(Value_type == 'f'){
		Float_to_Byte(Value);
		tx_data[4]=byte[3];
		tx_data[5]=byte[2];
		tx_data[6]=byte[1];
		tx_data[7]=byte[0];		
	}
	else if(Value_type == 's'){
		tx_data[4]=(uint8_t)Value;
		tx_data[5]=0x00;
		tx_data[6]=0x00;
		tx_data[7]=0x00;				
	}

		can_txd();	
	
	
}

/**
  * @brief          ��ȡ����ظ�֡��չID�еĵ��CANID
  * @param[in]      CAN_ID_Frame:����ظ�֡�е���չCANID   
  * @retval         ���CANID
  */
static uint32_t Get_Motor_ID(uint32_t CAN_ID_Frame)
{
	return (CAN_ID_Frame&0xFFFF)>>8;
}

/**
  * @brief          ����ظ�֡���ݴ�����
  * @param[in]      Motor:��Ӧ���Ƶ���ṹ��   
  * @param[in]      DataFrame:����֡
  * @param[in]      IDFrame:��չID֡
  * @retval         None
  */
static void Motor_Data_Handler(MI_Motor *Motor,uint8_t DataFrame[8],uint32_t IDFrame)
{	
		Motor->Angle=uint16_to_float(DataFrame[0]<<8|DataFrame[1],MIN_P,MAX_P,16);
		Motor->Speed=uint16_to_float(DataFrame[2]<<8|DataFrame[3],V_MIN,V_MAX,16);			
		Motor->Torque=uint16_to_float(DataFrame[4]<<8|DataFrame[5],T_MIN,T_MAX,16);				
		Motor->Temp=(DataFrame[6]<<8|DataFrame[7])*Temp_Gain;
		Motor->error_code=(IDFrame&0x1F0000)>>16;	
}

/**
  * @brief          С�׵��ID���
  * @param[in]      id:  ��Ӧ���Ƶ���ṹ��
  * @retval         none
  */
void chackcybergear(uint8_t ID,MI_Motor *Motor)
{
    uint8_t tx_data[8] = {0};
    txMsg.ExtId = Communication_Type_GetID<<24|Master_CAN_ID<<8|ID;
    can_txd();
}

/**
  * @brief          ʹ��С�׵��
  * @param[in]      Motor:��Ӧ���Ƶ���ṹ��   
  * @retval         none
  */
void start_cybergear(MI_Motor *Motor)
{
    uint8_t tx_data[8] = {0}; 
    txMsg.ExtId = Communication_Type_MotorEnable<<24|Master_CAN_ID<<8|Motor->CAN_ID;
    can_txd();
}

/**
  * @brief          ֹͣ���
  * @param[in]      Motor:��Ӧ���Ƶ���ṹ��   
  * @param[in]      clear_error:�������λ��0 ����� 1�����
  * @retval         None
  */
void stop_cybergear(MI_Motor *Motor,uint8_t clear_error)
{
	uint8_t tx_data[8]={0};
	tx_data[0]=clear_error;//�������λ����
	txMsg.ExtId = Communication_Type_MotorStop<<24|Master_CAN_ID<<8|Motor->CAN_ID;
    can_txd();
}

/**
  * @brief          ���õ��ģʽ(����ֹͣʱ������)
  * @param[in]      Motor:  ����ṹ��
  * @param[in]      Mode:   �������ģʽ��1.�˶�ģʽMotion_mode 2. λ��ģʽPosition_mode 3. �ٶ�ģʽSpeed_mode 4. ����ģʽCurrent_mode��
  * @retval         none
  */
void set_mode_cybergear(MI_Motor *Motor,uint8_t Mode)
{	
	Set_Motor_Parameter(Motor,Run_mode,Mode,'s');
}

/**
  * @brief          ��������ģʽ�����õ���
  * @param[in]      Motor:  ����ṹ��
  * @param[in]      Current:��������
  * @retval         none
  */
void set_current_cybergear(MI_Motor *Motor,float Current)
{
	Set_Motor_Parameter(Motor,Iq_Ref,Current,'f');
}

/**
  * @brief          ���õ�����
  * @param[in]      Motor:  ����ṹ��
  * @retval         none
  */
void set_zeropos_cybergear(MI_Motor *Motor)
{
	uint8_t tx_data[8]={0};
	tx_data[0]=0x01;
	txMsg.ExtId = Communication_Type_SetPosZero<<24|Master_CAN_ID<<8|Motor->CAN_ID;
	can_txd();		
}

/**
  * @brief          ���õ��CANID
  * @param[in]      Motor:  ����ṹ��
  * @param[in]      Motor:  ������ID
  * @retval         none
  */
void set_CANID_cybergear(MI_Motor *Motor,uint8_t CAN_ID)
{
	uint8_t tx_data[8]={0};
	txMsg.ExtId = Communication_Type_CanID<<24|CAN_ID<<16|Master_CAN_ID<<8|Motor->CAN_ID;
    Motor->CAN_ID = CAN_ID;//���µ�ID�������ṹ��
    can_txd();	
}
/**
  * @brief          С�׵����ʼ��
  * @param[in]      Motor:  ����ṹ��
  * @param[in]      Can_Id: С�׵��ID(Ĭ��0x7F)
  * @param[in]      Motor_Num: ������
  * @param[in]      mode: �������ģʽ��0.�˶�ģʽMotion_mode 1. λ��ģʽPosition_mode 2. �ٶ�ģʽSpeed_mode 3. ����ģʽCurrent_mode��
  * @retval         none
  */
void init_cybergear(MI_Motor *Motor,uint8_t Can_Id, uint8_t mode)
{
    txMsg.StdId = 0;            //����CAN���ͣ���׼֡���� 
    txMsg.ExtId = 0;            //����CAN���ͣ���չ֡����     
    txMsg.DLC = 0x08;           //����CAN���ͣ����ݳ���
	Motor->CAN_ID=Can_Id;       //ID���� 
	if(Can_Id/0x10==1||Can_Id/0x10==2)
	{
		Motor->canx=0;
	}else if(Can_Id/0x10==3||Can_Id/0x10==4)
  {
		Motor->canx=2;
	}
		
	//set_mode_cybergear(Motor,mode);//���õ��ģʽ
  //set_zeropos_cybergear(Motor);   //�������
	//start_cybergear(Motor);        //ʹ�ܵ��
}

/**
  * @brief          С���˿�ģʽָ��
  * @param[in]      Motor:  Ŀ�����ṹ��
  * @param[in]      torque: ��������[-12,12] N*M
  * @param[in]      MechPosition: λ������[-12.5,12.5] rad
  * @param[in]      speed: �ٶ�����[-30,30] rpm
  * @param[in]      kp: ������������
  * @param[in]      kd: ΢�ֲ�������
  * @retval         none
  */
void motor_controlmode(MI_Motor *Motor,float torque, float MechPosition, float speed, float kp, float kd)
{   
    uint8_t tx_data[8];//�������ݳ�ʼ��
    //װ�������
    tx_data[0]=float_to_uint(MechPosition,P_MIN,P_MAX,16)>>8;  
    tx_data[1]=float_to_uint(MechPosition,P_MIN,P_MAX,16);  
    tx_data[2]=float_to_uint(speed,V_MIN,V_MAX,16)>>8;  
    tx_data[3]=float_to_uint(speed,V_MIN,V_MAX,16);  
    tx_data[4]=float_to_uint(kp,KP_MIN,KP_MAX,16)>>8;  
    tx_data[5]=float_to_uint(kp,KP_MIN,KP_MAX,16);  
    tx_data[6]=float_to_uint(kd,KD_MIN,KD_MAX,16)>>8;  
    tx_data[7]=float_to_uint(kd,KD_MIN,KD_MAX,16); 
    
    txMsg.ExtId = Communication_Type_MotionControl<<24|float_to_uint(torque,T_MIN,T_MAX,16)<<8|Motor->CAN_ID;//װ����չ֡����
    can_txd();
}


/*****************************�ص����� ����ӻش���Ϣ ��ת������*****************************/
/**
  * @brief          hal��CAN�ص�����,���յ������
  * @param[in]      hcan:CAN���ָ��
  * @retval         none
  */
// void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan)
// {
//     //HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);              //LED��˸ָʾ
//     HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO1, &rxMsg, rx_data);//��������
// 	Motor_Can_ID=Get_Motor_ID(rxMsg.ExtId);//���Ȼ�ȡ�ش����ID��Ϣ  
//     switch(Motor_Can_ID)                   //����ӦID�����Ϣ��ȡ����Ӧ�ṹ��
//     {
//         case 0X7F:  
//             if(rxMsg.ExtId>>24 != 0)               //����Ƿ�Ϊ�㲥ģʽ
//                 Motor_Data_Handler(&mi_motor[0],rx_data,rxMsg.ExtId);
//             else 
//                 mi_motor[0].MCU_ID = rx_data[0];
//             break;           
//         default:
//             break;		
//     }
// }
