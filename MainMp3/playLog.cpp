#include<stdio.h>
#include<time.h>
#include"playLog.h"
void outputPlayInfo(char * playStr)
{
	FILE * fp;
	errno_t err;
	if ((err = fopen_s(&fp, "playLog.txt", "a") )!= 0)
	{
		return;
	}
	char timec[60];
	time_t timep;  
	time (&timep);
	ctime_s(timec, 60, &timep);
		fprintf(fp,"%s\t%s\n",playStr,timec);
	fclose(fp);
}
void outputErrInfo(char * errStr)
{
	FILE * fp;
	time_t timep;
	time(&timep);
	char time[20];
	errno_t err = fopen_s(&fp, "errLog.txt", "a");
	fprintf(fp, "%s\t%s\n", errStr, ctime_s(time, 20, &timep));
	fclose(fp);
}