//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Debug.h"
#include "Unit13.h"
#include "stdio.h"
#include "Libs.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CGAUGES"
#pragma resource "*.dfm"
TForm13 *Form13;
//---------------------------------------------------------------------------
__fastcall TForm13::TForm13(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

//远程控制指令发送
//CmdFlag：1：关机；2：重启；3：暂停服务；4：启动服务;5：下载数据库文件；6：上传数据库文件
//7:下载配置文件；8：上传配置文件
bool __fastcall TForm13::SendCtrlCmd(AnsiString IP, AnsiString Port, int CmdFlag,BOOL   Disp)
{
        //TODO: Add your source code here
        char    SendCmd[16];
        char    *precv;
        SOCKET	clientfd;
        int     n;
        int     ServerPort;
        ServerPort=StrToInt(Port);
        clientfd=AsyConnectToServer(ServerPort,IP.c_str());
        precv=NULL;
        if(clientfd!=INVALID_SOCKET)
        {
                MonitorErr.WriteMsg("\t\t\t远程控制指令执行---工作套接字创建成功!");
                if(CmdFlag==1)//关机
                {
                        memset(SendCmd,0,sizeof(SendCmd));
                        sprintf(SendCmd,"%s","210100");
                        if(Disp)
                        {
                                this->Edit2->Text=IP;
                                this->Edit3->Text="关闭机器";
                                this->Show();
                        }
                        SendBuff(clientfd,SendCmd,strlen(SendCmd));
                        n = RecvBuff(clientfd, &precv);
                        if(n == -1)
                        {
                                MonitorErr.WriteMsg("RemoteServ\t\t\t远程控制指令执行---关机失败！");
                        }
                        else    if(strncmp(precv, "1011", 4) == 0)
                        {
                                MonitorErr.WriteMsg("RemoteServ\t\t\t远程控制指令执行---关机成功！");
                        }
                        if(Disp)
                        {
                               this->Close();
                        }

                }
                else    if(CmdFlag==2)//重启
                {
                        memset(SendCmd,0,sizeof(SendCmd));
                        sprintf(SendCmd,"%s","210101");
                        if(Disp)
                        {
                                this->Edit2->Text=IP;
                                this->Edit3->Text="重启机器";
                                this->Show();
                        }
                        SendBuff(clientfd,SendCmd,strlen(SendCmd));
                        n = RecvBuff(clientfd, &precv);
                        if(n == -1)
                        {
                                MonitorErr.WriteMsg("RemoteServ\t\t\t远程控制指令执行---重启失败！");
                        }
                        else    if(strncmp(precv, "1013", 4) == 0)
                        {
                                MonitorErr.WriteMsg("RemoteServ\t\t\t远程控制指令执行---重启成功！");
                        }
                        if(Disp)
                        {
                               this->Close();
                        }

                }
                else    if(CmdFlag==3)//暂停服务
                {

                        memset(SendCmd,0,sizeof(SendCmd));
                        sprintf(SendCmd,"%s","210102");
                        if(Disp)
                        {
                                this->Edit2->Text=IP;
                                this->Edit3->Text="暂停服务";
                                this->Show();
                        }
                        SendBuff(clientfd,SendCmd,strlen(SendCmd));
                        n = RecvBuff(clientfd, &precv);
                        if(n == -1)
                        {
                                MonitorErr.WriteMsg("RemoteServ\t\t\t远程控制指令执行---暂停服务失败！");
                        }
                        else    if(strncmp(precv, "1014", 4) == 0)
                        {
                                MonitorErr.WriteMsg("RemoteServ\t\t\t远程控制指令执行---暂停服务成功！");
                        }
                        if(Disp)
                        {
                               this->Close();
                        }
                }
                else    if(CmdFlag==4)//启动服务
                {
                        memset(SendCmd,0,sizeof(SendCmd));
                        sprintf(SendCmd,"%s","210103");
                        if(Disp)
                        {
                                this->Edit2->Text=IP;
                                this->Edit3->Text="启动服务";
                                this->Show();
                        }
                        SendBuff(clientfd,SendCmd,strlen(SendCmd));
                        n = RecvBuff(clientfd, &precv);
                        if(n == -1)
                        {
                                MonitorErr.WriteMsg("RemoteServ\t\t\t远程控制指令执行---启动服务失败！");
                        }
                        else    if(strncmp(precv, "1015", 4) == 0)
                        {
                                MonitorErr.WriteMsg("RemoteServ\t\t\t远程控制指令执行---启动服务成功！");
                        }
                        if(Disp)
                        {
                               this->Close();
                        }
                }
                else    if(CmdFlag==5)
                {
                        memset(SendCmd,0,sizeof(SendCmd));
                        sprintf(SendCmd,"%s%s","1028","DataFile");

                        SendBuff(clientfd,SendCmd,strlen(SendCmd));
                        n = RecvBuff(clientfd, &precv);
                        if(n == -1)
                        {
                                MonitorErr.WriteMsg("RemoteServ\t\t\t远程控制指令执行---下载数据文件失败！");
                        }
                        else
                        {
                                //if(strncmp(precv, "002900", 6) == 0)
                                if(strlen(precv)>0)
                                {
                                        int     i;
                                        char    StrLen[16];
                                        FILE    *fp;
                                        char    filename[256];
                                        int     nfileinfolen;
                                        int     Length;
                                        //nfileinfolen=strlen(precv+6);
                                        i = 0;
                                        memset(StrLen, 0x00, sizeof(StrLen));
                                        memset(filename, 0x00, sizeof(filename));
                                        memcpy(StrLen,precv,12);
                                        Length=StrToInt(StrLen);
                                        //GetValue(fileinfo, filename, &i);
                                        sprintf(filename,"%s","./Pddb.mdb");
                                        fp = fopen(filename, "wb");
                                        if (fp == NULL)
                                        {
                                                MonitorErr.WriteMsg("RemoteServ\t\t\t远程控制指令执行---下载文件---打开本地文件错误");
                                                return  false;
                                        }
                                        fwrite(precv+12, 1, Length, fp);
                                        fclose(fp);
                                        MonitorErr.WriteMsg("RemoteServ\t\t\t远程控制指令执行---下载文件---成功！");
                                }
                                else
                                {
                                        MonitorErr.WriteMsg("RemoteServ\t\t\t远程控制指令执行---下载文件---失败:"+(AnsiString)precv+6);
                                        if (precv)
                                        {
                                                free(precv);
                                        }
                                        CloseSocket(clientfd);
                                        return false;
                                }
                        }
                }
                else    if(CmdFlag==6)
                {
                        char    *psend;
                        int     l;
                        psend=NULL;

                        l = GetDBFileData(precv+4, &psend);//获取数据库文件
                        if (l > 0)
                        {
                                SendBuff(clientfd, psend, l);
                                free(psend);
                        }
                        n = RecvBuff(clientfd, &precv);
                        if(n == -1)
                        {
                                MonitorErr.WriteMsg("RemoteServ\t\t\t远程控制指令执行---上传数据文件失败！");
                                if (precv)
                                {
                                        free(precv);
                                }
                                CloseSocket(clientfd);
                                return false;
                        }
                        else
                        {
                                if(strncmp(precv, "003100", 6) == 0)
                                {
                                        MonitorErr.WriteMsg("RemoteServ\t\t\t远程控制指令执行---上传数据文件失败！");
                                }
                        }
                }
                else    if(CmdFlag==7)//下载配置文件
                {
                        memset(SendCmd,0,sizeof(SendCmd));
                        sprintf(SendCmd,"%s%s","1028","COFGFile");

                        SendBuff(clientfd,SendCmd,strlen(SendCmd));
                        n = RecvBuff(clientfd, &precv);
                        if(n == -1)
                        {
                                MonitorErr.WriteMsg("RemoteServ\t\t\t远程控制指令执行---下载数据文件失败！");
                        }
                        else
                        {
                                if(strlen(precv)>0)
                                {
                                        int     i;
                                        char    StrLen[16];
                                        FILE    *fp;
                                        char    filename[256];
                                        int     nfileinfolen;
                                        int     Length;
                                        //nfileinfolen=strlen(precv+6);
                                        i = 0;
                                        memset(StrLen, 0x00, sizeof(StrLen));
                                        memset(filename, 0x00, sizeof(filename));
                                        memcpy(StrLen,precv,12);
                                        Length=StrToInt(StrLen);
                                        //GetValue(fileinfo, filename, &i);
                                        sprintf(filename,"%s","./PDJServer.ini");
                                        fp = fopen(filename, "wb");
                                        if (fp == NULL)
                                        {
                                                MonitorErr.WriteMsg("RemoteServ\t\t\t远程控制指令执行---下载文件---打开本地文件错误");
                                                return  false;
                                        }
                                        fwrite(precv+12, 1, Length, fp);
                                        fclose(fp);
                                        MonitorErr.WriteMsg("RemoteServ\t\t\t远程控制指令执行---下载文件---成功！");
                                }
                                else
                                {
                                        MonitorErr.WriteMsg("RemoteServ\t\t\t远程控制指令执行---下载文件---失败:"+(AnsiString)precv+6);
                                        if (precv)
                                        {
                                                free(precv);
                                        }
                                        CloseSocket(clientfd);
                                        return false;
                                }
                        }
                }
                else    if(CmdFlag==8)//上传配置文件
                {
                        char    *psend;
                        int     l;
                        psend=NULL;

                        l = GetCfgFileData(precv+4, &psend);//获取数据库文件
                        if (l > 0)
                        {
                                SendBuff(clientfd, psend, l);
                                free(psend);
                        }
                        n = RecvBuff(clientfd, &precv);
                        if(n == -1)
                        {
                                MonitorErr.WriteMsg("RemoteServ\t\t\t远程控制指令执行---上传配置文件失败！");
                                if (precv)
                                {
                                        free(precv);
                                }
                                CloseSocket(clientfd);
                                return false;
                        }
                        else
                        {
                                if(strncmp(precv, "003300", 6) == 0)
                                {
                                        MonitorErr.WriteMsg("RemoteServ\t\t\t远程控制指令执行---上传配置文件失败！");
                                }
                        }
                }
                if (precv)
                {
                        free(precv);
                }
                CloseSocket(clientfd);
                return true;
        }
        else
        {
                MonitorErr.WriteMsg("\t\t\t远程控制指令执行---工作套接字创建失败!");
                return false;
        }
}

SOCKET __fastcall TForm13::GetWordSocket(AnsiString IP, AnsiString Port)
{
        //TODO: Add your source code here

}
void __fastcall TForm13::FormCreate(TObject *Sender)
{
        InitWS();        
}
//---------------------------------------------------------------------------

void __fastcall TForm13::Timer1Timer(TObject *Sender)
{
        CGauge1->Progress++;
        if(CGauge1->Progress==100)
                    CGauge1->Progress=1;
}
//---------------------------------------------------------------------------

void __fastcall TForm13::FormShow(TObject *Sender)
{
        CGauge1->Progress=1;
}
//---------------------------------------------------------------------------

