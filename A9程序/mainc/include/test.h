#ifndef __TEST__H__
#define __TEST__H__
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>
#include <termios.h>
#include <syscall.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <linux/fs.h>
#include <linux/ioctl.h>

unsigned char dev_m0_cmd;

#define DEV_UART		"/dev/ttyUSB0"

struct revEnv
{
	unsigned char  head[3];	 
	
	unsigned char  type;
	unsigned char  snum;
	unsigned char  temp[2];	
	unsigned char  hum[2];
	signed char   x;
	signed char  y;			 
	signed char  z;			 
	unsigned int  lex;
	unsigned int  bet;
	unsigned int  adc;
};
struct a9_info
{
	unsigned char a9_status;    // 0:open 1:close
	unsigned char led_status;
	unsigned char buzzer_status;
	
	float temperature;
	float temperatureMIN;
	float temperatureMAX;
	float adc;
	float adcMIN;
	float adcMAX;
	struct revEnv envMsg;		
};
struct a9_env_addr 
{
	struct a9_info       a9_info ;

};

struct a9_env_addr       a9_all_info ;

extern unsigned char dev_camera_cmd;
extern unsigned char dev_m0_cmd;
extern int dev_uart_fd;

extern pthread_mutex_t mutex_a9_adc ; 
extern pthread_mutex_t mutex_a9_temp ;
extern pthread_mutex_t mutex_a9_refresh ;
extern pthread_mutex_t mutex_a9_camera ;
extern pthread_mutex_t mutex_a9_uart_snd ;


extern pthread_cond_t cond_a9_adc;
extern pthread_cond_t cond_a9_temp;
extern pthread_cond_t cond_a9_refresh;
extern pthread_cond_t cond_a9_camera;
extern pthread_cond_t cond_a9_uart_snd;


extern void* pthread_a9_adc(void*);
extern void* pthread_a9_temp(void*);
extern void* pthread_a9_refresh(void*);
extern void* pthread_a9_msg(void* );
extern void* pthread_camera(void* );
extern void* pthread_a9_uart_snd(void* );
extern void* pthread_a9_uart_rev(void* );

#endif

