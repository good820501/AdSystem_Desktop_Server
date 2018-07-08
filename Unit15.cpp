//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit15.h"
#include "Libs.h"
#include "Debug.h"
#include "DataCtrl.h"
#include "SocketAccessThread.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm15 *Form15;
//---------------------------------------------------------------------------
__fastcall TForm15::TForm15(TComponent* Owner)
        : TForm(Owner)
{
        serverfd  = INVALID_SOCKET;
        PHead=NULL;
        TerminalCount=0;
        InitTerminalList();
}
//---------------------------------------------------------------------------
void __fastcall TForm15::Timer1Timer(TObject *Sender)
{
        Timer1->Enabled=false;
        StartSocketService();
        Timer1->Enabled=true;
}
//---------------------------------------------------------------------------


void __fastcall TForm15::StartSocketService()
{
        //TODO: Add your source code here
        int     n;
        long    l;
        char    *precv;
        char    *psend;
        char    tmp[1024];
        SOCKET  clientfd;
        TSocketAccessThread     *AccessProcessThread;
        AccessProcessThread=NULL;

        if(INVALID_SOCKET == serverfd)
        {
                serverfd = InitServer(GetCfgInt("Prime","ServerPort",3213));
                SetNoBlockMode(serverfd, true);
        }

        if(INVALID_SOCKET == serverfd)
        {
                MonitorErr.WriteMsg("SockServer\t\t\t建立远程服务失败");
                return;
        }

        clientfd = AcceptClient(serverfd);
        if(clientfd == INVALID_SOCKET)
        {
                return;
        }
        SetNoBlockMode(clientfd, true);
        if(AccessProcessThread==NULL)
        {
                AccessProcessThread=new TSocketAccessThread(false,clientfd,this);
                AccessProcessThread->FreeOnTerminate=true;
        }
}

void __fastcall TForm15::InitTerminalList()
{
        //TODO: Add your source code here
       AnsiString       StrSql;
       AnsiString       StrTemp;
       TerminalList     *PointTemp;
       int              MediaListID;
       PHead=new TerminalList();
       PNow=PHead;
       if(PHead!=NULL)
       {
               StrSql="select * from TermDevice,MediaList where TermDevice.TMediaIndex=MediaList.ID";
               DataModule1->InitAdoQuery(DataModule1->ADOQuery2,StrSql);
               DataModule1->ADOQuery2->Open();
               while(!DataModule1->ADOQuery2->Eof)
               {
                        PointTemp=new  TerminalList();
                        if(PointTemp!=NULL)
                        {
                                if(!DataModule1->ADOQuery2->FieldByName("TIP")->Value.IsNull())
                                        StrTemp=DataModule1->ADOQuery2->FieldByName("TIP")->Value;
                                StrTemp=StrTemp.Trim();
                                PointTemp->TerID=DataModule1->ADOQuery2->FieldByName("TermDevice.ID")->Value;
                                PointTemp->IP=StrTemp;

                                if(!DataModule1->ADOQuery2->FieldByName("MName")->Value.IsNull())
                                        StrTemp=DataModule1->ADOQuery2->FieldByName("MName")->Value;
                                StrTemp=StrTemp.Trim();
                                PointTemp->MediaName=StrTemp;
                                PointTemp->DispNums=0;
                                MediaListID=DataModule1->ADOQuery2->FieldByName("TMediaIndex")->Value;
                                PointTemp->MediaListID=MediaListID;
                                PointTemp->Login=false;
                                PointTemp->DLSuccess=true;
                                PointTemp->PNext=NULL;
                                PNow->PNext=PointTemp;
                                PNow=PointTemp;
                        }
                        DataModule1->ADOQuery2->Next();
               }
       }
}

void __fastcall TForm15::ClearTerminalList()
{
        //TODO: Add your source code here
        TerminalList    *TerminalTemp;
        if(PHead!=NULL)
        {
                TerminalTemp=PHead->PNext;
                while(TerminalTemp!=NULL)
                {
                        PNow=TerminalTemp->PNext;
                        delete   TerminalTemp;
                        TerminalTemp=NULL;
                        TerminalTemp=PNow;
                }
                delete  PHead;
                PHead=NULL;
        }
}
void __fastcall TForm15::FormClose(TObject *Sender, TCloseAction &Action)
{
        ClearTerminalList();
}
//---------------------------------------------------------------------------
void __fastcall TForm15::FormCreate(TObject *Sender)
{
        InitTerminalList();        
}
//---------------------------------------------------------------------------

