//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "stdio.h"

#include "Unit3.h"
#include "Unit4.h"
#include "Unit5.h"
#include "Unit9.h"
#include "Unit10.h"
#include "DataCtrl.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm10 *Form10;
int             ListNodeCount;
//---------------------------------------------------------------------------
__fastcall TForm10::TForm10(TComponent* Owner)
        : TForm(Owner)
{
        ListNodeCount=0;
        //ListNodeCount=0;
        OrderType=1;
}
//---------------------------------------------------------------------------

void __fastcall TForm10::PopupMenu1Popup(TObject *Sender)
{
        if(ListView1->SelCount>0)
        {
                A1->Enabled=false;
                M1->Enabled=true;
                D1->Enabled=true;
                R1->Enabled=false;
                N1->Enabled=false;
                N3->Enabled=false;
                L1->Enabled=false;
        }
        else
        {
                A1->Enabled=true;
                M1->Enabled=false;
                D1->Enabled=false;
                R1->Enabled=true;
                N1->Enabled=true;
                N3->Enabled=true;
                L1->Enabled=true;
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm10::A1Click(TObject *Sender)
{
        //
        AnsiString      StrSql;
        StrSql="insert into MediaInfo(";
        if(Form9!=NULL)
        {
                Form9->ShowModal();
                if(Form9->SelFlag)
                {
                        if(Form9->SelType==1)
                        {
                                if(Form5!=NULL)
                                {
                                        Form5->Edit1->Clear();
                                        Form5->ListBox1->Clear();
                                        Form5->Caption="视频展示属性";
                                        Form5->MediaType=2;
                                        Form5->ShowModal();
                                        if(Form5->StoreFlag)
                                        {//添加视频项目
                                                StrSql+="MName,MType,PlayMode,CBType,ScreenType,SFileName)Values('";
                                                StrSql+=Form5->Edit1->Text.Trim();
                                                StrSql+="',1,";
                                                if(Form5->RadioButton1->Checked)
                                                {
                                                        StrSql+="1,";
                                                }
                                                else
                                                        StrSql+="2,";
                                                if(Form5->RadioButton3->Checked)
                                                {
                                                        StrSql+="1,";
                                                }
                                                else
                                                        StrSql+="2,";
                                                if(Form5->RadioButton5->Checked)
                                                {
                                                        StrSql+="1,'";
                                                }
                                                else    if(Form5->RadioButton6->Checked)
                                                        StrSql+="2,'";
                                                else
                                                        StrSql+="3,'";
                                                StrSql+=GetFullFileNameExt(Form5->ListBox1);
                                                StrSql+="')";
                                                DataModule1->InitAdoQuery(DataModule1->ADOQuery1,StrSql);
                                                DataModule1->ADOQuery1->ExecSQL();
                                        }
                                }
                        }
                        else    if(Form9->SelType==2)//添加循环图片
                        {
                                if(Form3!=NULL)
                                {
                                        Form3->Edit1->Clear();
                                        Form3->Edit2->Clear();
                                        Form3->Edit3->Clear();
                                        Form3->ShowModal();
                                        if(Form3->StoreFlag)
                                        {
                                                StrSql+="MName,MType,SFileName,SInterval,PicType)Values('";
                                                StrSql+=Form3->Edit1->Text.Trim();
                                                StrSql+="',2,'";
                                                StrSql+=Form3->Edit2->Text.Trim();
                                                StrSql+="',";
                                                if(Form3->Edit3->Text!="")
                                                        StrSql+=Form3->Edit3->Text.Trim()+",";
                                                else    
                                                        StrSql+="3,";
                                                if(Form3->RadioButton1->Checked)
                                                {
                                                        StrSql+="1";
                                                }
                                                else    if(Form3->RadioButton2->Checked)
                                                        {
                                                                StrSql+="2";
                                                        }
                                                else    if(Form3->RadioButton3->Checked)
                                                        {
                                                                StrSql+="3";
                                                        }
                                                else   if(Form3->RadioButton4->Checked)
                                                        {
                                                                StrSql+="4";
                                                        }
                                                else   if(Form3->RadioButton5->Checked)
                                                        {
                                                                StrSql+="5";
                                                        }
                                                else    if(Form3->RadioButton6->Checked)
                                                        StrSql+="6";
                                                else    if(Form3->RadioButton7->Checked)
                                                        StrSql+="7";
                                                else    if(Form3->RadioButton8->Checked)
                                                        StrSql+="8";
                                                else    if(Form3->RadioButton9->Checked)
                                                        StrSql+="9";

                                                StrSql+=")";
                                                DataModule1->InitAdoQuery(DataModule1->ADOQuery1,StrSql);
                                                DataModule1->ADOQuery1->ExecSQL();
                                        }
                                }
                        }
                        else    if(Form9->SelType==3)//滚动文本
                        {
                                if(Form4!=NULL)
                                {
                                        Form4->Edit1->Clear();
                                        Form4->Edit2->Clear();
                                        Form4->Edit3->Clear();
                                        Form4->Edit4->Clear();
                                        Form4->ShowModal();
                                        if(Form4->StoreFlag)
                                        {//添加Flash项目
                                                StrSql+="MName,MType,SFileName,ReceivePort,MFontSize)Values('";
                                                StrSql+=Form4->Edit1->Text.Trim();
                                                StrSql+="',3,'";
                                                StrSql+=Form4->Edit3->Text;

                                                StrSql+="',";
                                                if(Form4->Edit4->Text!="")
                                                        StrSql+=Form4->Edit4->Text;
                                                else
                                                        StrSql+="256";

                                                StrSql+=",";
                                                if(Form4->Edit2->Text!="")
                                                        StrSql+=Form4->Edit2->Text.Trim();
                                                else
                                                        StrSql+="170";
                                                StrSql+=")";
                                                DataModule1->InitAdoQuery(DataModule1->ADOQuery1,StrSql);
                                                DataModule1->ADOQuery1->ExecSQL();
                                        }
                                }
                        }
                        else    if(Form9->SelType==4)
                        {
                                if(Form5!=NULL)
                                {
                                        Form5->Edit1->Clear();
                                        Form5->ListBox1->Clear();
                                        Form5->Caption="Flash展示属性";
                                        Form5->MediaType=1;
                                        Form5->ShowModal();
                                        if(Form5->StoreFlag)
                                        {//添加Flash项目
                                                StrSql+="MName,MType,PlayMode,CBType,ScreenType,SFileName)Values('";
                                                StrSql+=Form5->Edit1->Text.Trim();
                                                StrSql+="',4,";
                                                if(Form5->RadioButton1->Checked)
                                                {
                                                        StrSql+="1,";
                                                }
                                                else
                                                        StrSql+="2,";
                                                if(Form5->RadioButton3->Checked)
                                                {
                                                        StrSql+="1,";
                                                }
                                                else
                                                        StrSql+="2,";
                                                if(Form5->RadioButton5->Checked)
                                                {
                                                        StrSql+="1,'";
                                                }
                                                else    if(Form5->RadioButton6->Checked)
                                                        StrSql+="2,'";
                                                else
                                                        StrSql+="3,'";
                                                StrSql+=GetFullFileNameExt(Form5->ListBox1);
                                                StrSql+="')";
                                                DataModule1->InitAdoQuery(DataModule1->ADOQuery1,StrSql);
                                                DataModule1->ADOQuery1->ExecSQL();
                                        }
                                }
                        }
                }
        }
        CheckBox1Click(Sender);
}
//---------------------------------------------------------------------------

AnsiString __fastcall TForm10::GetFullFileNameExt(TListBox * ListBox)
{
        //TODO: Add your source code here
        AnsiString      StrTemp;
        
        for(int i=0;i<ListBox->Items->Count;i++)
        {
                StrTemp+="#";
                
                StrTemp+=ListBox->Items->Strings[i].Trim();
        }
        StrTemp+="#";
        return StrTemp.Trim();
}

void __fastcall TForm10::LoadMediaInfo(AnsiString       SqlTemp,TListView * ListView)
{
        //TODO: Add your source code here
        AnsiString      StrSql;
        AnsiString      StrTemp;
        TListItem       *ItemTemp;
        int             MType;
        int             ID;
        if(SqlTemp=="")
        {
                StrSql="select * from MediaInfo ";
                StrSql+=GetSqlExt();
                if(OrderType==1)
                        StrSql+=" order by MName";
                else   if(OrderType==2)
                        StrSql+=" order by MType";
        }
        else
                {
                        StrSql=SqlTemp;
                }
        DataModule1->InitAdoQuery(DataModule1->ADOQuery1,StrSql);
        DataModule1->ADOQuery1->Open();
        ListView->Items->Clear();
        ListView->Items->BeginUpdate();
        if(ListNodeCount>200)
                ListNodeCount=0;
        while(!DataModule1->ADOQuery1->Eof)
        {
               ID=DataModule1->ADOQuery1->FieldByName("ID")->Value;
               if(!DataModule1->ADOQuery1->FieldByName("MName")->Value.IsNull())
                        StrTemp=DataModule1->ADOQuery1->FieldByName("MName")->Value;
               StrTemp=StrTemp.Trim();
               ItemTemp=ListView->Items->Add();
               ItemTemp->Caption=StrTemp;
               ListViewNodeList[ListNodeCount].ID=ID;
               MType=DataModule1->ADOQuery1->FieldByName("MType")->Value;
               ListViewNodeList[ListNodeCount].MType=MType;

               ItemTemp->Data=&ListViewNodeList[ListNodeCount];
               if(MType==1)
                        ItemTemp->ImageIndex=4;
               else     if(MType==2)
                        ItemTemp->ImageIndex=1;
               else     if(MType==3)
                        ItemTemp->ImageIndex=6;
               else     if(MType==4)
                        ItemTemp->ImageIndex=5;
               ListNodeCount++;
               DataModule1->ADOQuery1->Next();
        }
        ListView->Items->EndUpdate();
}

AnsiString __fastcall TForm10::GetSqlExt()
{
        //TODO: Add your source code here
        BOOL            QueryFlag;//
        AnsiString      StrSql;
        QueryFlag=false;
        if(CheckBox1->Checked)
        {
               QueryFlag=true;
               StrSql=" where MType=1 ";
        }
        if(CheckBox2->Checked)
        {
               if(QueryFlag)
                        StrSql+=" or MType=4 ";
               else
                        StrSql+=" where MType=4 ";
               QueryFlag=true;
        }
        if(CheckBox3->Checked)
        {
               if(QueryFlag)
                        StrSql+=" or MType=2 ";
               else
                        StrSql+=" where MType=2 ";
               QueryFlag=true;
        }
        if(CheckBox4->Checked)
        {
               if(QueryFlag)
                        StrSql+=" or MType=3 ";
               else
                        StrSql+=" where MType=3 ";
               QueryFlag=true;
        }
        return  StrSql;
}
void __fastcall TForm10::FormShow(TObject *Sender)
{
        LoadMediaInfo("",ListView1);
}
//---------------------------------------------------------------------------

void __fastcall TForm10::CheckBox1Click(TObject *Sender)
{
       FormShow(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm10::R1Click(TObject *Sender)
{
       CheckBox1Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm10::N2Click(TObject *Sender)
{
        OrderType=1;
        N2->Checked=true;
        T1->Checked=false;
        CheckBox1Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm10::T1Click(TObject *Sender)
{
        OrderType=2;
        T1->Checked=true;
        N2->Checked=false;
        CheckBox1Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm10::M1Click(TObject *Sender)
{
        //
        if(EditMediaInfo(ListView1))
                CheckBox1Click(Sender);
}
//---------------------------------------------------------------------------


void __fastcall TForm10::GetFileSourceName(AnsiString FullName,TListBox *ListBox)
{
        //TODO: Add your source code here
        char            Buf[1024];
        AnsiString      StrTemp;
        memset(Buf,0x00,sizeof(Buf));
        sprintf(Buf,"%s",FullName);
        ListBox->Items->Clear();
        for(int i=1;i<strlen(Buf);i++)
        {
                if((Buf[i]!='#')&&(i!=strlen(Buf)-1))
                        StrTemp+=Buf[i];
                else
                {
                        if(StrTemp!="")
                        {
                                ListBox->Items->Add(StrTemp);
                        }
                        StrTemp="";
                }
        }
}
void __fastcall TForm10::D1Click(TObject *Sender)
{
        TListItem       *ItemTemp;
        ListViewNodeDat *NodeTemp;
        int             ID;
        int             MType;
        int             InteTemp;
        int             SelCount;
        int             TotalCount;
        AnsiString      StrSql;
        AnsiString      StrTemp;
        ItemTemp=ListView1->Selected;
        SelCount=ListView1->SelCount;
        if(SelCount==1)
        {
                if(ItemTemp!=NULL)
                {
                        if(MessageBox(Handle,"删除该媒体文件，确定吗？","删除确认",MB_OKCANCEL)==1)
                        {
                                NodeTemp=(ListViewNodeDat *)ItemTemp->Data;
                                ID=NodeTemp->ID;
                                DelMediaInfo(ID);
                                CheckBox1Click(Sender);
                        }
                }
        }
        else    if(SelCount>1)//删除多个媒体文件
        {
                if(MessageBox(Handle,"删除选定的媒体文件，确定吗？","删除确认",MB_OKCANCEL)==1)
                {
                        TotalCount=ListView1->Items->Count;
                        for(int i=0;i<SelCount;i++)
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
                                NodeTemp=(ListViewNodeDat *)ItemTemp->Data;
                                ID=NodeTemp->ID;
                                DelMediaInfo(ID);
                        }
                }
                CheckBox1Click(Sender);
        }
}
//---------------------------------------------------------------------------
//
void __fastcall TForm10::DelMediaInfo(int ID)
{
        //TODO: Add your source code here
        AnsiString      StrSql;
        StrSql="delete from MediaInfo where ID="+IntToStr(ID);
        DataModule1->InitAdoQuery(DataModule1->ADOQuery1,StrSql);
        DataModule1->ADOQuery1->ExecSQL();
}

bool __fastcall TForm10::EditMediaInfo(TListView * ListView1)
{
        //TODO: Add your source code here
        TListItem       *ItemTemp;
        ListViewNodeDat *NodeTemp;
        int             ID;
        int             MType;
        int             InteTemp;
        AnsiString      StrSql;
        AnsiString      StrTemp;
        ItemTemp=ListView1->Selected;
        if(ItemTemp!=NULL)
        {
                NodeTemp=(ListViewNodeDat *)ItemTemp->Data;
                ID=NodeTemp->ID;
                MType=NodeTemp->MType;
                StrSql="select * from MediaInfo where ID="+IntToStr(ID);
                DataModule1->InitAdoQuery(DataModule1->ADOQuery1,StrSql);
                DataModule1->ADOQuery1->Open();

                if(DataModule1->ADOQuery1->RecordCount>0)
                {
                        if(MType==1)
                        {
                                if(!DataModule1->ADOQuery1->FieldByName("MName")->Value.IsNull())
                                        StrTemp=DataModule1->ADOQuery1->FieldByName("MName")->Value;
                                StrTemp=StrTemp.Trim();
                                Form5->Edit1->Text=StrTemp;
                                Form5->Caption="视频展示属性";
                                InteTemp=DataModule1->ADOQuery1->FieldByName("PlayMode")->Value;
                                if(InteTemp==1)
                                        Form5->RadioButton1->Checked=true;
                                else    if(InteTemp==2)
                                        Form5->RadioButton2->Checked=true;
                                InteTemp=DataModule1->ADOQuery1->FieldByName("CBType")->Value;
                                if(InteTemp==1)
                                        Form5->RadioButton3->Checked=true;
                                else    if(InteTemp==2)
                                        Form5->RadioButton4->Checked=true;
                                InteTemp=DataModule1->ADOQuery1->FieldByName("ScreenType")->Value;
                                if(InteTemp==1)
                                        Form5->RadioButton5->Checked=true;
                                else    if(InteTemp==2)
                                        Form5->RadioButton6->Checked=true;
                                else    if(InteTemp==3)
                                        Form5->RadioButton7->Checked=true;
                                if(!DataModule1->ADOQuery1->FieldByName("SFileName")->Value.IsNull())
                                        StrTemp=DataModule1->ADOQuery1->FieldByName("SFileName")->Value;
                                StrTemp=StrTemp.Trim();
                                GetFileSourceName(StrTemp,Form5->ListBox1);
                                Form5->MediaType=2;
                                Form5->ShowModal();
                                if(Form5->StoreFlag)
                                {
                                        StrSql="update MediaInfo set MName='";
                                        StrSql+=Form5->Edit1->Text.Trim();
                                        StrSql+="',PlayMode=";
                                        if(Form5->RadioButton1->Checked)
                                        {
                                                StrSql+="1,";
                                        }
                                        else
                                                StrSql+="2,";
                                        StrSql+="CBType=";
                                        if(Form5->RadioButton3->Checked)
                                        {
                                                StrSql+="1,";
                                        }
                                        else
                                                StrSql+="2,";
                                        StrSql+="ScreenType=";
                                        if(Form5->RadioButton5->Checked)
                                        {
                                                StrSql+="1,";
                                        }
                                        else    if(Form5->RadioButton6->Checked)
                                                StrSql+="2,";
                                        else
                                                StrSql+="3,";
                                        StrSql+="SFileName='";
                                        StrSql+=GetFullFileNameExt(Form5->ListBox1);
                                        StrSql+="' where ID="+IntToStr(ID);
                                        DataModule1->InitAdoQuery(DataModule1->ADOQuery1,StrSql);
                                        DataModule1->ADOQuery1->ExecSQL();
                                        return true;
                                }
                        }
                        else    if(MType==2)
                        {
                                if(!DataModule1->ADOQuery1->FieldByName("MName")->Value.IsNull())
                                        StrTemp=DataModule1->ADOQuery1->FieldByName("MName")->Value;
                                StrTemp=StrTemp.Trim();
                                Form3->Edit1->Text=StrTemp;

                                InteTemp=DataModule1->ADOQuery1->FieldByName("PicType")->Value;
                                if(InteTemp==1)
                                        Form3->RadioButton1->Checked=true;
                                else    if(InteTemp==2)
                                        Form3->RadioButton2->Checked=true;
                                else    if(InteTemp==3)
                                        Form3->RadioButton3->Checked=true;
                                else    if(InteTemp==4)
                                        Form3->RadioButton4->Checked=true;
                                else    if(InteTemp==5)
                                        Form3->RadioButton5->Checked=true;
                                else    if(InteTemp==6)
                                        Form3->RadioButton6->Checked=true;
                                else    if(InteTemp==7)
                                        Form3->RadioButton7->Checked=true;
                                else    if(InteTemp==8)
                                        Form3->RadioButton8->Checked=true;
                                else    if(InteTemp==9)
                                        Form3->RadioButton9->Checked=true;
                                InteTemp=DataModule1->ADOQuery1->FieldByName("SInterval")->Value;
                                Form3->Edit3->Text=IntToStr(InteTemp);
                                if(!DataModule1->ADOQuery1->FieldByName("SFileName")->Value.IsNull())
                                        StrTemp=DataModule1->ADOQuery1->FieldByName("SFileName")->Value;
                                StrTemp=StrTemp.Trim();
                                //StrTemp=StrTemp.SubString(2,strlen(StrTemp.c_str())-2);
                                Form3->Edit2->Text=StrTemp;

                                Form3->ShowModal();
                                if(Form3->StoreFlag)
                                {
                                        StrSql="update MediaInfo set MName='";
                                        StrSql+=Form3->Edit1->Text.Trim();
                                        StrSql+="',PicType=";
                                        if(Form3->RadioButton1->Checked)
                                        {
                                                StrSql+="1,";
                                        }
                                        else    if(Form3->RadioButton2->Checked)
                                                StrSql+="2,";

                                        else    if(Form3->RadioButton3->Checked)
                                        {
                                                StrSql+="3,";
                                        }
                                        else    if(Form3->RadioButton4->Checked)
                                                StrSql+="4,";
                                        else    if(Form3->RadioButton5->Checked)
                                        {
                                                StrSql+="5,";
                                        }
                                        else    if(Form3->RadioButton6->Checked)
                                                StrSql+="6,";
                                        else    if(Form3->RadioButton7->Checked)
                                                StrSql+="7,";
                                        else    if(Form3->RadioButton8->Checked)
                                                StrSql+="8,";
                                        else    if(Form3->RadioButton9->Checked)
                                                StrSql+="9,";
                                        StrSql+="SFileName='";
                                        StrSql+=Form3->Edit2->Text.Trim();
                                        StrSql+="',SInterval="+Form3->Edit3->Text.Trim();
                                        StrSql+=" where ID="+IntToStr(ID);
                                        DataModule1->InitAdoQuery(DataModule1->ADOQuery1,StrSql);
                                        DataModule1->ADOQuery1->ExecSQL();
                                        return true;
                                }
                        }
                        else    if(MType==3)
                        {
                                int    IntTemp;
                                if(!DataModule1->ADOQuery1->FieldByName("MName")->Value.IsNull())
                                        StrTemp=DataModule1->ADOQuery1->FieldByName("MName")->Value;
                                StrTemp=StrTemp.Trim();
                                Form4->Edit1->Text=StrTemp;

                                if(!DataModule1->ADOQuery1->FieldByName("SFileName")->Value.IsNull())
                                        StrTemp=DataModule1->ADOQuery1->FieldByName("SFileName")->Value;
                                StrTemp=StrTemp.Trim();
                                Form4->Edit3->Text=StrTemp;

                                IntTemp=DataModule1->ADOQuery1->FieldByName("ReceivePort")->Value;
                                Form4->Edit4->Text=IntToStr(IntTemp);

                                IntTemp=DataModule1->ADOQuery1->FieldByName("MFontSize")->Value;
                                Form4->Edit2->Text=IntToStr(IntTemp);

                                Form4->ShowModal();
                                if(Form4->StoreFlag)
                                {
                                        StrSql="update MediaInfo set MName='";
                                        StrSql+=Form4->Edit1->Text.Trim();
                                        StrSql+="',SFileName='";
                                        StrSql+=Form4->Edit3->Text.Trim();
                                        StrSql+="',ReceivePort=";
                                        if(Form4->Edit4->Text!="")
                                                StrSql+=Form4->Edit4->Text.Trim()+",";
                                        else
                                                StrSql+="256,";
                                        StrSql+="MFontSize=";
                                        if(Form4->Edit2->Text!="")
                                                StrSql+=Form4->Edit2->Text.Trim();
                                        else
                                                StrSql+="170";
                                        StrSql+=" where ID="+IntToStr(ID);
                                        DataModule1->InitAdoQuery(DataModule1->ADOQuery1,StrSql);
                                        DataModule1->ADOQuery1->ExecSQL();
                                        return true;
                                }
                        }
                        else    if(MType==4)
                        {
                                if(!DataModule1->ADOQuery1->FieldByName("MName")->Value.IsNull())
                                        StrTemp=DataModule1->ADOQuery1->FieldByName("MName")->Value;
                                StrTemp=StrTemp.Trim();
                                Form5->Edit1->Text=StrTemp;
                                Form5->Caption="Flash展示属性";
                                InteTemp=DataModule1->ADOQuery1->FieldByName("PlayMode")->Value;
                                if(InteTemp==1)
                                        Form5->RadioButton1->Checked=true;
                                else    if(InteTemp==2)
                                        Form5->RadioButton2->Checked=true;
                                InteTemp=DataModule1->ADOQuery1->FieldByName("CBType")->Value;
                                if(InteTemp==1)
                                        Form5->RadioButton3->Checked=true;
                                else    if(InteTemp==2)
                                        Form5->RadioButton4->Checked=true;
                                InteTemp=DataModule1->ADOQuery1->FieldByName("ScreenType")->Value;
                                if(InteTemp==1)
                                        Form5->RadioButton5->Checked=true;
                                else    if(InteTemp==2)
                                        Form5->RadioButton6->Checked=true;
                                else    if(InteTemp==3)
                                        Form5->RadioButton7->Checked=true;
                                if(!DataModule1->ADOQuery1->FieldByName("SFileName")->Value.IsNull())
                                        StrTemp=DataModule1->ADOQuery1->FieldByName("SFileName")->Value;
                                StrTemp=StrTemp.Trim();
                                GetFileSourceName(StrTemp,Form5->ListBox1);
                                Form5->MediaType=1;
                                Form5->ShowModal();
                                if(Form5->StoreFlag)
                                {
                                        StrSql="update MediaInfo set MName='";
                                        StrSql+=Form5->Edit1->Text.Trim();
                                        StrSql+="',PlayMode=";
                                        if(Form5->RadioButton1->Checked)
                                        {
                                                StrSql+="1,";
                                        }
                                        else
                                                StrSql+="2,";
                                        StrSql+="CBType=";
                                        if(Form5->RadioButton3->Checked)
                                        {
                                                StrSql+="1,";
                                        }
                                        else
                                                StrSql+="2,";
                                        StrSql+="ScreenType=";
                                        if(Form5->RadioButton5->Checked)
                                        {
                                                StrSql+="1,";
                                        }
                                        else    if(Form5->RadioButton6->Checked)
                                                StrSql+="2,";
                                        else
                                                StrSql+="3,";
                                        StrSql+="SFileName='";
                                        StrSql+=GetFullFileNameExt(Form5->ListBox1);
                                        StrSql+="' where ID="+IntToStr(ID);
                                        DataModule1->InitAdoQuery(DataModule1->ADOQuery1,StrSql);
                                        DataModule1->ADOQuery1->ExecSQL();
                                        return true;
                                }
                        }
                }
        }
        return false;
}
void __fastcall TForm10::L1Click(TObject *Sender)
{
        TListItem       *ItemTemp;
        ListViewNodeDat *NodeTemp;
        int             ID;
        int             MType;
        int             InteTemp;
        int             SelCount;
        int             TotalCount;
        AnsiString      StrSql;
        AnsiString      StrTemp;


        if(MessageBox(Handle,"删除所有的媒体文件，确定吗？","删除确认",MB_OKCANCEL)==1)
        {
              TotalCount=ListView1->Items->Count;
              for(int j=0;j<TotalCount;j++)
              {
                        ItemTemp=ListView1->Items->Item[j];
                        NodeTemp=(ListViewNodeDat *)ItemTemp->Data;
                        ID=NodeTemp->ID;
                        DelMediaInfo(ID);
              }              
              CheckBox1Click(Sender);
        }
        
}
//---------------------------------------------------------------------------

