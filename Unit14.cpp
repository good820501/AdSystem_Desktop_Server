//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit14.h"
#include "Unit10.h"
#include "Main.h"
#include "DataCtrl.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm14 *Form14;
//---------------------------------------------------------------------------
__fastcall TForm14::TForm14(TComponent* Owner)
        : TForm(Owner)
{
        MediaListID=0;
}
//---------------------------------------------------------------------------

void __fastcall TForm14::FormShow(TObject *Sender)
{
        //
        StoreFlag=false;
        LoadTotalTerm();
        LoadSelTermList();
}
//---------------------------------------------------------------------------


void __fastcall TForm14::LoadSelTermList()
{
        //TODO: Add your source code here
        AnsiString      StrSql;
        if(MediaListID!=0)
        {
                StrSql="select * from TermDevice where TMediaIndex ="+IntToStr(MediaListID);
                StrSql+=" and TGroup=0";
                if(Form12!=NULL)
                        Form12->LoadDeviceList(StrSql,ListView2);
                OldTerminalList=GetTerminalList();
        }
}

void __fastcall TForm14::LoadTotalTerm()
{
        //TODO: Add your source code here
        AnsiString      StrSql;
        StrSql="select * from TermDevice where TMediaIndex = 0";
        StrSql+=" and TGroup=0";
        if(Form12!=NULL)
                Form12->LoadDeviceList(StrSql,ListView1);
}
void __fastcall TForm14::Button6Click(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------
void __fastcall TForm14::Button2Click(TObject *Sender)
{
        int             ItemIndex;
        AnsiString      StrTemp;
        TListItem       *ItemTemp;
        ListViewNodeDat *DaTemp;
        if(ListView1->SelCount>0)
        {
                ItemTemp=ListView1->Selected;
                if(ItemTemp!=NULL)
                {
                        AddToListBox2(ItemTemp);
                        //LoadTotalTerm();
                }
        }        
}
//---------------------------------------------------------------------------

void __fastcall TForm14::Button3Click(TObject *Sender)
{
        TListItem       *Item;
        for(int i=0;i<ListView1->Items->Count;i++)
        {
               Item=ListView1->Items->Item[i];
               if(Item!=NULL)
                        AddToListBox2(Item);
        }
        //LoadTotalTerm();
}
//---------------------------------------------------------------------------

void __fastcall TForm14::Button4Click(TObject *Sender)
{
        int             ItemIndex;
        TListItem       *Item;
        AnsiString      Caption;
        if(ListView2->SelCount>0)
        {
                Item=ListView2->Selected;
                Caption=Item->Caption;
                ListView2->Items->Delete(ListView2->ItemIndex);
                ListView2->Refresh();
                //LoadTotalTerm();
        }        
}
//---------------------------------------------------------------------------

void __fastcall TForm14::Button5Click(TObject *Sender)
{
        ListView2->Items->Clear();
        //LoadTotalTerm();       
}
//---------------------------------------------------------------------------


void __fastcall TForm14::AddToListBox2(TListItem       *ItemTemp)
{
        //TODO: Add your source code here
        TListItem       *Item;
        for(int i=0;i<ListView2->Items->Count;i++)
        {
                Item=ListView2->Items->Item[i];
                if(Item->Caption==ItemTemp->Caption)
                        return;
        }
        ListView2->Items->BeginUpdate();
        Item=ListView2->Items->Add();
        Item->Caption=ItemTemp->Caption;
        
        Item->Data=ItemTemp->Data;
        Item->ImageIndex=ItemTemp->ImageIndex;
        ListView2->Items->EndUpdate();
}
void __fastcall TForm14::ListView2DragOver(TObject *Sender,
      TObject *Source, int X, int Y, TDragState State, bool &Accept)
{
        Button2Click(Sender);        
}
//---------------------------------------------------------------------------

void __fastcall TForm14::Button1Click(TObject *Sender)
{
        //
        AnsiString      StrSql;
        AnsiString      StrTemp;
        StrTemp=GetTerminalList();
        if(OldTerminalList!="")
        {
                StrSql="update TermDevice set TMediaIndex=0 where ID In("+OldTerminalList+")";
                DataModule1->InitAdoQuery(DataModule1->ADOQuery2,StrSql);
                DataModule1->ADOQuery2->ExecSQL();
        }
        if(StrTemp!="")
        {
                StrSql="update TermDevice set TMediaIndex="+IntToStr(MediaListID);
                StrSql+=" where ID In("+StrTemp+")";
                DataModule1->InitAdoQuery(DataModule1->ADOQuery2,StrSql);
                DataModule1->ADOQuery2->ExecSQL();
        }
        StoreFlag=true;
        Close();
}
//---------------------------------------------------------------------------


AnsiString __fastcall TForm14::GetTerminalList()
{
        //TODO: Add your source code here
        AnsiString      StrTemp;
        TListItem       *ItemTemp;
        ListViewNodeDat *DaTemp;
        for(int i=0;i<ListView2->Items->Count;i++)
        {
                ItemTemp=ListView2->Items->Item[i];
                DaTemp=(ListViewNodeDat *)ItemTemp->Data;
                if(StrTemp=="")
                        StrTemp=IntToStr(DaTemp->ID);
                else
                        StrTemp+=","+IntToStr(DaTemp->ID);
        }
        return StrTemp;
}
