#include <windows.h>
#include <stdio.h>
#include "thread.h"
#include "mci.h"
#include "ui.h"

int order=-1;//ȫ�ֱ������ı䲥����״̬

//�����ṹ�壬��̬���ú���
struct staFunc{
	int status;
	void (*func)(void);
}StaFunc;
const int STA_LENGTH = 6;
struct staFunc sf[STA_LENGTH];
/*
�������ܣ���ʼ������ָ��
*/
void initFuc()
{
	sf[0].status=1;
	sf[0].func = play;
	sf[1].status=2;
	sf[1].func = pause;
	sf[2].status=3;
	sf[2].func = resume;
	sf[3].status=4;
	sf[3].func = stop; 
	sf[4].status = 7;
	sf[4].func = getAfter;
	sf[5].status =8;
	sf[5].func = getBefore;

}
/*
�������ܣ����̴߳�����
*/
DWORD WINAPI ThreadProc( LPVOID lpParam ) 
{
	while(true){
		for(int i=0;order!=-1 && i < STA_LENGTH; i++){
			if(sf[i].status == order){
				(*sf[i].func)();
				break;
			}
		}
		order=-1;
		int state = getState();
		if ((state < 524 && state > 530) && state > 0)
		{
			NextSong();
		}
		Sleep(100);
	}
	return 0;
}
/*
�������ܣ��������߳�
*/
void init_thread()
{
	initFuc();
	CreateThread( 
            NULL,              // default security attributes
            0,                 // use default stack size  
            ThreadProc,        // thread function 
            NULL,             // argument to thread function 
            0,                 // use default creation flags 
            NULL);           // returns the thread identifier 
}