#include<stdio.h>
#include<windows.h>
#include<math.h>
#include"thread.h"
#include"readMp3File.h"
#include "mci.h"



int index;//���Ÿ������
int beforIndex=-1;//��һ�����

int start=0;
int end=10;
int curPage=1;
int sumPage=0;

void playList();
void NextSong();
void Command()
{
	system("color 81");
	int i;
	
	order=-1;
	index=-1;
	init_thread();
	while(true){
		while(order != -1){
			;
		}
		system("cls");
		readFileName();
		playList();
	scanf_s("%d",&i);
	if(i==1){
		printf("������������\n");
		int n;
		scanf_s("%d", &n);
		if (index != -1){
			beforIndex = index;
		}
		index=n;
		path=PATH_TO_FILENAME(index+1);
		name=strFileName[index];
		order=i;

	}
	if (i == 5){
		if (beforIndex != -1){
			index = beforIndex;
			beforIndex = -1;
			path = PATH_TO_FILENAME(index + 1);
			name = strFileName[index];
			order = 1;
			continue;
		}
	}
	if (i == 6){
		beforIndex = index;
		NextSong();
		continue;
	}
	if(i == 9){
		mode=LIST;
	}
	if(i == 10){
		mode=RANDOM;
	}
	if(i == 11){
		mode=CIRCLE;
	}
	if(i == 12){
		exit(0);
	}
	if(i == 13){
		printf("������ѡ��ҳ��\n");
		int n;
		scanf_s("%d", &n);
		if(n > sumPage){
			printf("ѡ��ҳ������\n");
			Sleep(300);
		}
		else{
			curPage=n;
			start = (curPage-1)*10;
			end = start+10;
		}
	}
	if(i == 14){
		if(curPage>1){
			curPage--;
			start = (curPage-1)*10;
			end = start+10;
		}
	}
	
	if(i == 15){
		if(curPage<sumPage){
			curPage++;
			start = (curPage-1)*10;
			end = start+10;
		}
	}
	if(i==16)
	{
		addMusicFile();
		Sleep(1000);
	}
	if(i==17)
	{
		deleteFile();
		
	}
	order=i;
	}
}

void playList()
{
	printf("\t\t\t��ӭʹ������MP3������\n");
	for(int i =0;i<40;i++)
		printf("��");
	printf("\n");
	//
	for(int i=start;i<end && i < iFileNumber; i ++)
	{
		printf("\t\t%d\t%s\n", i, strFileName[i]);
	}
	sumPage = iFileNumber/10+1;
	printf("\t\t��%dҳ����ǰ%dҳ\n", sumPage, curPage);
	for(int i =0;i<40;i++)
		printf("��");
	//printf("\n");
	printf("\t\t�밴����˵������ָ��\n");
	printf("\t\t1  ����      2 ��ͣ       3  ����       4 ֹͣ\n");
	printf("\t\t5  ��һ��    6 ��һ��     7  ���       8 ����\n");
	printf("\t\t9  ˳��      10 ���      11 ѭ��      12 �˳�\n");
	printf("\t\t13 ����ҳ    14 ��һҳ    15 ��һҳ	   16 ��Ӹ���\n");
	printf("\t\t17 ɾ������\n");
	printf("\n");
	printf("\t\t��ǰ����״̬: %s\t����ģʽ %s\n", strMessage, (mode == LIST) ?"˳�򲥷�" : ((mode == CIRCLE) ?"ѭ������" :"�������"));//
	
	for(int i =0;i<40;i++)
		printf("��");
}

void NextSong()
{
	if(mode == RANDOM){
		index=rand()%iFileNumber+1;
		path=PATH_TO_FILENAME(index+1);
		name=strFileName[index];
	}
	else if(mode == CIRCLE){
		index=index;
	}
	else if(mode == LIST){
		index++;
		path=PATH_TO_FILENAME(index+1);
		name=strFileName[index];
	}
	order = 1;
}