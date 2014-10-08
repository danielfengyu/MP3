#ifndef READMP3FILE_H
#define READMP3FILE_H


void readFileName( );
char * PATH_TO_FILENAME(int iChooseNumber);
/* 
全局变量
direct[100]促成歌曲的路径
strFileName[100][100]存储所有歌曲名;
iFileNumber当前文件夹下歌曲的数量
*/
extern int iFileNumber;
extern char strFileName[100][100];
void inputMp3FileDirect(char  direct1[100]);
void addMusicFile();
void deleteFile();
#endif