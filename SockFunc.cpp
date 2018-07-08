#include "Debug.h"
#include "Libs.h"                     
#include "SockFunc.h"

//初始化WinSock
//系统使用WinSock函数之前，必须初始化
bool  InitWS(void)
{
        int  err;
        WSADATA  WsaData;
        WORD  VersionRequested;

        VersionRequested=MAKEWORD(VERSION_MAJOR,VERSION_MINOR);//版本

        err=WSAStartup(VersionRequested,&WsaData);//启动WinSock

        if(err != 0){
                MonitorErr.WriteMsg("InitWS\t\t\t\t系统Sock版本低!");
                return false;
        }
        else
        {
                if(LOBYTE(WsaData.wVersion)!=VERSION_MAJOR||HIBYTE(WsaData.wVersion)!=VERSION_MINOR)
                {
                        WSACleanup();
                        MonitorErr.WriteMsg("InitWS\t\t\t\t系统Sock版本低!");
                        return false;
                }
        }
        return true;
}

//初始化Socket服务器
//指定端口，服务器可以不指定
SOCKET  InitServer(int port, char *server)
{
        int     i;
        SOCKET  listen_socket;
        struct  sockaddr_in server_addr;

        if(port <= 0){
                return INVALID_SOCKET;
        }

        //声明一个socket套接字
	listen_socket = socket(AF_INET, SOCK_STREAM,0);
	if (listen_socket == INVALID_SOCKET){
                MonitorErr.WriteMsg("InitServer\t\t\t声明套接字出现错误");
                return INVALID_SOCKET;
	}

        //初始化套接字
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family  = AF_INET;
        server_addr.sin_port    = htons(port);
        if(server == NULL || strlen(server) == 0){//没指定服务器地址，使用任意所有的IP地址
                server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        }
        else if(isip(server)){//指定的服务器是服务器IP地址
                server_addr.sin_addr.s_addr = inet_addr(server);
        }
        else{//指定的服务器是服务器名称
        	struct hostent *hp;

		hp = gethostbyname(server);
                if(hp == NULL){
                        MonitorErr.WriteMsg((AnsiString)"InitServer\t\t\t找不到指定的服务器["+server+(AnsiString)"]");
                        CloseSocket(listen_socket);
                        return INVALID_SOCKET;
                }
                memcpy(&(server_addr.sin_addr), hp->h_addr, hp->h_length);
        }

        i = 1;
        setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&i, sizeof(i));

        //套接字绑定
	if(bind(listen_socket,(struct sockaddr*)&server_addr,sizeof(server_addr)) == SOCKET_ERROR){
//                MonitorErr.WriteMsg("InitServer\t\t\t绑定端口出现错误!");
                CloseSocket(listen_socket);
                return INVALID_SOCKET;
        }

        //在指定端口监听客户端连接
        if(listen(listen_socket, MAX_CLIENT) == SOCKET_ERROR){
                MonitorErr.WriteMsg("InitServer\t\t\t启动监听出现错误!");
                CloseSocket(listen_socket);
                return INVALID_SOCKET;
        }

        return listen_socket;
}

//接收Socket客户端连接
SOCKET  AcceptClient(SOCKET sockserver, int overtime)
{
        if(overtime == 0){
                return accept(sockserver, NULL, NULL);
        }
        else{
                SOCKET sockclient = INVALID_SOCKET;
        	fd_set  readfds;
                struct  timeval tv;
                int     selnum;

                DWORD   dw = GetTickCount();
                while((int)(GetTickCount() - dw) < 1000*overtime){
                        sockclient = accept(sockserver, NULL, NULL);
                        if(INVALID_SOCKET != sockclient){
                                break;
                        }
                }
                return sockclient;
        }
}

//连接Socket服务器，指定服务器和端口
SOCKET  ConnectToServer(int port, char *server)
{
	SOCKET sockfd;
	struct sockaddr_in servaddr;

        //声明一个socket套接字
	sockfd = socket(AF_INET, SOCK_STREAM,0);
	if (sockfd == INVALID_SOCKET){
                MonitorErr.WriteMsg("ConnectToServer\t\t\t声明套接字出现错误");
                return INVALID_SOCKET;
	}

        //初始化套接字
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
        servaddr.sin_addr.s_addr = inet_addr(server);
	if (servaddr.sin_addr.s_addr == INADDR_NONE)
	{
                MonitorErr.WriteMsg("ConnectToServer\t\t\tIP地址错误");
                CloseSocket(sockfd);
                return INVALID_SOCKET;
        }
        
        //连接服务器
        if(connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) == SOCKET_ERROR){
                char    buff[1024];
                GetLastErrMsg(buff);
                delenter(buff);
                MonitorErr.WriteMsg((AnsiString)"ConnectToServer\t\t连接服务器["+server+ " " + IntToStr(port) + (AnsiString)"]出现错误："+(AnsiString)buff);
                CloseSocket(sockfd);
                return INVALID_SOCKET;
        }
        return sockfd;
}

//异步连接Socket服务器，指定服务器和端口
SOCKET  AsyConnectToServer(int port, char *server, int overtime)
{
	SOCKET  sockfd;
	struct  sockaddr_in servaddr;
        struct  timeval tv;
        int     selnum;
	fd_set  writefds;

        //声明一个socket套接字
	sockfd = socket(AF_INET, SOCK_STREAM,0);
	if (sockfd == INVALID_SOCKET){
                MonitorErr.WriteMsg("AsyConnectToServer\t\t声明套接字出现错误");
                return INVALID_SOCKET;
	}
        SetNoBlockMode(sockfd, true);

        //初始化套接字
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons((u_short)port);
        servaddr.sin_addr.s_addr = inet_addr(server);
	if (servaddr.sin_addr.s_addr == INADDR_NONE)
	{
                MonitorErr.WriteMsg("AsyConnectToServer\t\tIP地址错误");
                CloseSocket(sockfd);
                return INVALID_SOCKET;
        }

        //连接服务器
        connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));

        FD_ZERO(&writefds);
        FD_SET(sockfd, &writefds);
        tv.tv_sec = overtime;
        tv.tv_usec = 0;
        selnum = select(0, NULL, &writefds, NULL , &tv);
        if (selnum == 0 || selnum == SOCKET_ERROR){
                CloseSocket(sockfd);
                return INVALID_SOCKET;
        }

        if (FD_ISSET(sockfd, &writefds) != 0){
        	FD_CLR(sockfd, &writefds);
                return sockfd;
        }
        else{
        	FD_CLR(sockfd, &writefds);
                CloseSocket(sockfd);
                return INVALID_SOCKET;
        }
}

//发送指定长度的数据
int     SendData(SOCKET sockfd, char *buf, int datasize, int overtime)
{
        int     n,i;
        int     errno;
        MSG     msg;

        n = 0;
        DWORD   dw = GetTickCount();
        while(1){
                i = datasize - n;
                if (i <= 0)
                {
                        break;
                }
                else if (i > 1024)
                {
                        i = 1024;
                }

                //判断是否超时
                if((int)(GetTickCount() - dw) > 1000*overtime){//超时
                        break;
                }

                //执行其他操作
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
                {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

                i = send(sockfd, &buf[n], i, 0);
                if (i <= 0)
                {
                        i = 0;
                        errno = WSAGetLastError();
                        if(WSAEINTR != errno && WSAEWOULDBLOCK != errno && 0 != errno){
                                MonitorErr.WriteMsg("SendData\t\t\t\terrno：" + IntToStr(errno));
                                break;
                        }
                }
                n += i;
        }
        
        return n;
}

//发送指定长度的缓冲区数据
bool    SendBuff(SOCKET sockfd, char *buf, int size, int overtime)
{
        char DataLen[10];

        if(size < 0){
                return false;
        }

        sprintf(DataLen,"%08d",size);
        if(SendData(sockfd, DataLen, 8, overtime) != 8){
                return false;
        }
        if(SendData(sockfd, buf, size, overtime) != size){
                return false;
        }

        return true;
}

//接收指定长度的数据
int     RecvData(SOCKET sockfd, char *buf, int size, int overtime)
{
        int     n,i;
        int     errno;
        MSG     msg;

        if(size < 0){
                return false;
        }

        n = 0;
        DWORD   dw = GetTickCount();
        while(1){
                i = size - n;
                if (i <= 0)
                {
                        break;
                }
                else if (i > 1024)
                {
                        i = 1024;
                }

                //判断是否超时
                if((int)(GetTickCount() - dw) > 1000*overtime){
                        break;
                }

                //执行其他操作
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
                {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

                if ((i = recv(sockfd, &buf[n], i, 0)) == 0)
                {
                        break;
                }
                else if(i == SOCKET_ERROR)
                {
                        i = 0;
                        errno = WSAGetLastError();
                        if(WSAEINTR != errno && WSAEWOULDBLOCK != errno && 0 != errno){
                                MonitorErr.WriteMsg("RecvData\t\t\t\terrno：" + IntToStr(errno));
                                break;
                        }
                }
                n += i;
        }
        return n;
}

//接收指定缓冲区长度的数据
int    RecvBuff(SOCKET sockfd, char **ppbuf, int overtime)
{
        int     recvlen;
        char    DataLen[10];

        if (ppbuf == NULL)
        {
                return -1;
        }

        if(RecvData(sockfd, DataLen, 8, overtime) != 8)
        {
                MonitorErr.WriteMsg("RecvBuff\t\t\t\t接收包头错误");
                return -1;
        }

        DataLen[8] = 0;
        recvlen = atoi(DataLen);
        *ppbuf = (char *)malloc(recvlen+1);
        if (*ppbuf == NULL)
        {
                return -1;
        }

        memset(*ppbuf, 0x00, recvlen+1);
        if(RecvData(sockfd, *ppbuf, recvlen, overtime) != recvlen)
        {
                free(*ppbuf);
                MonitorErr.WriteMsg("RecvBuff\t\t\t\t接收包数据错误");
                return -1;
        }

        return recvlen;
}

//设置阻塞模式
bool    SetNoBlockMode(SOCKET sockfd, bool mode)
{
        u_long    argp = 0;
        if(mode){
                argp = 1;
        }
	if(ioctlsocket(sockfd, FIONBIO, &argp) == SOCKET_ERROR){
                return false;
        }
        return true;
}

//关闭Socket连接
bool    CloseSocket(SOCKET sockfd)
{
        int     err;
        struct  linger lg;

        SetNoBlockMode(sockfd, false);
        while(1)
        {
                err = closesocket(sockfd);
                if(err == SOCKET_ERROR){
                        err = WSAGetLastError();
                        MonitorErr.WriteMsg("CloseSocket\t\t\t err：" + IntToStr(err));
                        if (err != WSAEINTR)
                        {
                                break;
                        }
                }
                else
                {
                        break;
                }
        }

        lg.l_onoff = 0;
        lg.l_linger = 0;
        setsockopt(sockfd, SOL_SOCKET, SO_LINGER, (char *)&lg,sizeof(lg));
        closesocket(sockfd);
        return true;
}

//退出Socket应用
bool    CloseWS(void)
{
        int     err;

        err = WSACleanup();
        if(err == SOCKET_ERROR){
                return false;
        }
        else{
                return true;
        }
}

//简单判断一个字符串是否符合IP地址格式
bool    isip(char *ip)
{
        size_t i;

        if(strlen(ip) < 7){//0.0.0.0 255.255.255.255
                return false;
        }

        i = 0;
        while(i < strlen(ip)){
                if(isalpha(ip[i]) && ip[i] != '.'){
                        return false;
                }
                i++;
        }
        return true;
}

char    *getlocalhostip(char *ip)
{
        char    hostname[128];

      	struct hostent *he;
        struct in_addr sin_addr;

        if (ip == NULL){
                return ip;
        }

        gethostname(hostname, sizeof(hostname));
        he = gethostbyname(hostname);
        if(he == NULL){
                return NULL;
        }
        memcpy(&sin_addr, he->h_addr, he->h_length);
        strcpy(ip, inet_ntoa(sin_addr));
        return ip;
}
/*libs
**************************************************************************/

/*把回车换行删除
*************************************************************************/
void delenter(char *psztmp)
{
        while(*psztmp){
                if(*psztmp == '\n' || *psztmp == '\r'){
                        *psztmp = 0;
                        return;
                }
                psztmp++;
        }
}

