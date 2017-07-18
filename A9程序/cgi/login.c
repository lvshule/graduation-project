#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sqlite3.h>

#include "cgic.h"


#define N	128

int cgiMain()
{
	
	char name[N] = {0};
	char pw[N] = {0};
	char sql[N] = {0};
	char **result;
	int row, column;
	sqlite3 *db;

	cgiFormStringNoNewlines("username", name, N);
	cgiFormStringNoNewlines("userpass", pw, N);

	cgiHeaderContentType("text/html");
	fprintf(cgiOut, "<HTML>\n");
	fprintf(cgiOut, "<HTML><HEAD>\n");
	fprintf(cgiOut, "<TITLE>Login Promp</TITLE></HEAD>\n");
	
	if(sqlite3_open("user.db", &db) != SQLITE_OK)
	{
		fprintf(cgiOut, "<BODY>");
		fprintf(cgiOut, "<H1>%s</H1>", "Server is busy...");		
		fprintf(cgiOut, "<meta http-equiv=\"refresh\" content=\"1;url=../index.html\">");
		return -1;
	}

	sprintf(sql, "select * from user where name='%s' and password='%s'", name, pw);

	if(sqlite3_get_table(db, sql, &result, &row, &column, NULL) != SQLITE_OK)
	{
		fprintf(cgiOut, "<BODY>");
		fprintf(cgiOut, "<font color=\"blue\" size=\"6\"> <h1><u><div align=\"center\"> %s </div></u></h1></font>", "Server is busy...");	
		fprintf(cgiOut, "<meta http-equiv=\"refresh\" content=\"1;url=../index.html\">");
		sqlite3_close(db);
		return -1;
	}

	if(row == 0)
	{
		fprintf(cgiOut, "<BODY>");
		fprintf(cgiOut, "<font color=\"blue\" size=\"6\"> <h1><u><div align=\"center\"> %s </div></u></h1></font>", "Name or password error");		
		fprintf(cgiOut, "<meta http-equiv=\"refresh\" content=\"1;url=../index.html\">");
		sqlite3_close(db);
		return 0;
	}

	fprintf(cgiOut, "<BODY>");
	fprintf(cgiOut, "<font color=\"blue\" size=\"6\"> <h1><u><div align=\"center\"> %s </div></u></h1></font>", "Login OK!");		
	fprintf(cgiOut, "<meta http-equiv=\"refresh\" content=\"1;url=../env1.html\">");
	sqlite3_close(db);
	return 0;
	
}


