//�������ŵ�����״̬
#define PLAY 2
#define PAUSE 1
#define STOP 0
#define CIRCLE 10
#define LIST 20
#define RANDOM 30

//��ŵ�ǰ����״̬��Ϣ��������ʾ���
extern char strMessage[100];

//����·��
extern char * path;

//��������
extern char * name;


//����״̬
extern int state;//�������ŵ�ǰ״̬

extern 
int mode;


void pause();//��ͣ����
void resume();//�ָ�����
void stop();//ֹͣ����
void play();//��������
DWORD getState();
void getAfter();
void getBefore();

