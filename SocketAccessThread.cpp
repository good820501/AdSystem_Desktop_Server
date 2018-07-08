//---------------------------------------------------------------------------


#pragma hdrstop

#include "SocketAccessThread.h"
//#include "SockFunc.h"
#include "Debug.h"
#include "Libs.h"
#include "io.h"

void   read_line(char   line[],FILE   *fp);
void   SendFileInfo(SOCKET clientfd,char *FileName,char *Path);
void   SendDirectory(SOCKET clientfd,char *FileName,char *Path);
int    GetFileType(char *FileName);
AnsiString      GetShortPath(char *FullPath);
//---------------------------------------------------------------------------
#define Max_Terminals 10
#pragma package(smart_init)
__fastcall TSocketAccessThread::TSocketAccessThread(bool CreateSuspended,SOCKET ClientSock,TForm15 *FrmTemp)
        : TThread(CreateSuspended)
{
        ClientSocket=ClientSock;
        FrmPrc=FrmTemp;
        CmeTerminal.ClientSocket=ClientSocket;
        CmeTerminal.FrmPrc=FrmPrc;
}
//---------------------------------------------------------------------------
void __fastcall TSocketAccessThread::Execute()
{
        //---- Place thread code here ----
        TradeEatCard((LPVOID)&CmeTerminal);
}
TSocketAccessThread *pEatCard;

DWORD WINAPI TradeEatCard(LPVOID lpParam)
{
        char            *precv;
        int             n;
        int             ReceiveLength;
        void*           Buf;
        AnsiString      IPAddress;
        AnsiString      WorkDir;
        AnsiString      FileName;
        AnsiString      CfgFilePath;
        SYSTEMTIME	systime;
        CmdExecute      *Execute;
        TForm15         *FrmWork;
        BOOL            FindFlag=false;//是否找到客户端
        TerminalList    *TermTemp;
        TerminalList    *TermSec;
	memset(&systime, 0x00, sizeof(systime));
	GetLocalTime(&systime);

        Execute=(CmdExecute*)lpParam;
        
        SOCKADDR_IN sockAddr;
        memset(&sockAddr, 0, sizeof(sockAddr));
        int nSockAddrLen = sizeof(sockAddr);

        SOCKET  clientfd=Execute->ClientSocket;
        FrmWork=Execute->FrmPrc;
        n = RecvBuff(clientfd, &precv);

        if(n == -1)
        {
                MonitorErr.WriteMsg("RemoteServ\t\t\t远程控制指令执行---接收数据失败！");
        }
        else
        {
                if(strlen(precv)>0)
                {
                        int     i;
                        char    StrLen[16];
                        FILE    *fp;
                        char    *psend;
                        long    l;
                        char    filename[256];
                        char    ReadLine[256];
                        char    CmdStr[32];
                        int     nfileinfolen;
                        int     Length;
                        i = 0;


                        memset(CmdStr, 0x00, sizeof(CmdStr));
                        memset(StrLen, 0x00, sizeof(StrLen));
                        memset(filename, 0x00, sizeof(filename));
                        memcpy(StrLen,precv,12);
                        Length=StrToInt(StrLen);
                        
                        if(SOCKET_ERROR !=getpeername(clientfd,(SOCKADDR*)&sockAddr, &nSockAddrLen))
                        {
                                IPAddress=inet_ntoa(sockAddr.sin_addr);
                        }
                        IPAddress=IPAddress.Trim();
                        if(strncmp(precv,"110100",6)==0)//下载文件请求
                        {
                                TermTemp=FrmWork->PHead->PNext;
                                while(TermTemp!=NULL)
                                {
                                        if(TermTemp->IP==IPAddress)
                                        {
                                                FindFlag=true;
                                                break;
                                        }
                                        TermTemp=TermTemp->PNext;
                                }
                                if(FindFlag)//找到对应客户端
                                {
                                        if(FrmWork->TerminalCount<Max_Terminals)
                                        {
                                                WorkDir=GetCurrentDir();
                                                WorkDir+="\\MediaList\\";
                                                WorkDir+=TermTemp->MediaName;
                                                WorkDir+="\\DownLoad.lis";

                                                fp=fopen(WorkDir.c_str(),"r");
                                                if(fp!=NULL)
                                                {
                                                        while(!feof(fp))
                                                        {
                                                                memset(ReadLine, 0x00, sizeof(ReadLine));
                                                                read_line(ReadLine,fp);
                                                                if(strlen(ReadLine)>0)
                                                                {
                                                                        if(GetFileType(ReadLine)==2)//若为普通文件
                                                                                SendFileInfo(clientfd,ReadLine,"");
                                                                        else
                                                                                SendDirectory(clientfd,"",ReadLine);
                                                                }
                                                        }
                                                        fclose(fp);
                                                        memset(CmdStr,0x00,sizeof(CmdStr));
                                                        sprintf(CmdStr,"%s","110500");
                                                        SendBuff(clientfd,CmdStr,strlen(CmdStr));
                                                        TermTemp->DLSuccess=true;
                                                }
                                        }
                                        else
                                        { //超过连接最大数量，进行分流
                                                FindFlag=false;
                                                TermSec=FrmWork->PHead->PNext;
                                                while(TermSec!=NULL)
                                                {
                                                        if((TermSec->MediaListID==TermTemp->MediaListID)&&(TermSec->DLSuccess)&&(TermSec->TerID<Max_Terminals))
                                                        {
                                                                FindFlag=true;
                                                                break;
                                                        }
                                                        TermSec=TermSec->PNext;
                                                }
                                                if(FindFlag)//找到可以分流的客户端
                                                {
                                                        memset(CmdStr,0x00,sizeof(CmdStr));
                                                        sprintf(CmdStr,"%s%s","110203",TermSec->IP);
                                                        SendBuff(clientfd,CmdStr,strlen(CmdStr));
                                                }
                                                else//发送延时命令
                                                {
                                                        SendBuff(clientfd,"110202",6);
                                                }
                                        }
                                }
                                else
                                {
                                        SendBuff(clientfd,"110201",6);// 回送错误消息，该客户端IP地址未在服务器注册
                                }
                        }
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
        if (precv)
        {
                free(precv);
        }
        CloseSocket(clientfd);
        return 0;
}
void   SendFileInfo(SOCKET clientfd,char *FileName,char *Path)
{
        int     i;
        char    StrLen[16];
        FILE    *fp;
        char    *psend,*precv;
        long    l,n;
        char    filename[256];
        char    ReadLine[256];
        char    CmdStr[32];
        int     nfileinfolen;
        int     Length;
        i = 0;

        memset(filename,0x00,sizeof(filename));
        memset(ReadLine,0x00,sizeof(ReadLine));
        memset(CmdStr,0x00,sizeof(CmdStr));
        sprintf(ReadLine,"%s",FileName);

        l =GetFileData(ReadLine,&psend);
        if (l > 0)
        {
                memset(filename,0x00,sizeof(filename));
                if(strlen(Path)<=0)
                {
                         sprintf(filename,"%s%s","110301",ExtractFileName(ReadLine));
                }
                else
                         sprintf(filename,"%s%s\\%s","110302",Path,ExtractFileName(ReadLine));
                SendBuff(clientfd,filename,strlen(filename));
                n = RecvBuff(clientfd, &precv);
                if(n>0)
                {
                        if(strncmp(precv,"110300",6)==0)
                        {
                                memcpy(psend,"110400",6);
                                SendBuff(clientfd, psend, l);
                                free(psend);
                                MonitorErr.WriteMsg("\t\t\t数据文件传输---传输完成!");
                        }
                }
                
        }
}
void   SendDirectory(SOCKET clientfd,char *FileName,char *Path)
{
        TSearchRec sr;
        int iAttributes = 0;
        DWORD ResultAttr;
        AnsiString FoundFileName;

        iAttributes = faAnyFile;
        if(_access(Path,0)!=0)
                return;
        try
        {
        	if (FindFirst(AnsiString(Path)+"\\"+ "*.*", iAttributes, sr) == 0)
	        {
		        do //开始查找文件
		        {
			        FoundFileName = AnsiString(Path)+"\\"+ sr.Name; //生成找到的文件路径
			        ResultAttr = GetFileAttributes(LPCTSTR(FoundFileName.c_str())); //返回文件属性

			        //目录
			        if (ResultAttr == FILE_ATTRIBUTE_DIRECTORY)  //找到的文件是目录类型
			        {
				        if (sr.Name.Pos(".") == 0) //过滤掉创建目录是的默认子目录 "." 和 ".."
				        {
					        SendDirectory(clientfd,"",(AnsiString(Path) + sr.Name + "\\").c_str());
				        }
			        }

			        //文件
			        if(ResultAttr != FILE_ATTRIBUTE_DIRECTORY)
			        {
                                        SendFileInfo(clientfd,FoundFileName.c_str(),GetShortPath(Path).c_str());
				}
			}
                        while (FindNext(sr) == 0);
		}
		FindClose(sr); //关闭
	} 
        catch(...)
        {
	       // MessageBox(this->Handle, "读取文件夹失败！", "错误", MB_OKMB_ICONERROR);
	        return ;
        }
}
AnsiString      GetShortPath(char *FullPath)
{
        char            StrTemp[256];
        AnsiString      PathReturn;
        BOOL            Flag=false;
        
        memset(StrTemp,0x00,sizeof(StrTemp));
        if(FullPath!=NULL)
        {
                sprintf(StrTemp,"%s",FullPath);
                for(int i=0;i<strlen(StrTemp);i++)
                {
                        if((StrTemp[i]=='\\')&&(i!=strlen(StrTemp)-1))
                        {
                                PathReturn="";
                        }
                        else
                                PathReturn+=StrTemp[i];
                }
                return  PathReturn;
        }
        return "";
}
void   read_line(char   line[],FILE   *fp)
  {

        char   cn;
        int   i;
        i=0;
        if(fp!=NULL)
        {
                cn=fgetc(fp);
                while((cn!='\n')&&(!feof(fp)))
                {
                        line[i]=cn;
                        i++;
                        cn=fgetc(fp);
                }
                line[i]='\0';
        }
        return;
}
//判断FileName为目录或文件名：1：目录；2：文件名
int    GetFileType(char *FileName)
{
        int iAttributes = 0;
        DWORD ResultAttr;

        ResultAttr=GetFileAttributes(FileName);
        if(ResultAttr == FILE_ATTRIBUTE_DIRECTORY)
                return 1;
        return 2;
}