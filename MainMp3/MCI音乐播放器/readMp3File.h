#ifndef READMP3FILE_H
#define READMP3FILE_H


void readFileName( );
char * PATH_TO_FILENAME(int iChooseNumber);
/* 
ȫ�ֱ���
direct[100]�ٳɸ�����·��
strFileName[100][100]�洢���и�����;
iFileNumber��ǰ�ļ����¸���������
*/
extern int iFileNumber;
extern char strFileName[100][100];
void inputMp3FileDirect(char  direct1[100]);
void addMusicFile();
void deleteFile();
#endif