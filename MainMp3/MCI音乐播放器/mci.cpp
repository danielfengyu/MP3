#include<windows.h>
#include"Mmsystem.h"
#include<stdio.h>
#pragma comment(lib,"winmm.lib")
#include"string.h"
#include "conio.h"
#include"mci.h"
#include "playLog.h"



char strMessage[100]="���޸���";

//����·��
char * path;

//��������
char * name;

bool flag = false;//���ű��

int mode=LIST;


//����״̬
int state;//�������ŵ�ǰ״̬
char buf[128];//������
MCI_OPEN_PARMS mciOpen;
MCIERROR mciError;



void open()//��ý��
{
	mciOpen.lpstrDeviceType = "mpegvideo";
	mciOpen.lpstrElementName = path;//��Ҫ���ŵĸ���·��
	mciError = mciSendCommand(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)&mciOpen);//�򿪸���
	if (mciError)
	{
		mciGetErrorString(mciError, buf, 128);
		sprintf_s(strMessage,"send MCI_OPEN command failed:%s",buf);
		outputErrInfo("�򿪸����ļ�����");
	}
	outputPlayInfo("�򿪸����ɹ�");
}


void pause()//��ͣ����
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
		sprintf_s(strMessage, "��������ͣ��%s", name);
		state = PAUSE;
	}	
}
void resume()//�ָ�����
{
	UINT DeviceID = mciOpen.wDeviceID;
	mciError=mciSendCommand(DeviceID, MCI_RESUME, MCI_WAIT, NULL); //��ͣ������
	if (mciError)
	{
		sprintf_s(strMessage,"send MCI_RESUME command failed");
	}
	else
	{
		sprintf_s(strMessage, "��ǰ���ڲ��ţ�%s", name);
		state = PLAY;
	}
}
void stop()//ֹͣ����
{
	UINT DeviceID = mciOpen.wDeviceID;
	mciSendCommand(DeviceID, MCI_STOP, NULL, NULL);
	if (mciError)
	{
		sprintf_s(strMessage,"send MCI_STOP command failed");
	}
	else
	{
		sprintf_s(strMessage, "��ǰ�޸�������");
		state = STOP;
		MCI_GENERIC_PARMS gp;
		gp.dwCallback=NULL;

		mciError=mciSendCommand(DeviceID,MCI_CLOSE,MCI_WAIT,(DWORD)&gp);//�رղ���

	}		
	flag=false;
}

void play()//��������
{		
	if(flag == true)
	{
		stop();
	}
	open();//��ý��
	UINT DeviceID = mciOpen.wDeviceID;
	MCI_PLAY_PARMS mciPlay;
	mciError = mciSendCommand(DeviceID, MCI_PLAY, 0, (DWORD)&mciPlay);//���Ÿ���
	if (mciError)
	{
		sprintf_s(strMessage, "send MCI_PLAY command failed");
	}
	else
	{
		sprintf_s(strMessage, "��ǰ���ڲ��ţ�%s",name);
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
	//��ת��Ŀ��ʱ�䣬ʱ�䵥λΪ����
	mciSendCommand(DeviceID, MCI_SEEK, MCI_TO
		| MCI_WAIT, (DWORD)(LPVOID)
		&SeekParms);
	//play();
	MCI_PLAY_PARMS mciPlay;
	mciError = mciSendCommand(DeviceID, MCI_PLAY, 0, (DWORD)&mciPlay);//���Ÿ���
	mciSendCommand(DeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID)&StatusParms);
	if (mciError)
	{
		sprintf_s(strMessage, "send MCI_PLAY command failed");
	}
	else
	{
		sprintf_s(strMessage, "��ǰ���ڲ��ţ�%s", name);
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
	//��ת��Ŀ��ʱ�䣬ʱ�䵥λΪ����
	mciSendCommand(DeviceID, MCI_SEEK, MCI_TO
		| MCI_WAIT, (DWORD)(LPVOID)
		&SeekParms);
	//play();
	MCI_PLAY_PARMS mciPlay;
	mciError = mciSendCommand(DeviceID, MCI_PLAY, 0, (DWORD)&mciPlay);//���Ÿ���
	mciSendCommand(DeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID)&StatusParms);
	if (mciError)
	{
		sprintf_s(strMessage, "send MCI_PLAY command failed");
	}
	else
	{
		sprintf_s(strMessage, "��ǰ���ڲ��ţ�%s", name);
		state = PLAY;
	}
	flag = true;
}





