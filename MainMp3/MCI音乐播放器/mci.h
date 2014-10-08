//歌曲播放的三种状态
#define PLAY 2
#define PAUSE 1
#define STOP 0
#define CIRCLE 10
#define LIST 20
#define RANDOM 30

//存放当前播放状态信息，用于显示输出
extern char strMessage[100];

//歌曲路径
extern char * path;

//歌曲名字
extern char * name;


//播放状态
extern int state;//歌曲播放当前状态

extern 
int mode;


void pause();//暂停播放
void resume();//恢复播放
void stop();//停止播放
void play();//播放音乐
DWORD getState();
void getAfter();
void getBefore();

