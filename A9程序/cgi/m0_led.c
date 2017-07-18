#include <stdio.h> 
#include <string.h> 
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "msg.h"
#include "cgic.h" 

int cgiMain() 
{ 
	key_t key;
	char buf[2];
	int msgid;
	char sto_no[2];
	struct msg msg_buf;
	int cmd ;

	memset(&msg_buf,0,sizeof(msg_buf));


	cgiFormString("led",buf, sizeof(buf));
	cgiFormString("store", sto_no, 2);

	if((key = ftok("/root", 'g')) < 0)
	{
		perror("ftok");
		exit(1);
	}
	fprintf(stdout,"key = %d\n",key);
	if((msgid = msgget(1234567, IPC_CREAT|0666)) < 0)
	{

		exit(1);
	}
	fprintf(stdout,"msgid = %d\n",msgid);
	//msg_buf.text[0] = 97;
#if 1
	cmd  = buf[0] - '0';
	if (cmd)
		msg_buf.text[0]= ((sto_no[0] - 48)<< 6) | (2 << 4) | (1 << 0);
	else 
		msg_buf.text[0]= ((sto_no[0] - 48)<< 6) | (2 << 4) | (0 << 0);

#endif	
	msg_buf.type = MSG_LED;
	msg_buf.msgtype = MSG_UART_SND;
	msgsnd(msgid, &msg_buf, MSGSIZE, 0);


	cgiHeaderContentType("text/html\n\n"); 
	fprintf(cgiOut, "<HTML><HEAD>\n"); 
	fprintf(cgiOut, "<TITLE>My CGI</TITLE></HEAD>\n"); 
	fprintf(cgiOut, "<BODY>");  
	fprintf(cgiOut, "<H2>send sucess</H2>");
	fprintf(cgiOut,"data = %d\n",msg_buf.text[0]);
	fprintf(cgiOut, "<meta http-equiv=\"refresh\" content=\"1;url=../m0_1.html\">");
	fprintf(cgiOut, "</BODY>\n"); 
	fprintf(cgiOut, "</HTML>\n"); 


	return 0; 
}
