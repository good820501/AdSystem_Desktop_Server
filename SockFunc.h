#ifndef SOCKFUNC_H
#define SOCKFUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock.h>

#define VERSION_MAJOR 1         //���汾
#define VERSION_MINOR 1         //���汾

#define MAX_CLIENT      10
#define OVERTIME        30

//��ʼ��WinSock
bool    InitWS(void);
//��ʼ��Socket������
//ָ���˿ڣ����������Բ�ָ��
SOCKET  InitServer(int port, char *server=NULL);
//����Socket�ͻ�������
SOCKET  AcceptClient(SOCKET sockserver, int overtime=0);
//����Socket��������ָ���������Ͷ˿�
SOCKET  ConnectToServer(int port, char *server);
//ָ��ʱ������Socket��������ָ���������Ͷ˿�
SOCKET  AsyConnectToServer(int port, char *server, int overtime=10);
//����ָ�����ȵ�����
int     SendData(SOCKET sockfd, char *buf, int size, int overtime=OVERTIME);
//����ָ�����ȵĻ���������
bool    SendBuff(SOCKET sockfd, char *buf, int size, int overtime=OVERTIME);
//����ָ�����ȵ�����
int     RecvData(SOCKET sockfd, char *buf, int size, int overtime=OVERTIME);
//����ָ�����������ȵ�����
int     RecvBuff(SOCKET sockfd, char **ppbuf, int overtime=OVERTIME);
//��������ģʽ
bool    SetNoBlockMode(SOCKET sockfd, bool mode);
//�ر�Socket����
bool    CloseSocket(SOCKET sockfd);
//�˳�SocketӦ��
bool    CloseWS(void);

//������
//���ж�һ���ַ����Ƿ����IP��ַ��ʽ
bool    isip(char *ip);
char    *getlocalhostip(char *ip);
void delenter(char *psztmp);
#endif
 