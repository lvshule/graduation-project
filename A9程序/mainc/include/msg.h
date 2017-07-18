#ifndef _MSQ_H_
#define _MSQ_H
#define MSGTYPE			1L
#define MSG_LED			1L
#define MSG_CAMERA		2L
#define MSG_UART_SND	3L
#define MSG_SETENV		4L
#define MSG_CHGNUM		5L

#define QUEUE_MSG_LEN 32

//往M0 A8 发送的消息类型
#define MSG_M0_FAN_OFF			0x40
#define MSG_M0_FAN_ON1			0x41
#define MSG_M0_FAN_ON2			0x42
#define MSG_M0_FAN_ON3			0x43

#define MSG_M0_BEEP_OFF			0x50
#define MSG_M0_BEEP_ON			0x51
#define MSG_M0_BEEP_AU_OFF		0x12
#define MSG_M0_BEEP_AU_ON		0x13

#define MSG_M0_LED_OFF			0x60
#define MSG_M0_LED_ON			0x61

#define MSG_M0_SEG_ON			0x30
#define MSG_M0_SEG_OFF			0x3f

typedef struct msg
{
	long type;//从消息队列接收消息时用于判断的消息类型
	long msgtype;//具体的消息类型
	unsigned char text[QUEUE_MSG_LEN];//消息正文
}msg_s;
#define MSGSIZE			sizeof(msg_s)-sizeof(long)

unsigned char dev_camera_cmd;
unsigned char dev_m0_cmd;
int dev_uart_fd;
#endif
