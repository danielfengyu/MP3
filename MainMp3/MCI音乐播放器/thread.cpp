#include <windows.h>
#include <stdio.h>
#include "thread.h"
#include "mci.h"
#include "ui.h"

int order=-1;//全局变量，改变播放器状态

//函数结构体，动态调用函数
struct staFunc{
	int status;
	void (*func)(void);
}StaFunc;
const int STA_LENGTH = 6;
struct staFunc sf[STA_LENGTH];
/*
函数功能：初始化函数指针
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
函数功能：多线程处理函数
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
函数功能：启动多线程
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