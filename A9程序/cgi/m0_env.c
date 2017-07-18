#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>


#include "cgic.h"
#include "test.h"

#define N 1024

struct shm_addr
{
	struct a9_env_addr rt_a9_info;
};

struct shm_addr *shm_buf;



int cgiMain()
{

	key_t key;
	int shmid;
	struct shm_addr *shm_buf;

	if((key = ftok("/dev",'i')) <0)
	{
		perror("ftok");
		exit(1);
	}
	printf("key = %x\n",key);


	if((shmid = shmget(key, N, IPC_CREAT|0666 )) == -1)
	{
		perror("shmget");
		exit(1);
	}

	if((shm_buf = (struct shm_addr*)shmat(shmid, NULL, 0)) == (void*)-1 )
	{
		perror("shmat");
		exit(1);
	}



	cgiHeaderContentType("text/html");

	fprintf(cgiOut, "<head><meta http-equiv=\"refresh\" content=\"1\"></head>");
	fprintf(cgiOut, "<HTML>\n");
	fprintf(cgiOut, "<BODY bgcolor=\"#FEE9BE\">\n");

	if (1)
	{
		fprintf(cgiOut, "<h2><font face=\"Broadway\"><font color=\"#FF0000\"> M0 Real-time environment  </font></font></H2>\n ");	

		fprintf(cgiOut, "<h4>snum :\t%d</H4>\n ", shm_buf->rt_a9_info.a9_info.envMsg.snum);
		fprintf(cgiOut, "<h4>temperature:\t %d</H4>\n ", shm_buf->rt_a9_info.a9_info.envMsg.temp[0]);
		fprintf(cgiOut, "<h4>hum:\t%d</H4>\n ", shm_buf->rt_a9_info.a9_info.envMsg.hum[0]);
		fprintf(cgiOut, "<h4>X:\t%d</H4>\n ", shm_buf->rt_a9_info.a9_info.envMsg.x);
		fprintf(cgiOut, "<h4>Y:\t%d</H4>\n ", shm_buf->rt_a9_info.a9_info.envMsg.y);
		fprintf(cgiOut, "<h4>Z:\t%d</H4>\n ", shm_buf->rt_a9_info.a9_info.envMsg.z);
		fprintf(cgiOut, "<h4>light:\t%d</H4>\n ", shm_buf->rt_a9_info.a9_info.envMsg.lex);
		fprintf(cgiOut, "<h4>battery:\t%d.%d</H4>\n ", shm_buf->rt_a9_info.a9_info.envMsg.bet/10,shm_buf->rt_a9_info.a9_info.envMsg.bet%10);
		fprintf(cgiOut, "<h4>Adc:\t%d.%d</H4>\n ", shm_buf->rt_a9_info.a9_info.envMsg.adc /10 ,shm_buf->rt_a9_info.a9_info.envMsg.adc%10);





		//fprintf(cgiOut, "<h4>Temperature\nMAX: %0.2f MIN: %0.2f</H4>\n ", 70.5,4.0);
		//fprintf(cgiOut, "<h4>Adc\nMAX: %0.2f MIN: %0.2f</H4>\n ", 3.3,0.0);

	}
	else
	{
		fprintf(cgiOut, "<h2><font face=\"Broadway\"><font color=\"#FF0000\"> Close! </font></font></H2>\n ");	
	}

	fprintf(cgiOut, "</BODY></HTML>\n");	
	return 0;
}
