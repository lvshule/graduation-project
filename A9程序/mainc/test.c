#include "test.h"

//pthread_mutex_t mutex_a9_adc ; 
//pthread_mutex_t mutex_a9_temp ;
pthread_mutex_t mutex_a9_refresh ;
pthread_mutex_t mutex_a9_camera ;
pthread_mutex_t mutex_a9_uart_snd ;



//pthread_cond_t cond_a9_adc;
//pthread_cond_t cond_a9_temp;
pthread_cond_t cond_a9_refresh;
pthread_cond_t cond_a9_msg;
pthread_cond_t cond_a9_camera;
pthread_cond_t cond_a9_uart_snd;

unsigned char dev_camera_cmd;
unsigned char dev_m0_cmd;
int dev_uart_fd;
 








 



