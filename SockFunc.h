#ifndef SOCKFUNC_H
#define SOCKFUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock.h>

#define VERSION_MAJOR 1         //主版本
#define VERSION_MINOR 1         //付版本

#define MAX_CLIENT      10
#define OVERTIME        30

//初始化WinSock
bool    InitWS(void);
//初始化Socket服务器
//指定端口，服务器可以不指定
SOCKET  InitServer(int port, char *server=NULL);
//接收Socket客户端连接
SOCKET  AcceptClient(SOCKET sockserver, int overtime=0);
//连接Socket服务器，指定服务器和端口
SOCKET  ConnectToServer(int port, char *server);
//指定时间连接Socket服务器，指定服务器和端口
SOCKET  AsyConnectToServer(int port, char *server, int overtime=10);
//发送指定长度的数据
int     SendData(SOCKET sockfd, char *buf, int size, int overtime=OVERTIME);
//发送指定长度的缓冲区数据
bool    SendBuff(SOCKET sockfd, char *buf, int size, int overtime=OVERTIME);
//接收指定长度的数据
int     RecvData(SOCKET sockfd, char *buf, int size, int overtime=OVERTIME);
//接收指定缓冲区长度的数据
int     RecvBuff(SOCKET sockfd, char **ppbuf, int overtime=OVERTIME);
//设置阻塞模式
bool    SetNoBlockMode(SOCKET sockfd, bool mode);
//关闭Socket连接
bool    CloseSocket(SOCKET sockfd);
//退出Socket应用
bool    CloseWS(void);

//函数库
//简单判断一个字符串是否符合IP地址格式
bool    isip(char *ip);
char    *getlocalhostip(char *ip);
void delenter(char *psztmp);
#endif
 