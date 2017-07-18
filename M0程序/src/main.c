#include "lpc11xx.h"
#include "gpio.h"
#include "uart.h"
#include "timer32.h"
#include "timeflag.h"
#include "tools.h"
#include "sensor.h"
#include "device.h"
#include "control.h"
#include "key.h"

#include "stdlib.h"
#include "oled2864.h" 

#define STO_NO	1


uint8_t Nu[200];

//extern uint8_t cmd;
#if(STO_NO == 1)
uint8_t TitileBuf[20] = {"     STORAGE ONE"};
#endif
#if(STO_NO == 2)
uint8_t TitileBuf[20] = {"     STORAGE TWO"};
#endif


int sure(uint8_t y)
{
	char i;
	for(i = 0;i < 100;i++)
	{
		if(y == Nu[i])
			return 1;
	}
	return 0;
}



void InitSys(void)
{
	SystemInit(); //ϵͳ��ʼ��
 	GPIOInit();	 //IO��ʼ��
	InitDelay(48); 	 //��ʼ����ʱ�δ�ʱ��
	init_timer32(0, 480000);	   //��ʼ��32λ��ʱ��  10ms
	NVIC_SetPriority(TIMER_32_0_IRQn, 0);	 //ӳ��32λ��ʱ���ж�
	enable_timer32(0);						//ʹ��32λ��ʱ��
	UARTInit(115200);						//���ô��ڲ�����
	NVIC_SetPriority(UART_IRQn, 2);			 //ӳ�䴮���ж�
}

int main(void)
{
 	InitSys();			 	//ϵͳ��ʼ������M0оƬ������
 	InitTimeFlag();			//��ʱʱ���־λ
 	InitAllSensor();		//��ʼ�����еĴ�����
 	InitAllDevice();		 //��ʼ����Χ�豸
	InitControl(TitileBuf);    //��ʼ���������ƣ����α���ͷTitileBuf
		


		while(1)
  {
 		ScanTimeFlag();
		ScanAllSensor();	//10ms����һ�βɼ�
		DealA8Cmd(STO_NO);		//zigbee ��������,��������Ӧ�Ĵ���
		SendEnvMsg(STO_NO);		//���ɼ��������ݷŵ� STO_NO���棬	memcpy(sendbuf, &EnvMsg, 24); ������buf���洫��
		Control(STO_NO);       //�ֿ�ţ�rfid����   
	}
}




