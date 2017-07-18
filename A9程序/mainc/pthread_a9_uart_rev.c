#include <pthread.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <termios.h>
#include "test.h"
void serial_init(int fd)
{
	struct termios options;
	tcgetattr(fd,&options);
	options.c_cflag |= (CLOCAL | CREAD);
	options.c_cflag &= ~CSIZE;
	options.c_cflag &= ~CRTSCTS;
	options.c_cflag |= CS8;
	options.c_cflag &= ~CSTOPB;
	options.c_iflag |= IGNPAR;
	options.c_iflag &= ~(ICRNL | IXON);
	options.c_oflag = 0;
	options.c_lflag = 0; 
	cfsetispeed(&options,B115200);
	cfsetospeed(&options,B115200);
	tcsetattr(fd,TCSANOW,&options);
}

void *pthread_a9_uart_rev(void *arg)      //主程序中main.c创建该线程
{
	
	int nbytes ;	
	char revbuff[23];

	if ((dev_uart_fd = open (DEV_UART, O_RDWR)) < 0)
	{
			perror ("open ttyUSB0 error\n");
			exit (1);
	}
	printf ("fd1 = %d\n",dev_uart_fd);
//	printf ("11111\n");
	serial_init (dev_uart_fd);
	printf ("pthread_a9_uart_rev is ok\n");
	while (1)
	{	
		if((nbytes = read(dev_uart_fd,revbuff,23))<0)
		{
			perror("pthread_a9_uart_rev read error");	
			exit(1);
		}



		memcpy (&a9_all_info.a9_info.envMsg,revbuff,23);
#if 0
		printf("readbytes = %d  \n",nbytes);
		printf ("snum = %d\n",a9_all_info.a9_info.envMsg.snum);
		printf ("temperature  = %d\n",a9_all_info.a9_info.envMsg.temp[0]);
		printf ("hum = %d\n",a9_all_info.a9_info.envMsg.hum[0]);
		printf ("x = %d\n",a9_all_info.a9_info.envMsg.x);
		printf ("y = %d\n",a9_all_info.a9_info.envMsg.y);
		printf ("z = %d\n",a9_all_info.a9_info.envMsg.z);
		printf ("light = %d\n",a9_all_info.a9_info.envMsg.lex);
		printf ("battery = %d\n",a9_all_info.a9_info.envMsg.bet);
		printf ("adc = %d\n",a9_all_info.a9_info.envMsg.adc);
#endif
	}

}
