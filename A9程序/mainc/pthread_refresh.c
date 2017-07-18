#include <stdio.h>    //更新共享内存数据
#include <errno.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>

#include "test.h"


#define N 1024

struct shm_addr
{
	struct a9_env_addr     rt_a9_info;
};

struct shm_addr *shm_buf;



void* pthread_a9_refresh(void* arg)
{

	key_t key_info;
	int shmid;
	
	
	if ((key_info = ftok ("/dev", 'i')) < 0)
	{
		perror ("ftok info");
		exit(1) ;
	}
	
	printf ("key_info = %d\n", key_info);
	
	if ((shmid = shmget (key_info, N, IPC_CREAT | IPC_EXCL | 0666)) < 0)
	{
		if (errno == EEXIST)
		{
			shmid = shmget (key_info, N, 0666);
			shm_buf = (struct shm_addr *)shmat (shmid, NULL, 0);
			
		}
		else
		{
			perror ("shmget");
			exit(1) ;
		}

	}
	else
	{
		if ((shm_buf = (struct shm_addr *)shmat (shmid, NULL, 0)) == (void *)-1)
		{
			perror ("shmat");
			exit(1) ;
		}
	}
	
	bzero (shm_buf, sizeof (struct shm_addr));
	printf ("pthread_refresh is ok\n");
	
	while(1)
	{
		
		pthread_mutex_lock (&mutex_a9_refresh);	
		shm_buf->rt_a9_info = a9_all_info;
		pthread_mutex_unlock (&mutex_a9_refresh);
		//printf("%f \n",shm_buf->rt_a9_info.a9_info.temperature);
		//printf("%f \n",shm_buf->a9_info.a9_info.adc);
	}
}
