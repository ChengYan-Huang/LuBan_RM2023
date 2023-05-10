
#include "stm32f4xx.h"
#include "usart.h"
#include "AutoAimTask.h"
#include "gimbal_task.h"


GMAngle_t aim,abt,abtLast,opt,adj;//aim视觉数据，absolute绝对角度，optimized处理后的角度，adjust摄像头机械安装补偿
uint8_t Enemy_INFO[10],Tx_INFO[8];						//接收
uint8_t FindEnemy,AimMode;//AimMode==5：外侧5m外
int16_t AimTic=1;
GMAngle_t aimProcess(float yaw,float pit,int16_t *tic);
//********************************自瞄初始化********************************//
void InitAutoAim(){
	//开启AUTO_AIM_UART的DMA接收
	if(HAL_UART_Receive(&huart1,(uint8_t *)&Enemy_INFO,10,100)!= HAL_OK){Error_Handler();}
	//角度变量初始化
	aim.yaw=0;				aim.pit=0;
	adj.yaw=0.2;				adj.pit=-0.4;
}
//*******************************UART回调函数********************************/
void USART1_IRQHandler(void)  
{
    volatile uint8_t receive;
    //receive interrupt 接收中断
    if(huart1.Instance->SR & UART_FLAG_RXNE)
    {
        receive = huart1.Instance->DR;
        //HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin);
		AutoAimUartRxCpltCallback();
    }
    //idle interrupt 空闲中断
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
		//onLed(5);//if主控板闪灯，说明接收到了数据
		aim.yaw=(int16_t)((RX_ENEMY_YAW1<<8)|RX_ENEMY_YAW2)*kAngle;
		aim.pit=-(int16_t)((RX_ENEMY_PITCH1<<8)|RX_ENEMY_PITCH2)*kAngle;
		aim.dis=(int16_t)((RX_ENEMY_DIS1<<8)|RX_ENEMY_DIS2);//0无，500弱识别，1000正常，2000陀螺正装甲，3000陀螺右装甲，4000陀螺左装甲，5000五米外，6000工程
		if(aim.dis==500){
			HAL_UART_Receive(&huart1,(uint8_t*)&Enemy_INFO,10,100);
			return;
		}
		aim.yaw/=2.7;//把视觉的像素角度拟合成真实角度
		aim.pit/=2.83;
		abt.yaw=gimbal_control.gimbal_yaw_motor.absolute_angle+aim.yaw-adj.yaw;//获取真实角度
		abt.pit=gimbal_control.gimbal_pitch_motor.absolute_angle+aim.pit-adj.pit;
//		if(abt.pit>-12 && GMY.encoderAngle>0){AimMode=5;}//外侧远处
//		if(abt.pit<-13){AimMode=0;}//太远的目标忽略
//		if(abt.pit<-2){//近处目标
		FindEnemy=1;
		abtLast=abt;
	}
	HAL_UART_Receive(&huart1,(uint8_t*)&Enemy_INFO,10,100);
}

void autoAim(){
	//if(AimMode){opt.pit-=12/opt.pit+0.5;}//5m下坠补偿
	//else if(GMY.encoderAngle<0){opt.pit-=10/opt.pit-0.5;}//基地侧下坠补偿
	//else{opt.pit-=30/opt.pit+0.5;}//下坠补偿
	gimbal_control.gimbal_yaw_motor.absolute_angle_set=abt.yaw;
	gimbal_control.gimbal_pitch_motor.relative_angle_set=abt.pit;
	FindEnemy=0;
}
