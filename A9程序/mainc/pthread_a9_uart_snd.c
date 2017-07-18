#include <pthread.h>
#include <unistd.h>

#include <sys/ipc.h>
#include <sys/sem.h>
#include <termios.h>
#include "test.h"

void *pthread_a9_uart_snd(void *arg)//主函数main.c中初始化，创建线程
{
	int ret = 0 ; 	
	char buff[2]={0};
	while(1)
	{	
		printf("begin to snd message to M0\n");
		pthread_mutex_lock(&mutex_a9_uart_snd);//斥锁
		pthread_cond_wait(&cond_a9_uart_snd, &mutex_a9_uart_snd);	
		printf("line= %d\n",__LINE__);
		buff[0] = dev_m0_cmd;
		pthread_mutex_unlock(&mutex_a9_uart_snd);
		printf("fd = %d\n",dev_uart_fd);
		if((ret = write(dev_uart_fd,buff,1))<0)
		{
				perror("uart_snd error\n");
				exit(1);	
		}
		printf("dev_m0_cmd = %d\n",buff[0]);
	}
	
}
