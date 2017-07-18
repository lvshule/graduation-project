#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <errno.h>
#include <sys/sem.h>
#include <unistd.h>
#include "cgic.h"
#include "test.h"
#include "msg.h"
#if 0
#include "./inc/sem.h"

#include "./inc/data_global.h"

#endif
#define N 32
#define STO_NO 1


struct shm_addr
{
	char cgi_status;
	char qt_status;
	struct env_info_clien_addr rt_status;
};


int cgiMain()
{/*
	key_t key;
	int shmid,semid;
	struct shm_addr *shm_buf;
		
	if((key = ftok("/app",'i')) <0)
	{
		perror("ftok");
		exit(1);
	}

	if((semid  = semget(key, 1, IPC_CREAT | 0666)) < 0)
	{
		perror("semget");
		exit(1);
	}*/

/*	if((shmid = shmget(key, N, IPC_CREAT | 0666 )) == -1)
	{
		perror("shmget");
		exit(1);
	}*/

	/*if((shm_buf = (struct shm_addr*)shmat(shmid, NULL, 0)) == (void*)-1 )
	{
		perror("shmat");
		exit(1);
	}*/

	//sem_p(semid,0);
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

	#if 0

	cgiHeaderContentType("text/html");

	fprintf(cgiOut, "<head><meta http-equiv=\"refresh\" content=\"1\"><style><!--body{line-height:50%}--></style></head>");
	fprintf(cgiOut, "<HTML>\n");
	fprintf(cgiOut, "<BODY bgcolor=\"#666666\">\n");
	fprintf(cgiOut, "<h1><font color=\"#FF0000\">Storage #%d:</font></H2>\n ", STO_NO);
//	if (shm_buf->rt_status.storage_no[STO_NO].storage_status == 1)
	if(1)
	{
		fprintf(cgiOut, "<h2><font face=\"Broadway\"><font color=\"#FFFAF0\">Real-time information environment</font></font></H2>\n ");	
		fprintf(cgiOut, "<h4>Temperature:\t%0.2f C</H4>\n ", shm_buf->rt_status.storage_no[STO_NO].temperature);
		fprintf(cgiOut, "<h4>Humidity:\t%0.2f</H4>\n ", shm_buf->rt_status.storage_no[STO_NO].humidity);
		fprintf(cgiOut, "<h4>Illumination:\t%0.2f</H4>\n ", shm_buf->rt_status.storage_no[STO_NO].illumination);
		fprintf(cgiOut, "<h4>Battery:\t%0.2f</H4>\n ", shm_buf->rt_status.storage_no[STO_NO].battery);
		fprintf(cgiOut, "<h4>Adc:\t%0.2f V</H4>\n ", shm_buf->rt_status.storage_no[STO_NO].adc);
		fprintf(cgiOut, "<h4>X:\t%d</H4>\n ", shm_buf->rt_status.storage_no[STO_NO].x);
		fprintf(cgiOut, "<h4>Y:\t%d</H4>\n ", shm_buf->rt_status.storage_no[STO_NO].y);
		fprintf(cgiOut, "<h4>Z:\t%d</H4>\n ", shm_buf->rt_status.storage_no[STO_NO].z);
#if 0
		fprintf(cgiOut, "<h4>Temperature\nMAX: %0.0f MIN: %0.0f</H4>\n ", shm_buf->rt_status.storage_no[STO_NO].temperatureMAX, shm_buf->rt_status.storage_no[STO_NO].temperatureMIN);
		fprintf(cgiOut, "<h4>Humidity\nMAX: %0.0f MIN: %0.0f</H4>\n ", shm_buf->rt_status.storage_no[STO_NO].humidityMAX, shm_buf->rt_status.storage_no[STO_NO].humidityMIN);
		fprintf(cgiOut, "<h4>Illumination\nMAX: %0.0f MIN: %0.0f</H4>\n ", shm_buf->rt_status.storage_no[STO_NO].illuminationMAX, shm_buf->rt_status.storage_no[STO_NO].illuminationMIN);
#endif	
	}
	else
	{
		fprintf(cgiOut, "<h2><font face=\"Broadway\"><font color=\"#FFFAF0\">Close!</font></font></H2>\n ");	
	}

	fprintf(cgiOut, "</BODY></HTML>\n");	
	sem_v (semid, 0);
	return 0;
}
#endif
