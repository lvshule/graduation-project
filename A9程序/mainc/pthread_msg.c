#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include "test.h"
#include "msg.h"

struct setenv
{
	int temMAX;//温度
	int temMIN;
	int humMAX;//湿度
	int humMIN;
	int illMAX;//采光度
	int illMIN;
};

void* pthread_a9_msg(void* arg)
{
	key_t key;
	msg_s msgbuf;
	struct setenv sEnv;
	int msgqid;

	if((key=ftok("/root",'g')<0))
	{
		perror("msg_ftok error");
		exit(1);
	}
	fprintf(stdout,"key = %d\n",key);
	if((msgqid=msgget(1234567,IPC_CREAT | 0666))<0)
	{
		perror("msg error");
		exit(1);
	}
	fprintf(stdout,"msgqid = %d\n",msgqid);
	printf("msg ok\n");
	while(1)
	{
		bzero(&msgbuf,sizeof(msgbuf));
		printf("%d\n",MSGSIZE);
		printf("line=%d,fun:%s\n", __LINE__, __func__);

		if(msgrcv(msgqid, &msgbuf, MSGSIZE, 0, 0) < 0)
		{
			printf("22222222222222222222222\n");
			printf("line=%d,fun:%s\n", __LINE__, __func__);

		}

		printf("line=%d,fun:%s\n", __LINE__, __func__);
		printf("3333333333333\n");
		switch(msgbuf.msgtype)
		{

			case MSG_CAMERA:
				printf("msg_camera:\n");
				pthread_mutex_lock(&mutex_a9_camera);
				dev_camera_cmd = msgbuf.text[0];
				printf("dev_camera_msg_cmd = %d\n",dev_camera_cmd);
				pthread_cond_signal(&cond_a9_camera);
				pthread_mutex_unlock(&mutex_a9_camera);
				break;
			case MSG_SETENV:
				printf("msg_setenv:\n");
				memcpy(&sEnv,msgbuf.text+1,32);
				printf("temMAX=%d,temMIN=%d,humMAX=%d,humMIN=%d,illMAX=%d,illMIN=%d\n",sEnv.temMAX,sEnv.temMIN,sEnv.humMAX,sEnv.humMIN,sEnv.illMAX,sEnv.illMIN);
				break;
			case MSG_UART_SND:
				printf("msg_uart_snd:\n");
				pthread_mutex_lock(&mutex_a9_uart_snd);
				dev_m0_cmd = msgbuf.text[0];
				pthread_cond_signal(&cond_a9_uart_snd);
				pthread_mutex_unlock(&mutex_a9_uart_snd);
				break;
			default:
				break;
		}
	}

}
