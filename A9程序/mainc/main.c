#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <pthread.h>
#include "test.h"


pthread_t id_a9_uart_rev;
pthread_t id_a9_uart_snd;//pthread_t :类型定义typedef unsigned long int pthread_t;//用于创建线程id；
pthread_t id_a9_msg;
pthread_t id_a9_refresh;

void release(int signo)//信号函数，用于接受到主线程signal函数发送的信号，这里主线程执行键盘CTRL+C 后执行释放。
//剩下需要释放的变量继续添加
{
	pthread_mutex_destroy (&mutex_a9_uart_snd);//销毁互斥锁
	pthread_cond_destroy(&cond_a9_uart_snd);
	
	pthread_mutex_destroy(&mutex_a9_refresh);
	pthread_cond_destroy(&cond_a9_refresh);
	
	pthread_cancel(id_a9_uart_snd);//退出线程
	pthread_cancel(id_a9_uart_rev);
	pthread_cancel(id_a9_msg);
	pthread_cancel(id_a9_refresh);
}

int main(int args,char *argv[])//需要初始化的函数继续添加
{
	pthread_mutex_init(&mutex_a9_uart_snd,NULL);//申请互斥锁，NULL表示默认方式
	pthread_cond_init(&cond_a9_uart_snd,NULL);
	pthread_mutex_init(&mutex_a9_camera, NULL);
	pthread_cond_init(&cond_a9_camera, NULL);
	
	pthread_create(&id_a9_uart_snd,NULL,pthread_a9_uart_snd,NULL);//创建线程
	pthread_create(&id_a9_uart_rev,NULL,pthread_a9_uart_rev,NULL);//创建线程
	pthread_create(&id_a9_msg, NULL, pthread_a9_msg, NULL);
	pthread_create(&id_a9_refresh,NULL,pthread_a9_refresh,NULL);
	
	signal(SIGINT,release);
	pthread_join(id_a9_uart_snd,NULL);
	pthread_join(id_a9_uart_rev,NULL);//线程结束等待函数
	pthread_join(id_a9_msg,NULL);
	pthread_join(id_a9_refresh,NULL);
	return 0;
}
