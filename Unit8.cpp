//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit8.h"
#include "Unit6.h"
#include "Unit10.h"
#include "Unit14.h"

#include "DataCtrl.h"
#include "Main.h"
ListViewNodeDatEx         ListNodeLink[64];
int                       ListCount;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm8 *Form8;
//---------------------------------------------------------------------------
__fastcall TForm8::TForm8(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm8::Button1Click(TObject *Sender)
{
        if(Form6!=NULL)
        {
                Form6->Edit1->Clear();
                Form6->ListView2->Clear();
                Form6->RadioButton1->Checked=true;
                Form6->Edit4->Text="";
                Form6->ComboBox1->Text="";
                Form6->ShowType=1;
                Form6->ListNodeCount=0;
                Form6->ShowModal();
                if(Form6->StoreFlag)
                         LoadMListFull();
        }
}
//---------------------------------------------------------------------------
//加载媒体列表
void __fastcall TForm8::LoadMListFull()
{
        //TODO: Add your source code here
        AnsiString      StrSql;
        AnsiString      StrTemp;
        TListItem       *ItemTemp;
        TDateTime       DTTemp;
        int             ID;
        int             Index=0;

        ListCount=0;
        StrSql="select * from MediaList";
        DataModule1->InitAdoQuery(DataModule1->ADOQuery1,StrSql);
        DataModule1->ADOQuery1->Open();
        ListView1->Items->Clear();
        if(DataModule1->ADOQuery1->RecordCount>0)
        {
                ListView1->Items->BeginUpdate();
                while(!DataModule1->ADOQuery1->Eof)
                {
                       Index++;
                       ID=DataModule1->ADOQuery1->FieldByName("ID")->Value;
                       if(!DataModule1->ADOQuery1->FieldByName("MName")->Value.IsNull())
                                StrTemp=DataModule1->ADOQuery1->FieldByName("MName")->Value;
                       StrTemp=StrTemp.Trim();
                       ItemTemp=ListView1->Items->Add();
                       ItemTemp->Caption=IntToStr(Index);
                       ItemTemp->SubItems->Add(StrTemp);
                       ListNodeLink[ListCount].ID=ID;
                       StrTemp="";
                      
                       if(!DataModule1->ADOQuery1->FieldByName("Begin_Time")->Value.IsNull())
                       {
                                DTTemp=(TDateTime)DataModule1->ADOQuery1->FieldByName("Begin_Time")->Value;
                                StrTemp=DTTemp.DateTimeString();
                       }
                       ItemTemp->SubItems->Add(StrTemp);

                       StrTemp="";
                       if(!DataModule1->ADOQuery1->FieldByName("End_Time")->Value.IsNull())
                       {
                                DTTemp=(TDateTime)DataModule1->ADOQuery1->FieldByName("End_Time")->Value;
                                StrTemp=DTTemp.DateTimeString();
                       }
                       ItemTemp->SubItems->Add(StrTemp);
                       StrTemp="";
                       if(!DataModule1->ADOQuery1->FieldByName("MediaIDList")->Value.IsNull())
                                StrTemp=DataModule1->ADOQuery1->FieldByName("MediaIDList")->Value;
                       StrTemp=StrTemp.Trim();
                       ListNodeLink[ListCount].Caption=StrTemp;
                       ItemTemp->Data=&ListNodeLink[ListCount++];
                       DataModule1->ADOQuery1->Next();
                }
                ListView1->Items->EndUpdate();
        }
}
void __fastcall TForm8::FormShow(TObject *Sender)
{
        GroupBox2->Width=Form8->Width/2;
        ListView2->Clear();
        ListView3->Clear();
        LoadMListFull();
}
//---------------------------------------------------------------------------


TForm8::LoadMediaDetail(AnsiString MediaList,TListView *ListView2)
{
        //TODO: Add your source code here
        AnsiString      StrSql;
        ListView2->Items->Clear();
        if(MediaList!="")
        {
                StrSql="select * from MediaInfo where ID In(";
                StrSql+=MediaList+")";
                if(Form6!=NULL)
                {
                        Form6->LoadMediaName(StrSql,ListView2);
                }
        }
}
void __fastcall TForm8::ListView1Click(TObject *Sender)
{
        TListItem               *ItemTemp;
        ListViewNodeDatEx       *NodeTemp;
        ItemTemp=ListView1->Selected;
        if(ItemTemp!=NULL)
        {
               NodeTemp=(ListViewNodeDatEx *)ItemTemp->Data;
               LoadMediaDetail(NodeTemp->Caption,ListView2);
               LoadTerminalList(NodeTemp->ID);
               Button2->Enabled=true;
               Button3->Enabled=true;
        }
        else
        {
               Button2->Enabled=false;
               Button3->Enabled=false;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm8::ListView2DblClick(TObject *Sender)
{
        if(Form10!=NULL)
        {
                Form10->EditMediaInfo(ListView2);
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm8::Button2Click(TObject *Sender)
{
        TListItem               *ItemTemp;
        ListViewNodeDatEx       *DTTemp;
        AnsiString              StrSql;
        AnsiString              StrTemp;
        TDateTime               TimeTemp;
        int                     ID;
        int                     IntTemp;

        ItemTemp=ListView1->Selected;
        if(ItemTemp!=NULL)
        {
                DTTemp=(ListViewNodeDatEx  *)ItemTemp->Data;
                ID=DTTemp->ID;
                Form6->ListNodeCount=0;
                StrSql="select * from MediaList where ID="+IntToStr(ID);
                DataModule1->InitAdoQuery(DataModule1->ADOQuery2,StrSql);
                DataModule1->ADOQuery2->Open();
                if(DataModule1->ADOQuery2->RecordCount>0)
                {
                        if(Form6!=NULL)
                        {
                                Form6->MediaID=ID;
                                if(!DataModule1->ADOQuery2->FieldByName("MName")->Value.IsNull())
                                       StrTemp=DataModule1->ADOQuery2->FieldByName("MName")->Value;
                                StrTemp=StrTemp.Trim();
                                Form6->Edit1->Text=StrTemp;

                                LoadMediaDetail(DTTemp->Caption,Form6->ListView2);

                                if(!DataModule1->ADOQuery2->FieldByName("Begin_Time")->Value.IsNull())
                                        TimeTemp=(TDateTime)DataModule1->ADOQuery2->FieldByName("Begin_Time")->Value;
                                Form6->DateTimePicker1->Date=TimeTemp;
                                if(!DataModule1->ADOQuery2->FieldByName("End_Time")->Value.IsNull())
                                        TimeTemp=(TDateTime)DataModule1->ADOQuery2->FieldByName("End_Time")->Value;
                                Form6->DateTimePicker4->Date=TimeTemp;
                                Form6->ShowType=2;
                                Form6->ShowModal();
                                if(Form6->StoreFlag)
                                {
                                        LoadMListFull();
                                        ListView1Click(Sender);
                                }
                        }
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm8::ListView1Change(TObject *Sender, TListItem *Item,
      TItemChange Change)
{
        ListView1Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm8::PopupMenu1Popup(TObject *Sender)
{
        TListItem               *ItemTemp;
        ListViewNodeDatEx       *DTTemp;
        AnsiString              StrSql;
        AnsiString              StrTemp;
        TDateTime               TimeTemp;
        int                     ID;
        int                     IntTemp;

        ItemTemp=ListView1->Selected;
        if(ItemTemp!=NULL)
        {
                M1->Enabled=true;
                D1->Enabled=true;
                A1->Enabled=false;
                R1->Enabled=false;
        }
        else
        {
                M1->Enabled=false;
                D1->Enabled=false;
                A1->Enabled=true;
                R1->Enabled=true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm8::R1Click(TObject *Sender)
{
        LoadMListFull();        
}
//---------------------------------------------------------------------------

void __fastcall TForm8::E1Click(TObject *Sender)
{
        TListItem               *ItemTemp;
        ListViewNodeDatEx       *DTTemp;
        ItemTemp=ListView1->Selected;
        if(ItemTemp!=NULL)
        {
                DTTemp=(ListViewNodeDatEx  *)ItemTemp->Data;
                ItemTemp=ListView3->Selected;
                if(ItemTemp==NULL)
                {
                        if(Form14!=NULL)
                        {
                                Form14->MediaListID=DTTemp->ID;
                                Form14->ShowModal();
                                if(Form14->StoreFlag)
                                {
                                        LoadTerminalList(DTTemp->ID);
                                }
                        }
                }
        }
}
//---------------------------------------------------------------------------


void __fastcall TForm8::LoadTerminalList(int MediaID)
{
        //TODO: Add your source code here
        AnsiString      StrSql;
        if(MediaID!=0)
        {
                StrSql="select * from TermDevice where TMediaIndex ="+IntToStr(MediaID);
                StrSql+=" and TGroup=0";
                if(Form12!=NULL)
                        Form12->LoadDeviceList(StrSql,ListView3);
        }
}
void __fastcall TForm8::Button3Click(TObject *Sender)
{
        TListItem               *ItemTemp;
        ListViewNodeDatEx       *DTTemp;
        AnsiString              StrSql;
        AnsiString              StrTemp;
        TDateTime               TimeTemp;
        int                     ID;
        int                     IntTemp;

        ItemTemp=ListView1->Selected;
        if(ItemTemp!=NULL)
        {
                DTTemp=(ListViewNodeDatEx  *)ItemTemp->Data;
                ID=DTTemp->ID;
                if(DeleteListInfo(ID,true))
                        LoadMListFull();
        }
}
//---------------------------------------------------------------------------

//ListID:媒体列表编号,HindtFlag:是否询问删除;true:询问;false:不询问
BOOL __fastcall TForm8::DeleteListInfo(int ListID, BOOL HintFlag)
{
        //TODO: Add your source code here
        AnsiString      StrSql;
        if(HintFlag)
        {
                if(MessageBox(Handle,"删除该媒体列表,确定吗?","系统提示",MB_OKCANCEL)!=1)
                        return false;
        }
        StrSql="delete from MediaList where ID="+IntToStr(ListID);
        DataModule1->InitAdoQuery(DataModule1->ADOQuery2,StrSql);
        DataModule1->ADOQuery2->ExecSQL();
        return true;
}
