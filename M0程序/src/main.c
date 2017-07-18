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
	SystemInit(); //系统初始化
 	GPIOInit();	 //IO初始化
	InitDelay(48); 	 //初始化延时滴答定时器
	init_timer32(0, 480000);	   //初始化32位定时器  10ms
	NVIC_SetPriority(TIMER_32_0_IRQn, 0);	 //映射32位定时器中断
	enable_timer32(0);						//使能32位定时器
	UARTInit(115200);						//设置串口波特率
	NVIC_SetPriority(UART_IRQn, 2);			 //映射串口中断
}

int main(void)
{
 	InitSys();			 	//系统初始化，让M0芯片跑起来
 	InitTimeFlag();			//定时时间标志位
 	InitAllSensor();		//初始化所有的传感器
 	InitAllDevice();		 //初始化外围设备
	InitControl(TitileBuf);    //初始化按键控制，传参标题头TitileBuf
		


		while(1)
  {
 		ScanTimeFlag();
		ScanAllSensor();	//10ms进行一次采集
		DealA8Cmd(STO_NO);		//zigbee 接收命令,并进行相应的处理
		SendEnvMsg(STO_NO);		//将采集到的数据放到 STO_NO里面，	memcpy(sendbuf, &EnvMsg, 24); 拷贝到buf里面传出
		Control(STO_NO);       //仓库号，rfid控制   
	}
}




