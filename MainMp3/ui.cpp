#include<stdio.h>
#include<windows.h>
#include<math.h>
#include"thread.h"
#include"readMp3File.h"
#include "mci.h"



int index;//播放歌曲序号
int beforIndex=-1;//上一首序号

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
		printf("请输入歌曲序号\n");
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
		printf("请输入选择页数\n");
		int n;
		scanf_s("%d", &n);
		if(n > sumPage){
			printf("选择页数过大\n");
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
	printf("\t\t\t欢迎使用亮剑MP3播放器\n");
	for(int i =0;i<40;i++)
		printf("—");
	printf("\n");
	//
	for(int i=start;i<end && i < iFileNumber; i ++)
	{
		printf("\t\t%d\t%s\n", i, strFileName[i]);
	}
	sumPage = iFileNumber/10+1;
	printf("\t\t共%d页，当前%d页\n", sumPage, curPage);
	for(int i =0;i<40;i++)
		printf("—");
	//printf("\n");
	printf("\t\t请按下述说明输入指令\n");
	printf("\t\t1  播放      2 暂停       3  继续       4 停止\n");
	printf("\t\t5  上一首    6 下一首     7  快进       8 快退\n");
	printf("\t\t9  顺序      10 随机      11 循环      12 退出\n");
	printf("\t\t13 其他页    14 上一页    15 下一页	   16 添加歌曲\n");
	printf("\t\t17 删除歌曲\n");
	printf("\n");
	printf("\t\t当前播放状态: %s\t播放模式 %s\n", strMessage, (mode == LIST) ?"顺序播放" : ((mode == CIRCLE) ?"循环播放" :"随机播放"));//
	
	for(int i =0;i<40;i++)
		printf("—");
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