
#include "stm32f4xx.h"
#include "usart.h"
#include "AutoAimTask.h"
#include "gimbal_task.h"


GMAngle_t aim,abt,abtLast,opt,adj;//aim�Ӿ����ݣ�absolute���ԽǶȣ�optimized�����ĽǶȣ�adjust����ͷ��е��װ����
uint8_t Enemy_INFO[10],Tx_INFO[8];						//����
uint8_t FindEnemy,AimMode;//AimMode==5�����5m��
int16_t AimTic=1;
GMAngle_t aimProcess(float yaw,float pit,int16_t *tic);
//********************************�����ʼ��********************************//
void InitAutoAim(){
	//����AUTO_AIM_UART��DMA����
	if(HAL_UART_Receive(&huart1,(uint8_t *)&Enemy_INFO,10,100)!= HAL_OK){Error_Handler();}
	//�Ƕȱ�����ʼ��
	aim.yaw=0;				aim.pit=0;
	adj.yaw=0.2;				adj.pit=-0.4;
}
//*******************************UART�ص�����********************************/
void USART1_IRQHandler(void)  
{
    volatile uint8_t receive;
    //receive interrupt �����ж�
    if(huart1.Instance->SR & UART_FLAG_RXNE)
    {
        receive = huart1.Instance->DR;
        //HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin);
		AutoAimUartRxCpltCallback();
    }
    //idle interrupt �����ж�
    else if(huart1.Instance->SR & UART_FLAG_IDLE)
    {
        receive = huart1.Instance->DR;
        //HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_RESET);
		AutoAimUartRxCpltCallback();
    }

}

float tmpY,tmpP;
void AutoAimUartRxCpltCallback(){
	if(RX_ENEMY_START=='s'&&RX_ENEMY_END=='e'){
		//onLed(5);//if���ذ����ƣ�˵�����յ�������
		aim.yaw=(int16_t)((RX_ENEMY_YAW1<<8)|RX_ENEMY_YAW2)*kAngle;
		aim.pit=-(int16_t)((RX_ENEMY_PITCH1<<8)|RX_ENEMY_PITCH2)*kAngle;
		aim.dis=(int16_t)((RX_ENEMY_DIS1<<8)|RX_ENEMY_DIS2);//0�ޣ�500��ʶ��1000������2000������װ�ף�3000������װ�ף�4000������װ�ף�5000�����⣬6000����
		if(aim.dis==500){
			HAL_UART_Receive(&huart1,(uint8_t*)&Enemy_INFO,10,100);
			return;
		}
		aim.yaw/=2.7;//���Ӿ������ؽǶ���ϳ���ʵ�Ƕ�
		aim.pit/=2.83;
		abt.yaw=gimbal_control.gimbal_yaw_motor.absolute_angle+aim.yaw-adj.yaw;//��ȡ��ʵ�Ƕ�
		abt.pit=gimbal_control.gimbal_pitch_motor.absolute_angle+aim.pit-adj.pit;
//		if(abt.pit>-12 && GMY.encoderAngle>0){AimMode=5;}//���Զ��
//		if(abt.pit<-13){AimMode=0;}//̫Զ��Ŀ�����
//		if(abt.pit<-2){//����Ŀ��
		FindEnemy=1;
		abtLast=abt;
	}
	HAL_UART_Receive(&huart1,(uint8_t*)&Enemy_INFO,10,100);
}

void autoAim(){
	//if(AimMode){opt.pit-=12/opt.pit+0.5;}//5m��׹����
	//else if(GMY.encoderAngle<0){opt.pit-=10/opt.pit-0.5;}//���ز���׹����
	//else{opt.pit-=30/opt.pit+0.5;}//��׹����
	gimbal_control.gimbal_yaw_motor.absolute_angle_set=abt.yaw;
	gimbal_control.gimbal_pitch_motor.relative_angle_set=abt.pit;
	FindEnemy=0;
}
