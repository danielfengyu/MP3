#include<windows.h>
#include"Mmsystem.h"
#include<stdio.h>
#pragma comment(lib,"winmm.lib")
#include"string.h"
#include "conio.h"
#include"mci.h"
#include "playLog.h"



char strMessage[100]="暂无歌曲";

//歌曲路径
char * path;

//歌曲名字
char * name;

bool flag = false;//播放标记

int mode=LIST;


//播放状态
int state;//歌曲播放当前状态
char buf[128];//缓冲区
MCI_OPEN_PARMS mciOpen;
MCIERROR mciError;



void open()//打开媒体
{
	mciOpen.lpstrDeviceType = "mpegvideo";
	mciOpen.lpstrElementName = path;//所要播放的歌曲路径
	mciError = mciSendCommand(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)&mciOpen);//打开歌曲
	if (mciError)
	{
		mciGetErrorString(mciError, buf, 128);
		sprintf_s(strMessage,"send MCI_OPEN command failed:%s",buf);
		outputErrInfo("打开歌曲文件错误");
	}
	outputPlayInfo("打开歌曲成功");
}


void pause()//暂停播放
{
	UINT DeviceID = mciOpen.wDeviceID;
	MCI_PLAY_PARMS mciPlay;
	mciError = mciSendCommand(DeviceID, MCI_PAUSE, 0, (DWORD)&mciPlay);
	if (mciError)
	{
		sprintf_s(strMessage,"send MCI_PAUSE command failed");
	}
	else
	{
		sprintf_s(strMessage, "歌曲已暂停：%s", name);
		state = PAUSE;
	}	
}
void resume()//恢复播放
{
	UINT DeviceID = mciOpen.wDeviceID;
	mciError=mciSendCommand(DeviceID, MCI_RESUME, MCI_WAIT, NULL); //暂停处播放
	if (mciError)
	{
		sprintf_s(strMessage,"send MCI_RESUME command failed");
	}
	else
	{
		sprintf_s(strMessage, "当前正在播放：%s", name);
		state = PLAY;
	}
}
void stop()//停止播放
{
	UINT DeviceID = mciOpen.wDeviceID;
	mciSendCommand(DeviceID, MCI_STOP, NULL, NULL);
	if (mciError)
	{
		sprintf_s(strMessage,"send MCI_STOP command failed");
	}
	else
	{
		sprintf_s(strMessage, "当前无歌曲播放");
		state = STOP;
		MCI_GENERIC_PARMS gp;
		gp.dwCallback=NULL;

		mciError=mciSendCommand(DeviceID,MCI_CLOSE,MCI_WAIT,(DWORD)&gp);//关闭播放

	}		
	flag=false;
}

void play()//播放音乐
{		
	if(flag == true)
	{
		stop();
	}
	open();//打开媒体
	UINT DeviceID = mciOpen.wDeviceID;
	MCI_PLAY_PARMS mciPlay;
	mciError = mciSendCommand(DeviceID, MCI_PLAY, 0, (DWORD)&mciPlay);//播放歌曲
	if (mciError)
	{
		sprintf_s(strMessage, "send MCI_PLAY command failed");
	}
	else
	{
		sprintf_s(strMessage, "当前正在播放：%s",name);
		state = PLAY;	
	}	
	flag=true;
	//
}

DWORD getState()
{
	MCI_STATUS_PARMS StatusParms;
	StatusParms.dwItem = MCI_STATUS_MODE;
	UINT DeviceID = mciOpen.wDeviceID;
	mciSendCommand (DeviceID, MCI_STATUS,MCI_WAIT | MCI_STATUS_ITEM,(DWORD)(LPVOID) &StatusParms);
	return StatusParms.dwReturn;
}

void getAfter()
{
	MCI_STATUS_PARMS StatusParms;
	StatusParms.dwItem = MCI_STATUS_POSITION;
	UINT DeviceID = mciOpen.wDeviceID;
	mciSendCommand(DeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID)&StatusParms);
	DWORD position = StatusParms.dwReturn;
	MCI_SEEK_PARMS SeekParms;
	SeekParms.dwTo = position + 10 * 1000;
	//跳转的目标时间，时间单位为毫秒
	mciSendCommand(DeviceID, MCI_SEEK, MCI_TO
		| MCI_WAIT, (DWORD)(LPVOID)
		&SeekParms);
	//play();
	MCI_PLAY_PARMS mciPlay;
	mciError = mciSendCommand(DeviceID, MCI_PLAY, 0, (DWORD)&mciPlay);//播放歌曲
	mciSendCommand(DeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID)&StatusParms);
	if (mciError)
	{
		sprintf_s(strMessage, "send MCI_PLAY command failed");
	}
	else
	{
		sprintf_s(strMessage, "当前正在播放：%s", name);
		state = PLAY;
	}
	flag = true;
}
void getBefore()
{
	MCI_STATUS_PARMS StatusParms;
	StatusParms.dwItem = MCI_STATUS_POSITION;
	UINT DeviceID = mciOpen.wDeviceID;
	mciSendCommand(DeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID)&StatusParms);
	DWORD position = StatusParms.dwReturn;
	MCI_SEEK_PARMS SeekParms;
	SeekParms.dwTo = position - 10 * 1000;
	//跳转的目标时间，时间单位为毫秒
	mciSendCommand(DeviceID, MCI_SEEK, MCI_TO
		| MCI_WAIT, (DWORD)(LPVOID)
		&SeekParms);
	//play();
	MCI_PLAY_PARMS mciPlay;
	mciError = mciSendCommand(DeviceID, MCI_PLAY, 0, (DWORD)&mciPlay);//播放歌曲
	mciSendCommand(DeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID)&StatusParms);
	if (mciError)
	{
		sprintf_s(strMessage, "send MCI_PLAY command failed");
	}
	else
	{
		sprintf_s(strMessage, "当前正在播放：%s", name);
		state = PLAY;
	}
	flag = true;
}





