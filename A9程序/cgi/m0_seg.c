#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <errno.h>
#include "cgic.h"
#include "msg.h"
#define STORAGE_NO '1'
char errflag = 0;

int cgiMain()
{
	struct msg msg_buf;
	key_t key;
	int msgid;
	char buf[4] = {0};
	char segvalue[2] = {0};
	cgiFormString("seg", buf, 4);
	cgiFormString("seg_val", segvalue, 2);
	
	if((key = ftok("/root", 'g')) < 0)
	{
		perror("ftok");
		exit(1);
	}

	if((msgid = msgget(1234567,IPC_CREAT|0666)) < 0)
	{
		perror("msgget");
		exit(1);
	}
		if(strncmp(buf,"off", 3) == 0)
	{
		msg_buf.text[0] = ((STORAGE_NO - 48)) << 6 | (3 << 4) | (0xf << 0);
	}
	else if (strncmp(buf, "on", 2) == 0)
	{
		msg_buf.text[0] = ((STORAGE_NO - 48)) << 6 | (3 << 4) | (segvalue[0] << 0);
	} 
	else 
	{
		errflag = 3;
	}
	msg_buf.type = MSGTYPE;
	msg_buf.msgtype = MSG_UART_SND;
	msgsnd(msgid, &msg_buf, MSGSIZE, 0);




	
	cgiHeaderContentType("text/html\n\n"); 
	fprintf(cgiOut, "<HTML><HEAD>\n"); 
	fprintf(cgiOut, "<TITLE>My CGI</TITLE></HEAD>\n"); 
	fprintf(cgiOut, "<BODY>"); 
	fprintf(cgiOut, "<H2>send sucess</H2>");
	fprintf(cgiOut,"data = %x\n",msg_buf.text[0]);
	fprintf(cgiOut,"data1= %d\n",segvalue[0]);
	fprintf(cgiOut, "<meta http-equiv=\"refresh\" content=\"1;url=../m0_1.html\">");
	fprintf(cgiOut, "</BODY>\n"); 
	fprintf(cgiOut, "</HTML>\n"); 


	return 0; 
}
