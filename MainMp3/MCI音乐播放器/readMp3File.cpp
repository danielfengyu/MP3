#include<windows.h>
#include<stdio.h>
#include"Mmsystem.h"
#pragma comment(lib,"winmm.lib")
#include<string.h>
#include "conio.h"
#include<io.h>
#include"readMp3File.h"
/***********************************************/

/***********************************************/

char tempStr[100];
char direct1[100]=" I:\\KuGou\\ ";
char direct[100]="I:\\KuGou\\";
int iFileNumber=0;
char strFileName[100][100];
/***********************************************/
/* 
extenceFile�ļ���չ��
�õ�ָ��·���µ���չ��ΪextendFile�������ļ�������ȫ�ֱ�������
strFileame[100][100];
*/
/***********************************************/
void readFileName( )
{
	long Handle;
	char temp[100];
	char *extendFile="*.mp3";//�����ļ���չ��
	struct _finddata_t FileInfo;//�����ļ���Ϣ�Ľṹ��
	//inputMp3FileDirect("D:\\TTPmusic\\");
	strcpy_s(temp, direct);//����
	strcat_s(temp,extendFile);
	//�õ�ָ��·���µ���չ��Ϊ�������ļ�
	if((Handle=_findfirst(temp,&FileInfo))==-1L)
		return ;
	else
	{
		strcpy_s(strFileName[iFileNumber],FileInfo.name);
		iFileNumber=1;
		while( _findnext(Handle,&FileInfo)==0) 
		{
			strcpy_s(strFileName[iFileNumber],FileInfo.name);
			iFileNumber++;
		}
		_findclose(Handle); 
	}
}
char * PATH_TO_FILENAME(int iChooseNumber)
{
	strcpy_s(tempStr,direct);
	iChooseNumber=iChooseNumber-1;
	strcat_s(tempStr,100, strFileName[iChooseNumber]);
	return tempStr;
}
void inputMp3FileDirect(char  direct1[100])
{
	direct[100]=direct1[100];
}
void addMusicFile()
{
	char temp[100];
	char b[100]="xcopy ";
	char c[100];//[100]="D:\\Downloads\\QQMUSIC\\29.mp3";
	printf("��קҪ��ӵĸ�����");
	scanf("%s",&c);
	//strcpy(temp,direct);
	strcat(b,c);
	strcat(b,direct1);
	system(b);
}
void deleteFile()
{
	int iNumber;
	char temp[100];
	strcpy(temp,direct);
	printf("����Ҫɾ����������ţ�");
	scanf("%d",&iNumber);
	strcat(temp,strFileName[iNumber]);
	remove(temp);
}