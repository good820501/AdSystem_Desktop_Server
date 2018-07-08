//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"

#include "Unit3.h"
#include "Unit10.h"
#include "Unit11.h"
#include "Unit13.h"
#include "Unit16.h"
#include "DataCtrl.h"
#include "Debug.h"
#include "io.h"
TreeNodeDat             NodeList[256];
ListViewNodeDatEx         ListNodeLink[64];
int         NodeCount;  //树节点的数目
int         ListNodeCount;//列表项的数目

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm12 *Form12;
TForm *FormTemp=NULL;
//---------------------------------------------------------------------------
__fastcall TForm12::TForm12(TComponent* Owner)
        : TForm(Owner)
{
        NodeCount=0;
        ListNodeCount=0;
}
//---------------------------------------------------------------------------
void __fastcall TForm12::E1Click(TObject *Sender)
{
        //Application->Terminate();
        int                     ID;
        AnsiString              StrSql;
        TListItem               *ItemTemp;
        ListViewNodeDatEx         *DaTemp;

        ItemTemp=ListView1->Selected;
        if(ItemTemp!=NULL)
        {
                DaTemp=(ListViewNodeDatEx*)ItemTemp->Data;
                DispGroupDevices(DaTemp->ID,ListView1);
        }
}
//---------------------------------------------------------------------------


//页面跳转
void __fastcall TForm12::TurnPage(AnsiString Text)
{
        //TODO: Add your source code here
        if(FormTemp)
        {
                FormTemp->Close();
        }
        FormTemp=NULL;
        if(Text=="基本信息")
                {

                }
        else
                {       /*
                        try
                        {
                                if(Form5==NULL)
                                        Form5=new TForm5(Application);
                                 FormTemp=Form5;
                        }
                        catch(Exception &exception)
                        {
                                delete Form5;
                                Form5=NULL;
                        }*/
                }

}
void __fastcall TForm12::TreeView1Change(TObject *Sender, TTreeNode *Node)
{
        //TurnPage(Node->Text);
        bool            SingleFlag;//判断机构信息是否为单层组织方式

}
//---------------------------------------------------------------------------


void __fastcall TForm12::S2Click(TObject *Sender)
{
        if(Form3!=NULL)
        {
                Form3->ShowModal();
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm12::T2Click(TObject *Sender)
{
        /*if(Form10!=NULL)
        {
                Form10->ShowModal();
        }*/
}
//---------------------------------------------------------------------------

void __fastcall TForm12::FormShow(TObject *Sender)
{
       InitSysTree();
       CurrentRoot=0;//定位在根目录
       LoadDeviceList("",ListView1);
}
//---------------------------------------------------------------------------


void __fastcall TForm12::InitSysTree()
{
        //TODO: Add your source code here
        TTreeNode       *ItemTemp;
        TTreeNode       *Root;
        bool            SingleFlag;//判断机构信息是否为单层组织方式



}

void __fastcall TForm12::LoadDeviceList(AnsiString       SqlTemp,TListView * ListView)
{
        //TODO: Add your source code here
        AnsiString      StrSql;
        AnsiString      StrTemp;
        int             ID;
        int             NodeType;       //节点标志：1：普通终端；2：终端分组
        TListItem       *ItemTemp;
        if(SqlTemp=="")
               {
                        StrSql="select * from TermDevice where TGroup=0";
                        ListNodeCount=0;
               }
        else
                StrSql=SqlTemp;
        if(CurrentRoot!=0)
        {
                DispGroupDevices(CurrentRoot,ListView);
                return;
        }
        DataModule1->InitAdoQuery(DataModule1->ADOQuery3,StrSql);
        DataModule1->ADOQuery3->Open();
        ListView->Items->Clear();
        ListView->Items->BeginUpdate();
        while(!DataModule1->ADOQuery3->Eof)
        {
               NodeType=DataModule1->ADOQuery3->FieldByName("TType")->Value;
               ListNodeLink[ListNodeCount].NodeType=NodeType;
               if(NodeType==1)//普通终端节点处理
               {
                        ID=DataModule1->ADOQuery3->FieldByName("ID")->Value;
                        if(!DataModule1->ADOQuery3->FieldByName("TName")->Value.IsNull())
                        StrTemp=DataModule1->ADOQuery3->FieldByName("TName")->Value;
                        StrTemp=StrTemp.Trim();
                        
                        ItemTemp=ListView->Items->Add();
                        ItemTemp->Caption=StrTemp;
                        ListNodeLink[ListNodeCount].Caption=StrTemp;
                        ListNodeLink[ListNodeCount].ID=ID;
                        if(!DataModule1->ADOQuery3->FieldByName("TIP")->Value.IsNull())
                                StrTemp=DataModule1->ADOQuery3->FieldByName("TIP")->Value;
                        StrTemp=StrTemp.Trim();
                        ListNodeLink[ListNodeCount].IP=StrTemp;
                        if(!DataModule1->ADOQuery3->FieldByName("TPort")->Value.IsNull())
                                StrTemp=DataModule1->ADOQuery3->FieldByName("TPort")->Value;
                        StrTemp=StrTemp.Trim();
                        ListNodeLink[ListNodeCount].Port=StrTemp;
                        if(!DataModule1->ADOQuery3->FieldByName("TDBTYpe")->Value.IsNull())
                                ListNodeLink[ListNodeCount].DBType=DataModule1->ADOQuery3->FieldByName("TDBTYpe")->Value;
                        if(!DataModule1->ADOQuery3->FieldByName("TUserName")->Value.IsNull())
                                StrTemp=DataModule1->ADOQuery3->FieldByName("TUserName")->Value;
                        StrTemp=StrTemp.Trim();
                        ListNodeLink[ListNodeCount].UserName=StrTemp;

                        if(!DataModule1->ADOQuery3->FieldByName("TPass")->Value.IsNull())
                                StrTemp=DataModule1->ADOQuery3->FieldByName("TPass")->Value;
                        StrTemp=StrTemp.Trim();
                        ListNodeLink[ListNodeCount].Password=StrTemp;

                        ItemTemp->Data=&ListNodeLink[ListNodeCount];
                        ItemTemp->ImageIndex=3;
                        ItemTemp->StateIndex=3;

               }
               else//分组处理
               {
                        ID=DataModule1->ADOQuery3->FieldByName("ID")->Value;
                        if(!DataModule1->ADOQuery3->FieldByName("TName")->Value.IsNull())
                        StrTemp=DataModule1->ADOQuery3->FieldByName("TName")->Value;
                        StrTemp=StrTemp.Trim();

                        ItemTemp=ListView->Items->Add();
                        ItemTemp->Caption=StrTemp;
                        ListNodeLink[ListNodeCount].Caption=StrTemp;
                        ListNodeLink[ListNodeCount].ID=ID;

                        if(!DataModule1->ADOQuery3->FieldByName("TMemo")->Value.IsNull())
                                StrTemp=DataModule1->ADOQuery3->FieldByName("TMemo")->Value;
                        StrTemp=StrTemp.Trim();
                        ListNodeLink[ListNodeCount].Password=StrTemp;

                        ItemTemp->Data=&ListNodeLink[ListNodeCount];
                        ItemTemp->ImageIndex=42;
                        ItemTemp->StateIndex=42;
               }

               
               ListNodeCount++;
               DataModule1->ADOQuery3->Next();
        }
        ListView->Items->EndUpdate();
}

void __fastcall TForm12::PopupMenu2Popup(TObject *Sender)
{
        TListItem                 *ItemTemp;
        ListViewNodeDatEx         *DaTemp;
        ItemTemp=ListView1->Selected;
        if(ItemTemp!=NULL)
        {
                DaTemp=(ListViewNodeDatEx*)ItemTemp->Data;
                if(DaTemp->NodeType==1)
                {
                        A3->Enabled=false;
                        F2->Enabled=false;
                        L1->Enabled=true;
                        C2->Enabled=true;
                        R3->Enabled=true;
                        O2->Enabled=true;
                        P1->Enabled=true;
                        S1->Enabled=true;
                        T1->Enabled=true;
                        G1->Enabled=false;
                        P2->Enabled=false;
                        E1->Enabled=false;
                }
                else    if(DaTemp->NodeType==2)
                {
                        A3->Enabled=false;
                        F2->Enabled=false;
                        L1->Enabled=true;
                        C2->Enabled=false;
                        R3->Enabled=false;
                        O2->Enabled=false;
                        P1->Enabled=false;
                        S1->Enabled=false;
                        T1->Enabled=false;
                        G1->Enabled=false;
                        P2->Enabled=true;
                        E1->Enabled=true;
                }
                else
                {       A3->Enabled=false;
                        F2->Enabled=false;
                        L1->Enabled=false;
                        C2->Enabled=false;
                        R3->Enabled=false;
                        O2->Enabled=false;
                        P1->Enabled=false;
                        S1->Enabled=false;
                        T1->Enabled=false;
                        G1->Enabled=false;
                        P2->Enabled=false;
                        E1->Enabled=false;

                }
        }
        else
        {
                A3->Enabled=true;
                F2->Enabled=true;
                L1->Enabled=false;
                C2->Enabled=false;
                R3->Enabled=false;
                P1->Enabled=false;
                S1->Enabled=false;
                T1->Enabled=false;
                O2->Enabled=false;
                P2->Enabled=false;
                E1->Enabled=false;
                if(CurrentRoot==0)
                   G1->Enabled=true;
                else
                   G1->Enabled=false;
                //D1->Enabled=false;
                //N1->Enabled=false;
                //B1->Enabled=false;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm12::A3Click(TObject *Sender)
{
        AnsiString      StrTemp;
        AnsiString      StrSql;
        int             NowCount;
        if(Form11!=NULL)
        {
                Form11->Edit1->Clear();
                Form11->Edit2->Clear();
                Form11->Edit3->Clear();
                Form11->ShowModal();
                if(Form11->StoreFlag)
                {
                  if(!IsNameRight(Form16->Edit1->Text))
                  {
                        StrSql="insert into TermDevice(TName,TIP,TPort,TDBTYpe,TUserName,TPass,TGroup,TType)Values('";
                        StrSql+=Form11->Edit1->Text.Trim();
                        StrSql+="','";
                        StrSql+=Form11->Edit2->Text.Trim();
                        StrSql+="','";
                        StrSql+=Form11->Edit3->Text.Trim();
                        StrSql+="', ";
                        if(1)
                        {
                                StrSql+="1,'";
                                StrSql+="0";
                                StrSql+="','";
                                StrSql+="0";
                                StrSql+="'";
                                StrSql+=",";
                                StrSql+=IntToStr(CurrentRoot);
                                StrSql+=",1";
                                StrSql+=")";
                        }
                        /*else
                        {
                                StrSql+="2,'";
                                StrSql+=Form11->Edit4->Text.Trim();
                                StrSql+="','";
                                StrSql+=Form11->Edit5->Text.Trim();
                                StrSql+="')";
                        }*/
                        DataModule1->InitAdoQuery(DataModule1->ADOQuery3,StrSql);
                        DataModule1->ADOQuery3->ExecSQL();
                        LoadDeviceList("",ListView1);
                  }
                  else
                  {
                        ShowMessage("系统中已存在同名终端，添加失败！");
                  }
                }
        }
}
//---------------------------------------------------------------------------

//获取设备数目：Flag：层级标志：0：根节点；n：n层节点
//OptionName:配置像名称
int __fastcall TForm12::GetItemCount(int Flag, AnsiString OptionName)
{
        //TODO: Add your source code here
        int     NumTemp;

}
void __fastcall TForm12::O2Click(TObject *Sender)
{
        int                     ID;
        AnsiString              StrSql;
        TListItem               *ItemTemp;
        ListViewNodeDatEx         *DaTemp;

        ItemTemp=ListView1->Selected;
        if(ItemTemp!=NULL)
        {

              DaTemp=(ListViewNodeDatEx*)ItemTemp->Data;
              Form11->Edit1->Text=DaTemp->Caption;
              Form11->Edit2->Text=DaTemp->IP;
              Form11->Edit3->Text=DaTemp->Port;


              //Form11->Edit4->Text=DaTemp->UserName;
              //Form11->Edit5->Text=DaTemp->Password;
              Form11->ShowModal();
              if(Form11->StoreFlag)
              {
                        StrSql="update TermDevice set TName='";
                        StrSql+=Form11->Edit1->Text.Trim();
                        StrSql+="',TIP='";
                        StrSql+=Form11->Edit2->Text.Trim();
                        StrSql+="',TPort='";
                        StrSql+=Form11->Edit3->Text.Trim();
                        StrSql+="',TDBTYpe=";
                        if(1)
                        {
                                StrSql+="1,TUserName='";
                                StrSql+="0";
                                StrSql+="',TPass='";
                                StrSql+="0";
                                StrSql+="'";
                        }

                        StrSql+=" where ID="+IntToStr(DaTemp->ID);
                        DataModule1->InitAdoQuery(DataModule1->ADOQuery3,StrSql);
                        DataModule1->ADOQuery3->ExecSQL();
                        LoadDeviceList("",ListView1);
              }
        }

}
//---------------------------------------------------------------------------

void __fastcall TForm12::F2Click(TObject *Sender)
{
        LoadDeviceList("",ListView1);
}
void __fastcall TForm12::DeleteDevInfo(int DevID)
{
        //TODO: Add your source code here
        AnsiString      StrSql;
        StrSql="delete from TermDevice where ID="+IntToStr(DevID);
        DataModule1->InitAdoQuery(DataModule1->ADOQuery3,StrSql);
        DataModule1->ADOQuery3->ExecSQL();
}
//---------------------------------------------------------------------------

void __fastcall TForm12::L1Click(TObject *Sender)
{
        TListItem               *ItemTemp;
        ListViewNodeDatEx         *DaTemp;
        int                     NodeCount;
        int                     TotalCount;
        ItemTemp=ListView1->Selected;
        NodeCount=ListView1->SelCount;
        //DaTemp
        if(NodeCount==1)
        {
                if(ItemTemp!=NULL)
                {
                        DaTemp=(ListViewNodeDatEx*)ItemTemp->Data;
                        if(DaTemp->NodeType==1)
                        {
                                if(MessageBox(Handle,"删除该设备信息，确定吗？","多媒体展示平台",MB_OKCANCEL)==1)
                                {
                                        DeleteDevInfo(DaTemp->ID);
                                        F2Click(Sender);
                                }
                        }
                        else    if(DaTemp->NodeType==2)
                        {
                                 if(MessageBox(Handle,"删除该分组以及该分组所属的所有设备信息，确定吗？","多媒体展示平台",MB_OKCANCEL)==1)
                                {
                                        DeleteGroup(DaTemp->ID);
                                        F2Click(Sender);
                                }
                        }
                }
        }
        else    if(NodeCount>1)
        {
                if(MessageBox(Handle,"删除选定的设备信息，确定吗？","删除确认",MB_OKCANCEL)==1)
                {
                        TotalCount=ListView1->Items->Count;
                        for(int i=0;i<NodeCount;i++)
                        {
                                for(int j=0;j<TotalCount;j++)
                                {
                                        if(ListView1->Items->Item[j]->Selected)
                                        {
                                                ItemTemp=ListView1->Items->Item[j];
                                                ItemTemp->Selected=false;
                                                break;
                                        }
                                }
                                DaTemp=(ListViewNodeDatEx *)ItemTemp->Data;
                                //ID=DaTemp->ID;
                                if(DaTemp->NodeType==1)
                                        DeleteDevInfo(DaTemp->ID);
                                else    if(DaTemp->NodeType==2)
                                        DeleteGroup(DaTemp->ID);
                        }
                        F2Click(Sender);
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm12::C2Click(TObject *Sender)
{
        //远程关机
        TListItem               *ItemTemp;
        ListViewNodeDatEx         *DaTemp;
        int                     NodeCount;
        int                     TotalCount;

        ItemTemp=ListView1->Selected;
        NodeCount=ListView1->SelCount;
        if(NodeCount==1)
        {
                if(ItemTemp!=NULL)
                {

                        DaTemp=(ListViewNodeDatEx*)ItemTemp->Data;
                        if(Form13!=NULL)
                        {
                                Form13->SendCtrlCmd(DaTemp->IP,DaTemp->Port,1,true);
                        }
                }
        }
        else    if(NodeCount>1)
        {
                TotalCount=ListView1->Items->Count;
                for(int i=0;i<NodeCount;i++)
                {
                        for(int j=0;j<TotalCount;j++)
                        {
                                if(ListView1->Items->Item[j]->Selected)
                                {
                                        ItemTemp=ListView1->Items->Item[j];
                                        ItemTemp->Selected=false;
                                        break;
                                }
                        }
                        DaTemp=(ListViewNodeDatEx*)ItemTemp->Data;
                        if(Form13!=NULL)
                        {
                                Form13->SendCtrlCmd(DaTemp->IP,DaTemp->Port,1,true);
                        }
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm12::R3Click(TObject *Sender)
{
        //远程重启
        TListItem               *ItemTemp;
        ListViewNodeDatEx         *DaTemp;
        int                     NodeCount;
        int                     TotalCount;
        
        ItemTemp=ListView1->Selected;
        NodeCount=ListView1->SelCount;
        if(NodeCount==1)
        {
                if(ItemTemp!=NULL)
                {

                        DaTemp=(ListViewNodeDatEx*)ItemTemp->Data;
                        if(Form13!=NULL)
                        {
                                Form13->SendCtrlCmd(DaTemp->IP,DaTemp->Port,2,true);
                        }
                }
        }
        else    if(NodeCount>1)
        {
                TotalCount=ListView1->Items->Count;
                for(int i=0;i<NodeCount;i++)
                {
                        for(int j=0;j<TotalCount;j++)
                        {
                                if(ListView1->Items->Item[j]->Selected)
                                {
                                        ItemTemp=ListView1->Items->Item[j];
                                        ItemTemp->Selected=false;
                                        break;
                                }
                        }
                        DaTemp=(ListViewNodeDatEx*)ItemTemp->Data;
                        if(Form13!=NULL)
                        {
                                Form13->SendCtrlCmd(DaTemp->IP,DaTemp->Port,2,true);
                        }
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm12::B1Click(TObject *Sender)
{
        //基本信息-远程管理
        TListItem               *ItemTemp;
        ListViewNodeDatEx         *DaTemp;
        AnsiString              LinkStr;
        AnsiString              FullDBName;


        
}
//---------------------------------------------------------------------------

void __fastcall TForm12::N1Click(TObject *Sender)
{
        //控制参数-远程管理
        TListItem               *ItemTemp;
        ListViewNodeDatEx         *DaTemp;
        AnsiString              LinkStr;
        AnsiString              FullDBName;

        ItemTemp=ListView1->Selected;
        if(ItemTemp!=NULL)
        {
              FullDBName=ExtractFilePath(Application->ExeName);
              FullDBName+="\\PDJServer.ini";
              DaTemp=(ListViewNodeDatEx*)ItemTemp->Data;
              if(Form13->SendCtrlCmd(DaTemp->IP,DaTemp->Port,7,true))
              {
                        if(Form12!=NULL)
                                Form12->ShowModal();
                        if(Form13->SendCtrlCmd(DaTemp->IP,DaTemp->Port,8,true))
                        {
                                if(_access(FullDBName.c_str(),0)==0)
                                        DeleteFile(FullDBName);
                        }
                        else
                        {
                                MessageBox(Handle,"更新远程配置文件失败，请重新更新！","控制参数设置",MB_OK);
                                return;
                        }
              }
              else
              {
                        MessageBox(Handle,"下载前台数据文件失败！","远程控制参数设置",MB_OK);
                        MonitorErr.WriteMsg("\t\t\t远程控制参数设置---下载配置文件失败");
              }
        }
}
//---------------------------------------------------------------------------


void __fastcall TForm12::P1Click(TObject *Sender)
{
        //向客户端发送暂停服务指令
        TListItem               *ItemTemp;
        ListViewNodeDatEx       *DaTemp;
        int                     NodeCount;
        int                     TotalCount;


        ItemTemp=ListView1->Selected;
        NodeCount=ListView1->SelCount;
        if(NodeCount==1)
        {
                if(ItemTemp!=NULL)
                {

                        DaTemp=(ListViewNodeDatEx*)ItemTemp->Data;
                        if(Form13!=NULL)
                        {
                                Form13->SendCtrlCmd(DaTemp->IP,DaTemp->Port,3,true);
                        }
                }
        }
        else   if(NodeCount>1)
        {
                TotalCount=ListView1->Items->Count;
                for(int i=0;i<NodeCount;i++)
                {
                        for(int j=0;j<TotalCount;j++)
                        {
                                if(ListView1->Items->Item[j]->Selected)
                                {
                                        ItemTemp=ListView1->Items->Item[j];
                                        ItemTemp->Selected=false;
                                        break;
                                }
                        }
                        DaTemp=(ListViewNodeDatEx*)ItemTemp->Data;
                        if(Form13!=NULL)
                        {
                                Form13->SendCtrlCmd(DaTemp->IP,DaTemp->Port,3,true);
                        }
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm12::S1Click(TObject *Sender)
{
        TListItem               *ItemTemp;
        ListViewNodeDatEx       *DaTemp;
        int                     NodeCount;
        int                     TotalCount;


        ItemTemp=ListView1->Selected;
        NodeCount=ListView1->SelCount;
        if(NodeCount==1)
        {
                if(ItemTemp!=NULL)
                {
                        DaTemp=(ListViewNodeDatEx*)ItemTemp->Data;
                        if(Form13!=NULL)
                        {
                                Form13->SendCtrlCmd(DaTemp->IP,DaTemp->Port,4,true);
                        }
                }
        }
        else    if(NodeCount>1)
        {
                TotalCount=ListView1->Items->Count;
                for(int i=0;i<NodeCount;i++)
                {
                        for(int j=0;j<TotalCount;j++)
                        {
                                if(ListView1->Items->Item[j]->Selected)
                                {
                                        ItemTemp=ListView1->Items->Item[j];
                                        ItemTemp->Selected=false;
                                        break;
                                }
                        }
                        DaTemp=(ListViewNodeDatEx*)ItemTemp->Data;
                        if(Form13!=NULL)
                        {
                                Form13->SendCtrlCmd(DaTemp->IP,DaTemp->Port,4,true);
                        }
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm12::G1Click(TObject *Sender)
{
        AnsiString    StrSql;
        if(Form16!=NULL)
        {
                Form16->Edit1->Clear();
                Form16->Memo1->Clear();
                Form16->ShowModal();
                if(Form16->StoreFlag)
                {
                        if(!IsNameRight(Form16->Edit1->Text))
                        {
                                StrSql="insert into TermDevice(TName,TGroup,TType,TMemo)Values('";
                                StrSql+=Form16->Edit1->Text.Trim();
                                StrSql+="',0,2,'";
                                StrSql+=Form16->Memo1->Text;
                                StrSql+="')";
                                DataModule1->InitAdoQuery(DataModule1->ADOQuery3,StrSql);
                                DataModule1->ADOQuery3->ExecSQL();
                                LoadDeviceList("",ListView1);
                        }
                        else
                        {
                                ShowMessage("系统中已存在同名分组，添加失败");
                        }
                }
        }
}
//---------------------------------------------------------------------------

//判断分组或者设备名称是否在系统中存在重名
BOOL __fastcall TForm12::IsNameRight(AnsiString Name,int ID)
{
        //TODO: Add your source code here
        AnsiString      StrSql;
        BOOL             Ret;
        if(ID==0)
                StrSql="select ID from TermDevice where TName='"+Name+"'";
        else
                StrSql="select ID from TermDevice where TName='"+Name+"' and ID<>"+IntToStr(ID);
        DataModule1->InitAdoQuery(DataModule1->ADOQuery1,StrSql);
        DataModule1->ADOQuery1->Open();
        if(DataModule1->ADOQuery1->RecordCount>0)
        {
                Ret=true;
        }
        else
                Ret=false;
        DataModule1->ADOQuery1->Close();
        return  Ret;

}
void __fastcall TForm12::ListView1DblClick(TObject *Sender)
{
        //
        int                     ID;
        AnsiString              StrSql;
        TListItem               *ItemTemp;
        ListViewNodeDatEx         *DaTemp;

        ItemTemp=ListView1->Selected;
        if(ItemTemp!=NULL)
        {
                DaTemp=(ListViewNodeDatEx*)ItemTemp->Data;
                if(DaTemp->NodeType==1)
                {
                        O2Click(Sender);
                }
                else    if(DaTemp->NodeType==2)
                {
                        DispGroupDevices(DaTemp->ID,ListView1);
                }
                else
                {
                        CurrentRoot=0;
                        F2Click(Sender);
                }
        }
}
//---------------------------------------------------------------------------

//显示分组内的终端
void __fastcall TForm12::DispGroupDevices(int GroupIndex, TListView * ListView)
{
        //TODO: Add your source code here
        AnsiString      StrSql;
        AnsiString      StrTemp;
        int             ID;
        int             NodeType;       //节点标志：1：普通终端；2：终端分组
        TListItem       *ItemTemp;

         StrSql="select * from TermDevice where TGroup="+IntToStr(GroupIndex);
         ListNodeCount=0;

        CurrentRoot=GroupIndex;
        DataModule1->InitAdoQuery(DataModule1->ADOQuery3,StrSql);
        DataModule1->ADOQuery3->Open();
        ListView->Items->Clear();
        ListView->Items->BeginUpdate();
        AddUpHandle(ListView);
        while(!DataModule1->ADOQuery3->Eof)
        {
               NodeType=DataModule1->ADOQuery3->FieldByName("TType")->Value;
               ListNodeLink[ListNodeCount].NodeType=NodeType;
               if(NodeType==1)//普通终端节点处理
               {
                        ID=DataModule1->ADOQuery3->FieldByName("ID")->Value;
                        if(!DataModule1->ADOQuery3->FieldByName("TName")->Value.IsNull())
                        StrTemp=DataModule1->ADOQuery3->FieldByName("TName")->Value;
                        StrTemp=StrTemp.Trim();
                        
                        ItemTemp=ListView->Items->Add();
                        ItemTemp->Caption=StrTemp;
                        ListNodeLink[ListNodeCount].Caption=StrTemp;
                        ListNodeLink[ListNodeCount].ID=ID;
                        if(!DataModule1->ADOQuery3->FieldByName("TIP")->Value.IsNull())
                                StrTemp=DataModule1->ADOQuery3->FieldByName("TIP")->Value;
                        StrTemp=StrTemp.Trim();
                        ListNodeLink[ListNodeCount].IP=StrTemp;
                        if(!DataModule1->ADOQuery3->FieldByName("TPort")->Value.IsNull())
                                StrTemp=DataModule1->ADOQuery3->FieldByName("TPort")->Value;
                        StrTemp=StrTemp.Trim();
                        ListNodeLink[ListNodeCount].Port=StrTemp;
                        if(!DataModule1->ADOQuery3->FieldByName("TDBTYpe")->Value.IsNull())
                                ListNodeLink[ListNodeCount].DBType=DataModule1->ADOQuery3->FieldByName("TDBTYpe")->Value;
                        if(!DataModule1->ADOQuery3->FieldByName("TUserName")->Value.IsNull())
                                StrTemp=DataModule1->ADOQuery3->FieldByName("TUserName")->Value;
                        StrTemp=StrTemp.Trim();
                        ListNodeLink[ListNodeCount].UserName=StrTemp;

                        if(!DataModule1->ADOQuery3->FieldByName("TPass")->Value.IsNull())
                                StrTemp=DataModule1->ADOQuery3->FieldByName("TPass")->Value;
                        StrTemp=StrTemp.Trim();
                        ListNodeLink[ListNodeCount].Password=StrTemp;

                        ItemTemp->Data=&ListNodeLink[ListNodeCount];
                        ItemTemp->ImageIndex=3;
                        ItemTemp->StateIndex=3;

               }
               ListNodeCount++;
               DataModule1->ADOQuery3->Next();
        }
        ListView->Items->EndUpdate();
}

void __fastcall TForm12::AddUpHandle(TListView * ListView)
{
        AnsiString      StrSql;
        AnsiString      StrTemp;
        int             ID;
        int             NodeType;       //节点标志：1：普通终端；2：终端分组
        TListItem       *ItemTemp;
        ItemTemp=ListView->Items->Add();
        ItemTemp->Caption="返回";
        ListNodeLink[ListNodeCount].Caption=StrTemp;
        ListNodeLink[ListNodeCount].NodeType=3;
        ItemTemp->Data=&ListNodeLink[ListNodeCount];
        ItemTemp->ImageIndex=43;
        ItemTemp->StateIndex=43;
        //ItemTemp->
        ListNodeCount++;
}
void __fastcall TForm12::P2Click(TObject *Sender)
{
        //
        int                     ID;
        AnsiString              StrSql;
        TListItem               *ItemTemp;
        ListViewNodeDatEx         *DaTemp;

        ItemTemp=ListView1->Selected;
        if(ItemTemp!=NULL)
        {
                DaTemp=(ListViewNodeDatEx*)ItemTemp->Data;
                ID=DaTemp->ID;
                if(Form16!=NULL)
                {
                        Form16->Edit1->Text=DaTemp->Caption;
                        Form16->Memo1->Text=DaTemp->Password;
                        Form16->ShowModal();
                        if(Form16->StoreFlag)
                        {
                                if(!IsNameRight(Form16->Edit1->Text,ID))
                                {

                                        StrSql="Update TermDevice set TName='"+Form16->Edit1->Text;
                                        StrSql+="',TMemo='"+Form16->Memo1->Text;
                                        StrSql+="' where ID="+IntToStr(ID);
                                        DataModule1->InitAdoQuery(DataModule1->ADOQuery3,StrSql);
                                        DataModule1->ADOQuery3->ExecSQL();
                                        F2Click(Sender);
                                }
                                else
                                {
                                        ShowMessage("系统中存在同名的组，修改分组信息失败！");
                                }
                                
                        }
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm12::ListView1DragDrop(TObject *Sender,
      TObject *Source, int X, int Y)
{
        //
        TListItem       *ItemTemp;
        TListItem       *ItemSource;
        ListViewNodeDatEx         *DaTemp;
        ListViewNodeDatEx         *DaTempSec;
        ItemTemp=ListView1->GetItemAt(X,Y);
        ItemSource=ListView1->Selected;
        if((ItemTemp!=NULL)&&(ItemSource!=NULL))
        {
                DaTemp=(ListViewNodeDatEx*)ItemTemp->Data;
                DaTempSec=(ListViewNodeDatEx*)ItemSource->Data;
                if((DaTempSec->NodeType==1)&&(DaTemp->NodeType==2))
                {
                        ChangeDeviceGroup(DaTempSec->ID,DaTemp->ID);
                        F2Click(Sender);
                }
                else    if((DaTempSec->NodeType==1)&&(DaTemp->NodeType==3))
                {
                        ChangeDeviceGroup(DaTempSec->ID,0);
                        F2Click(Sender);
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm12::ListView1DragOver(TObject *Sender,
      TObject *Source, int X, int Y, TDragState State, bool &Accept)
{
        //
}
//---------------------------------------------------------------------------


void __fastcall TForm12::ChangeDeviceGroup(int DeviceID, int GroupID)
{
        //TODO: Add your source code here
        AnsiString      StrSql;
        StrSql="update TermDevice set TGroup="+IntToStr(GroupID);
        StrSql+=" where ID="+IntToStr(DeviceID);
        DataModule1->InitAdoQuery(DataModule1->ADOQuery3,StrSql);
        DataModule1->ADOQuery3->ExecSQL();
}
//删除分组及分组下的所有设备信息
void __fastcall TForm12::DeleteGroup(int GroupIndex)
{
        //TODO: Add your source code here
        AnsiString      StrSql;
        StrSql="delete from TermDevice where TGroup="+IntToStr(GroupIndex);
        DataModule1->InitAdoQuery(DataModule1->ADOQuery3,StrSql);
        DataModule1->ADOQuery3->ExecSQL();
        StrSql="delete from TermDevice where ID="+IntToStr(GroupIndex);
        DataModule1->InitAdoQuery(DataModule1->ADOQuery3,StrSql);
        DataModule1->ADOQuery3->ExecSQL();
}
