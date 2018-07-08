//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit6.h"
#include "Libs.h"
#include "DataCtrl.h"
#include "Unit10.h"
#include "io.h"
#include "stdio.h"

TForm7          *DividWnd[8];
TSplitter       *SplitList[6];
int     ChildNums;
int     SpNums;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm6 *Form6;
//---------------------------------------------------------------------------
__fastcall TForm6::TForm6(TComponent* Owner)
        : TForm(Owner)
{
        ChildNums=0;
        SpNums=0;
        for(int i=0;i<8;i++)
        {
                DividWnd[i]=NULL;
        }
        for(int i=0;i<6;i++)
        {
                SplitList[i]=NULL;
        }
}
//---------------------------------------------------------------------------



void __fastcall TForm6::InitFormState()
{
        //TODO: Add your source code here
        int             WndCount;
        TForm7          *WndTemp;
        TListItem       *ItemTemp;

        SelIndex=1;
        ComboBox1->Items->Clear();
        //ComboBox2->Items->Clear();
        ComboBox3->Items->Clear();
        //ComboBox5->Items->Clear();
        //ComboBox7->Items->Clear();
        //ComboBox8->Items->Clear();
        ComboBox9->Items->Clear();
        //ComboBox1->Items->Clear();
        for(int  i=0;i<ListView2->Items->Count;i++)
        {
                ItemTemp=ListView2->Items->Item[i];
                if(ItemTemp!="")
                {
                        ComboBox1->Items->Add(ItemTemp->Caption);
                        //ComboBox2->Items->Add(ItemTemp->Caption);
                        ComboBox3->Items->Add(ItemTemp->Caption);
                        //ComboBox5->Items->Add(ItemTemp->Caption);
                        //ComboBox7->Items->Add(ItemTemp->Caption);
                        //ComboBox8->Items->Add(ItemTemp->Caption);
                        ComboBox9->Items->Add(ItemTemp->Caption);
                }
        }
}
void __fastcall TForm6::FormShow(TObject *Sender)
{
        //Panel1->Height=Screen->Height*0.25;
        //Panel1->Width=Screen->Width*0.25;
        InitFormState();
        LoadAllMedia();
        GetInitCfg();
        StoreFlag=false;
}
//---------------------------------------------------------------------------
TForm7 * __fastcall TForm6::GetChildWnd(int Num, int index)
{
        //TODO: Add your source code here

        //return WndTemp;
}
//清空子窗口
void __fastcall TForm6::ClearChildWnd()
{
        //TODO: Add your source code here
        TForm7  *WndTemp;
        for(int i=ChildNums;i>=1;i--)
        {
                WndTemp=DividWnd[i];
                if(WndTemp!=NULL)
                {
                        delete WndTemp;
                        WndTemp=NULL;
                }
        }
        ChildNums=0;
}
//更新子窗口状态
void __fastcall TForm6::UpdateWindowState(int SelIndex)
{
        //TODO: Add your source code here
        TForm7          *WndTemp;
        TListItem       *ItemTemp;
        ListViewNodeDat *DaTemp;
        BOOL            FindFlag=false;
        for(int i=1;i<=ChildNums;i++)
        {
               WndTemp=DividWnd[i];
               if(i==SelIndex)
               {
                        WndTemp->OnGetFocus();
               }
               else
                        WndTemp->LostFocusPrc();
        }
        ComboBox1->Text="";
        for(int i=0;i<ListView2->Items->Count;i++)
        {
                ItemTemp=ListView2->Items->Item[i];
                DaTemp=(ListViewNodeDat *)ItemTemp->Data;
                if(DaTemp->ID==DividWnd[SelIndex]->MediaIndex)
                {
                        ComboBox1->Text=ItemTemp->Caption;
                        break;
                }
        }
}



void __fastcall TForm6::AddToWndList(TForm7 * ForTemp)
{
        //TODO: Add your source code here
        if(ForTemp!=NULL)
        {
                DividWnd[++ChildNums]=ForTemp;
        }
}
void __fastcall TForm6::FormClose(TObject *Sender, TCloseAction &Action)
{
       ClearSplitList();
       ClearChildWnd();       
}
//---------------------------------------------------------------------------

void __fastcall TForm6::ClearSplitList()
{
        //TODO: Add your source code here
        TSplitter       *SplitTemp;
        for(int i=0;i<SpNums;i++)
       {
                SplitTemp=SplitList[i];
                if(SplitTemp!=NULL)
                {
                        delete SplitTemp;
                        SplitTemp=NULL;
                }
       }
       SpNums=0;
}
//添加滑动窗口条 Flag:1-上下分；2：左右分
void __fastcall TForm6::AddSplitter(int Flag)
{
        //TODO: Add your source code here

}


void __fastcall TForm6::RadioButton5Click(TObject *Sender)
{
        //

}
//---------------------------------------------------------------------------

void __fastcall TForm6::LoadMediaName(AnsiString SqlTemp, TListView * ListView)
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
                StrSql+=GetSqlExt(true);
                StrSql+=" order by MType";
         }
         else
                StrSql=SqlTemp;
         DataModule1->InitAdoQuery(DataModule1->ADOQuery1,StrSql);
         DataModule1->ADOQuery1->Open();
         ListView->Items->Clear();
         ListView->Items->BeginUpdate();
         ListNodeCount++;
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
//Flag=1:加载全部列表;0:加载选定列表
AnsiString __fastcall TForm6::GetSqlExt(BOOL    Flag)
{
        //TODO: Add your source code here
        BOOL            QueryFlag;//
        AnsiString      StrSql;
        QueryFlag=false;
        if(Flag)
        {
                if(CheckBox1->Checked)
                {
                        QueryFlag=true;
                        StrSql=" where (MType=1 ";
                }
                if(CheckBox2->Checked)
                {
                        if(QueryFlag)
                                StrSql+=" or MType=4 ";
                        else
                                StrSql+=" where (MType=4 ";
                        QueryFlag=true;
                }
                if(CheckBox3->Checked)
                {
                        if(QueryFlag)
                                StrSql+=" or MType=2 ";
                        else
                                StrSql+=" where (MType=2 ";
                        QueryFlag=true;
                }
                if(CheckBox4->Checked)
                {
                        if(QueryFlag)
                                StrSql+=" or MType=3 ";
                        else
                                StrSql+=" where (MType=3 ";
                        QueryFlag=true;
                }
                StrSql+=")";
                if(Edit2->Text.Trim()!="")
                {
                        if(QueryFlag)
                                StrSql+=" and MName like '%"+Edit2->Text.Trim()+"%'";
                        else
                                StrSql+=" where MName like '%"+Edit2->Text.Trim()+"%'";
                        QueryFlag=true;
                }
        }
        else
        {
                if(CheckBox4->Checked)
                {
                        QueryFlag=true;
                        StrSql=" where (MType=1 ";
                }
                if(CheckBox5->Checked)
                {
                        if(QueryFlag)
                                StrSql+=" or MType=4 ";
                        else
                                StrSql+=" where (MType=4 ";
                        QueryFlag=true;
                }
                if(CheckBox6->Checked)
                {
                        if(QueryFlag)
                                StrSql+=" or MType=2 ";
                        else
                                StrSql+=" where (MType=2 ";
                        QueryFlag=true;
                }
                if(CheckBox7->Checked)
                {
                        if(QueryFlag)
                                StrSql+=" or MType=3 ";
                        else
                                StrSql+=" where (MType=3 ";
                        QueryFlag=true;
                }
                StrSql+=")";
                if(Edit3->Text.Trim()!="")
                {
                        if(QueryFlag)
                                StrSql+=" and MName like  '%"+Edit3->Text.Trim()+"%'";
                        else
                                StrSql+=" where MName like  '%"+Edit3->Text.Trim()+"%'";
                        QueryFlag=true;
                }
        }
        return  StrSql;
}

void __fastcall TForm6::LoadAllMedia()
{
        //TODO: Add your source code here
        LoadMediaName("",ListView1);
}
void __fastcall TForm6::Edit2Change(TObject *Sender)
{
       LoadAllMedia();
}
//---------------------------------------------------------------------------

void __fastcall TForm6::Button2Click(TObject *Sender)
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
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm6::AddToListBox2(TListItem       *ItemTemp)
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
        ComboBox1->Items->Add(ItemTemp->Caption);

        //ComboBox2->Items->Add(ItemTemp->Caption);
        ComboBox3->Items->Add(ItemTemp->Caption);
        //ComboBox5->Items->Add(ItemTemp->Caption);
        //ComboBox7->Items->Add(ItemTemp->Caption);
        //ComboBox8->Items->Add(ItemTemp->Caption);
        ComboBox9->Items->Add(ItemTemp->Caption);
        Item->Data=ItemTemp->Data;
        Item->ImageIndex=ItemTemp->ImageIndex;
        ListView2->Items->EndUpdate();
}
void __fastcall TForm6::Button3Click(TObject *Sender)
{
        TListItem       *Item;
        for(int i=0;i<ListView1->Items->Count;i++)
        {
               Item=ListView1->Items->Item[i];
               if(Item!=NULL)
                        AddToListBox2(Item);
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm6::Button4Click(TObject *Sender)
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
                UpdateComboBox(Caption);
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm6::Button5Click(TObject *Sender)
{
       ListView2->Items->Clear();
       ComboBox1->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TForm6::ListView2DragDrop(TObject *Sender, TObject *Source,
      int X, int Y)
{
        //ShowMessage("xxx");
        //Button2Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm6::ListView2DragOver(TObject *Sender, TObject *Source,
      int X, int Y, TDragState State, bool &Accept)
{
        Button2Click(Sender);
}
//---------------------------------------------------------------------------


void __fastcall TForm6::UpdateComboBox(AnsiString Caption)
{
        //TODO: Add your source code here
        for(int i=0;i<ComboBox1->Items->Count;i++)
        {
                if(ComboBox1->Items->Strings[i]==Caption)
                {
                        ComboBox1->Items->Delete(i);
                        //ComboBox2->Items->Delete(i);
                        ComboBox3->Items->Delete(i);
                        //ComboBox5->Items->Delete(i);
                        //ComboBox7->Items->Delete(i);
                        //ComboBox8->Items->Delete(i);
                        ComboBox9->Items->Delete(i);
                        return;
                }
        }
}
void __fastcall TForm6::Button7Click(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------

void __fastcall TForm6::ListView2DblClick(TObject *Sender)
{
        if(Form10!=NULL)
        {
                Form10->EditMediaInfo(ListView2);
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm6::Button6Click(TObject *Sender)
{
        AnsiString      StrSql;
        AnsiString      StrTemp;
        double          DBTemp;
        
        if(DateTimePicker1->Date<DateTimePicker4->Date)
        {
        if(Edit1->Text!="")
        {
                
                if(ListView2->Items->Count>0)
                {
                      AddToDownloadList("",true);
                      AddToDownloadList("Self",false);
                      if(ShowType==1)//添加新节目单
                      {
                                StrSql="insert into MediaList(MName,MediaIDList,WinType,LRRate,LRRateSec,TBRate,Begin_Time,End_Time)Values('";
                                StrSql+=Edit1->Text.Trim();
                                StrSql+="','";
                                StrSql+=GetMediaList();
                                StrSql+="',";
                                StrSql+="1,0.1,0.1,0.1,";


                                //DateTimePicker1->Time=DateTimePicker2->Time;
                                StrSql+="'";
                                StrSql+=DateTimePicker1->Date.DateString();
                                StrSql+="','";
                                //DateTimePicker4->Time=DateTimePicker3->Time;
                                StrSql+=DateTimePicker4->Date.DateString();
                                StrSql+="')";
                                DataModule1->InitAdoQuery(DataModule1->ADOQuery1,StrSql);
                                DataModule1->ADOQuery1->ExecSQL();
                                StoreMediaInfo();
                       }
                       else     if(ShowType==2)//修改节目单
                                {       //MName,MediaIDList,WinType,LRRate,LRRateSec,TBRate,Begin_Time,End_Time
                                        StrSql="update MediaList set MName='";
                                        StrSql+=Edit1->Text.Trim();
                                        StrSql+="',MediaIDList='";
                                        StrSql+=GetMediaList();
                                        StrSql+="',WinType=";
                                        StrSql+="1,LRRate=0.1,LRRateSec=0.1,TBRate=0.1,";
                                        StrSql+="Begin_Time=";
                                        //DateTimePicker1->Time=DateTimePicker2->Time;
                                        StrSql+="'";
                                        StrSql+=DateTimePicker1->Date.DateString();
                                        StrSql+="',End_Time='";
                                        //DateTimePicker4->Time=DateTimePicker3->Time;
                                        StrSql+=DateTimePicker4->Date.DateString();
                                        StrSql+="'";
                                        StrSql+=" where ID="+IntToStr(MediaID);
                                        DataModule1->InitAdoQuery(DataModule1->ADOQuery1,StrSql);
                                        DataModule1->ADOQuery1->ExecSQL();
                                        StoreMediaInfo();
                                }
                        StoreFlag=true;
                        Close();
                }
                else
                {
                        MessageBox(Handle,"请至少选择一个媒体文件!","系统提示",MB_OK);
                        return;
                }
        }
        else
        {
                MessageBox(Handle,"请输入节目单名称!","系统提示",MB_OK);
                return;
        }
        }
        else
        {
                MessageBox(Handle,"起始时间应早于终止时间，请重新设置!","系统提示",MB_OK);
                return;
        }
        
        

}
//---------------------------------------------------------------------------


AnsiString __fastcall TForm6::GetMediaList()
{
        //TODO: Add your source code here
        AnsiString      StrTemp;
        ListViewNodeDat *DaTemp;
        for(int i=0;i<ListView2->Items->Count;i++)
        {
               DaTemp=(ListViewNodeDat *)(ListView2->Items->Item[i]->Data);
               if(DaTemp!=NULL)
               {
                        if(StrTemp=="")
                                StrTemp+=IntToStr(DaTemp->ID);
                        else
                                StrTemp+=","+IntToStr(DaTemp->ID);
               }
        }
        return StrTemp;
}
//保存窗口对应信息
BOOL __fastcall TForm6::StoreMediaInfo()
{
        //TODO: Add your source code here
        AnsiString      StrTemp;
        AnsiString      CurrDir;
        TDateTime       DTFrom,DTEnd;
        int             IndexTemp;
        TForm7          *FrmTemp;
        double          DBTemp=0.1;

        CurrDir=GetCfgFileName();
        if(_access(CurrDir.c_str(),0)==0)
                DeleteFile(CurrDir);
        AddToDownloadList(CurrDir,false);
        StrTemp="1";


        DTFrom=DateTimePicker1->Date;
        DTEnd=DateTimePicker4->Date;

        WritePrivateProfileString("Time","From",DTFrom.DateString().c_str(),CurrDir.c_str());
        WritePrivateProfileString("Time","End",DTEnd.DateString().c_str(),CurrDir.c_str());
        WritePrivateProfileString("WindowCfg","WindowType",StrTemp.c_str(),CurrDir.c_str());
        /*
        for(int i=1;i<=ChildNums;i++)
        {
                StrTemp="000"+IntToStr(i);
                FrmTemp=DividWnd[i];
                if(FrmTemp!=NULL)
                      {
                                WritePrivateProfileString(StrTemp.c_str(),"MediaIndex",IntToStr(FrmTemp->MediaIndex).c_str(),CurrDir.c_str());
                                MakeMediaList(FrmTemp->MediaIndex);
                      }
        }
        */
        //壁纸
        WritePrivateProfileString("DesktopPic","MediaIndex","0",CurrDir.c_str());
        if(ComboBox1->Text!="")
        {
              IndexTemp=GetIndexByMediaName(ComboBox1->Text);
              if(IndexTemp!=0)
              {
                       WritePrivateProfileString("DesktopPic","MediaIndex",IntToStr(IndexTemp).c_str(),CurrDir.c_str());
                       if(RadioButton1->Checked)
                       {
                               WritePrivateProfileString("DesktopPic","TypeIndex","1",CurrDir.c_str());
                       }
                       else
                       {
                               WritePrivateProfileString("DesktopPic","TypeIndex","2",CurrDir.c_str());
                       }
                       MakeMediaList(IndexTemp);
              }
        }
        //桌面背景播放
        /*
        WritePrivateProfileString("BGPLAY","MediaIndex","0",CurrDir.c_str());
        if(ComboBox2->Text!="")
        {
              IndexTemp=GetIndexByMediaName(ComboBox2->Text);
              if(IndexTemp!=0)
              {
                       WritePrivateProfileString("BGPLAY","MediaIndex",IntToStr(IndexTemp).c_str(),CurrDir.c_str());
                       MakeMediaList(IndexTemp);
              }
        }*/
        TDateTime       TimeTemp;

        //弹出窗口
        WritePrivateProfileString("DISPWND","MediaIndex","0",CurrDir.c_str());
        if(ComboBox3->Text!="")
        {
              IndexTemp=GetIndexByMediaName(ComboBox3->Text);
              if(IndexTemp!=0)
              {
                       WritePrivateProfileString("DISPWND","MediaIndex",IntToStr(IndexTemp).c_str(),CurrDir.c_str());
                       if(RadioButton3->Checked)
                       {
                                WritePrivateProfileString("DISPWND","DispType","1",CurrDir.c_str());
                                TimeTemp=DateTimePicker2->DateTime;
                                WritePrivateProfileString("DISPWND","DispTime",TimeTemp.TimeString().c_str(),CurrDir.c_str());
                       }
                       else
                       {
                                WritePrivateProfileString("DISPWND","DispType","2",CurrDir.c_str());
                                WritePrivateProfileString("DISPWND","DispTime",IntToStr(ComboBox4->ItemIndex).c_str(),CurrDir.c_str());
                       }
                       MakeMediaList(IndexTemp);
              }
        }
        //桌面扩展工具条
        /*
        WritePrivateProfileString("DeskBar","MediaIndex","0",CurrDir.c_str());
        if(ComboBox5->Text!="")
        {
              IndexTemp=GetIndexByMediaName(ComboBox5->Text);
              if(IndexTemp!=0)
              {
                       WritePrivateProfileString("DeskBar","MediaIndex",IntToStr(IndexTemp).c_str(),CurrDir.c_str());
                       WritePrivateProfileString("DeskBar","Position",IntToStr(ComboBox6->ItemIndex).c_str(),CurrDir.c_str());

                       if(Edit5->Text!="")
                       {
                             WritePrivateProfileString("DeskBar","Height",Edit5->Text.c_str(),CurrDir.c_str());
                       }
                       if(Edit6->Text!="")
                       {
                             WritePrivateProfileString("DeskBar","Width",Edit6->Text.c_str(),CurrDir.c_str());
                       }
                       MakeMediaList(IndexTemp);
              }
        } */
        //IE首页
        WritePrivateProfileString("HostPage","PageURL","",CurrDir.c_str());
        if(Edit4->Text!="")
        {
                       WritePrivateProfileString("HostPage","PageURL",Edit4->Text.c_str(),CurrDir.c_str());
        }
        //定向本地视频
        /*
        if(ComboBox8->Text!="")
        {
              IndexTemp=GetIndexByMediaName(ComboBox8->Text);
              if(IndexTemp!=0)
              {
                       WritePrivateProfileString("LOCALVIDEO","MediaIndex",IntToStr(IndexTemp).c_str(),CurrDir.c_str());
                       MakeMediaList(IndexTemp);
              }
        } */
        //硬盘图片
        WritePrivateProfileString("HardDiskPic","MediaIndex","0",CurrDir.c_str());
        if(ComboBox9->Text!="")
        {
              IndexTemp=GetIndexByMediaName(ComboBox9->Text);
              if(IndexTemp!=0)
              {
                       WritePrivateProfileString("HardDiskPic","MediaIndex",IntToStr(IndexTemp).c_str(),CurrDir.c_str());
                       MakeMediaList(IndexTemp);
              }
        }
}
void __fastcall TForm6::ComboBox1Change(TObject *Sender)
{
        TListItem       *ItemTemp;
        AnsiString      StrTemp;
        ListViewNodeDat *DaTemp;
        int             ResourceType;

        BOOL            FindFlag=false;
        StrTemp=ComboBox1->Text;
        if(StrTemp!="")
        {
                ResourceType=GetTypeByName(StrTemp);
                if(ResourceType==0)//数据库中不存在该资源
                {
                        ShowMessage("请选择列表中的媒体，输入无效！");
                        ComboBox1->SetFocus();
                }
                else
                {
                        if(ResourceType!=2)
                        {
                             ShowMessage("壁纸只支持图片类型，请重新选择！");
                             ComboBox1->SetFocus();
                        }

                }
        }
}
//---------------------------------------------------------------------------


AnsiString __fastcall TForm6::GetCfgFileName()
{
        //TODO: Add your source code here
        AnsiString      CurrDir;
        CurrDir=ExtractFilePath(Application->ExeName);
        CurrDir+="\\MediaList\\";
        CreateDirectory(CurrDir.c_str(),NULL);
        CurrDir+=Edit1->Text.Trim()+"\\";
        CreateDirectory(CurrDir.c_str(),NULL);
        CurrDir+="WndSet.ini";
        return CurrDir;
}
//生成对应的媒体配置文件
void __fastcall TForm6::MakeMediaList(int MediaID)
{
        //TODO: Add your source code here
        AnsiString      StrSql;
        AnsiString      CfgDir;
        AnsiString      MediaName;
        char            CfgLabel[12];
        char            NumTemp[10];
        int             MediaType;
        int             TypeTemp;
        memset(CfgLabel,0x00,sizeof(CfgLabel));
        memset(NumTemp,0x00,sizeof(NumTemp));

        if(MediaID!=0)
        {
                CfgDir=GetCfgFileName();
                StrSql="select * from MediaInfo where ID="+IntToStr(MediaID);
                DataModule1->InitAdoQuery(DataModule1->ADOQuery2,StrSql);
                DataModule1->ADOQuery2->Open();
                if(DataModule1->ADOQuery2->RecordCount>0)
                {
                        sprintf(NumTemp,"%d",MediaID);
                        sprintf(CfgLabel,"%s","10000");
                        sprintf(CfgLabel+5-strlen(NumTemp),"%s",NumTemp);

                        MediaType=DataModule1->ADOQuery2->FieldByName("MType")->Value;
                        WritePrivateProfileString(CfgLabel,"MediaType",(IntToStr(MediaType)).c_str(),CfgDir.c_str());
                        if(!DataModule1->ADOQuery2->FieldByName("MName")->Value.IsNull())
                                MediaName=DataModule1->ADOQuery2->FieldByName("MName")->Value;
                        MediaName=MediaName.Trim();
                        WritePrivateProfileString(CfgLabel,"MediaName",MediaName.c_str(),CfgDir.c_str());

                        if((MediaType==1)||(MediaType==4))
                        {
                                char            Buf[1024];
                                AnsiString      StrTemp;
                                AnsiString      FullName;
                                int             VideoNums=0;
                                int             TotalNums=0;
                                memset(Buf,0x00,sizeof(Buf));
                                memset(NumTemp,0x00,sizeof(NumTemp));
                                if(!DataModule1->ADOQuery2->FieldByName("SFileName")->Value.IsNull())
                                {
                                        FullName=DataModule1->ADOQuery2->FieldByName("SFileName")->Value;
                                        FullName=FullName.Trim();
                                        sprintf(Buf,"%s",FullName);
                                        for(int i=1;i<strlen(Buf);i++)
                                        {
                                                if((Buf[i]!='#')&&(i!=strlen(Buf)-1))
                                                        StrTemp+=Buf[i];
                                                else
                                                {
                                                        VideoNums++;
                                                        GetPrivateProfileString(CfgLabel,"VideoNums","0",NumTemp,sizeof(NumTemp),CfgDir.c_str());
                                                        //TotalNums=StrToInt(NumTemp);
                                                        TotalNums++;
                                                        memset(NumTemp,0x00,sizeof(NumTemp));
                                                        sprintf(NumTemp,"%d",TotalNums);
                                                        WritePrivateProfileString(CfgLabel,"VideoNums",NumTemp,CfgDir.c_str());
                                                        memset(NumTemp,0x00,sizeof(NumTemp));
                                                        sprintf(NumTemp,"%s%d","Video",VideoNums);
                                                        AddToDownloadList(StrTemp,false);
                                                        StrTemp=ExtractFileName(StrTemp);
                                                        WritePrivateProfileString(CfgLabel,NumTemp,StrTemp.c_str(),CfgDir.c_str());
                                                        StrTemp="";
                                                }
                                        }
                                        TypeTemp=DataModule1->ADOQuery2->FieldByName("CBType")->Value;
                                        WritePrivateProfileString(CfgLabel,"CBType",(IntToStr(TypeTemp)).c_str(),CfgDir.c_str());

                                        TypeTemp=DataModule1->ADOQuery2->FieldByName("ScreenType")->Value;
                                        WritePrivateProfileString(CfgLabel,"ScreenType",(IntToStr(TypeTemp)).c_str(),CfgDir.c_str());

                                        TypeTemp=DataModule1->ADOQuery2->FieldByName("SInterval")->Value;
                                        WritePrivateProfileString(CfgLabel,"SInterval",(IntToStr(TypeTemp)).c_str(),CfgDir.c_str());
                                }
                        }
                        else    if(MediaType==2)
                                {
                                        if(!DataModule1->ADOQuery2->FieldByName("SFileName")->Value.IsNull())
                                                MediaName=DataModule1->ADOQuery2->FieldByName("SFileName")->Value;
                                        MediaName=MediaName.Trim();
                                        AddToDownloadList(MediaName,false);
                                        WritePrivateProfileString(CfgLabel,"FilePath",MediaName.c_str(),CfgDir.c_str());
                                        TypeTemp=DataModule1->ADOQuery2->FieldByName("PicType")->Value;
                                        WritePrivateProfileString(CfgLabel,"PicType",(IntToStr(TypeTemp)).c_str(),CfgDir.c_str());
                                        TypeTemp=DataModule1->ADOQuery2->FieldByName("SInterval")->Value;
                                        WritePrivateProfileString(CfgLabel,"SInterval",(IntToStr(TypeTemp)).c_str(),CfgDir.c_str());
                                }
                        else    if(MediaType==3)
                                {
                                        TypeTemp=DataModule1->ADOQuery2->FieldByName("ContentType")->Value;
                                        WritePrivateProfileString(CfgLabel,"ContentType",(IntToStr(TypeTemp)).c_str(),CfgDir.c_str());

                                        if(!DataModule1->ADOQuery2->FieldByName("SFileName")->Value.IsNull())
                                                MediaName=DataModule1->ADOQuery2->FieldByName("SFileName")->Value;
                                        MediaName=MediaName.Trim();
                                        WritePrivateProfileString(CfgLabel,"webURL",MediaName.c_str(),CfgDir.c_str());
                                        if(!DataModule1->ADOQuery2->FieldByName("ReceivePort")->Value.IsNull())
                                                TypeTemp=DataModule1->ADOQuery2->FieldByName("ReceivePort")->Value;
                                        WritePrivateProfileString(CfgLabel,"width",(IntToStr(TypeTemp)).c_str(),CfgDir.c_str());

                                        if(!DataModule1->ADOQuery2->FieldByName("MFontSize")->Value.IsNull())
                                                MediaName=DataModule1->ADOQuery2->FieldByName("MFontSize")->Value;
                                        MediaName=MediaName.Trim();
                                        WritePrivateProfileString(CfgLabel,"Height",MediaName.c_str(),CfgDir.c_str());

                                }
                }
        }
}
//添加文件名称到下载播放列表
void __fastcall TForm6::AddToDownloadList(AnsiString FileName,BOOL  DelFlag)
{
        //TODO: Add your source code here
        char            str[1024];
        FILE            *fp;
        AnsiString      FilePath;

        FilePath=ExtractFilePath(Application->ExeName);
        FilePath+="\\MediaList\\";
        FilePath+=Edit1->Text.Trim()+"\\";

        memset(str,0x00,sizeof(str));
        sprintf(str, "%s\\DownLoad.lis", FilePath);
        if(FileName=="Self")
                FileName=str;
        if(DelFlag)
        {
                if(_access(str,0)==0)
                        DeleteFile(str);
                return;
        }
        fp = fopen(str, "a+");
        if(fp == NULL)
        {
                return;
        }
        memset(str, 0x00, sizeof(str));
        sprintf(str, "%s\n",FileName);
        fputs(str, fp);
        fclose(fp);
}
//根据媒体名称获取媒体ID
int __fastcall TForm6::GetIndexByMediaName(AnsiString MediaName)
{
        //TODO: Add your source code here
        AnsiString      StrSql;
        int             Ret;
        StrSql ="select ID from MediaInfo where MName='"+MediaName+"'";
        DataModule1->InitAdoQuery(DataModule1->ADOQuery1,StrSql);
        DataModule1->ADOQuery1->Open();
        if(DataModule1->ADOQuery1->RecordCount>0)
        {
                Ret=DataModule1->ADOQuery1->FieldByName("ID")->Value;
        }
        else
                Ret=0;
        return  Ret;
}
//读取配置文件
void __fastcall TForm6::GetInitCfg()
{
        //TODO: Add your source code here
        AnsiString      StrTemp;
        AnsiString      CurrDir;
        TDateTime       DTFrom,DTEnd;
        int             IndexTemp;
        TForm7          *FrmTemp;
        double          DBTemp=0.1;
        char            tmp[64];

        CurrDir=GetCfgFileName();
        


        {
              memset(tmp,0x00,sizeof(tmp));
              GetPrivateProfileString("DesktopPic","MediaIndex","0",tmp,sizeof(tmp),CurrDir.c_str());
              IndexTemp=StrToInt(tmp);
              if(IndexTemp!=0)
              {
                       StrTemp=GetNameByMediaIndex(IndexTemp);
                       if(StrTemp!="")
                       {
                                ComboBox1->Text=StrTemp;
                                GetPrivateProfileString("DesktopPic","TypeIndex","0",tmp,sizeof(tmp),CurrDir.c_str());
                                IndexTemp=StrToInt(tmp);
                                if(IndexTemp==1)
                                        RadioButton1->Checked =true;
                                else
                                        RadioButton2->Checked =true;
                       }
              }
        }
        //桌面背景播放
        /*
        ComboBox2->Text="";
        {
              memset(tmp,0x00,sizeof(tmp));
              GetPrivateProfileString("BGPLAY","MediaIndex","0",tmp,sizeof(tmp),CurrDir.c_str());
              IndexTemp=StrToInt(tmp);
              if(IndexTemp!=0)
              {
                       StrTemp=GetNameByMediaIndex(IndexTemp);
                       //WritePrivateProfileString("BGPLAY","MediaIndex",IntToStr(IndexTemp).c_str(),CurrDir.c_str());
                       ComboBox2->Text=StrTemp;
              }
        }*/
        TDateTime       TimeTemp;
        //弹出窗口

        {
              ComboBox3->Text="";
              memset(tmp,0x00,sizeof(tmp));
              GetPrivateProfileString("DISPWND","MediaIndex","0",tmp,sizeof(tmp),CurrDir.c_str());
              IndexTemp=StrToInt(tmp);

              if(IndexTemp!=0)
              {
                       StrTemp=GetNameByMediaIndex(IndexTemp);
                       ComboBox3->Text= StrTemp;

                       memset(tmp,0x00,sizeof(tmp));
                       GetPrivateProfileString("DISPWND","DispType","0",tmp,sizeof(tmp),CurrDir.c_str());
                       IndexTemp=StrToInt(tmp);

                       if(IndexTemp==1)
                       {
                                RadioButton3->Checked=true;
                                memset(tmp,0x00,sizeof(tmp));
                                GetPrivateProfileString("DISPWND","DispTime","12:00:00",tmp,sizeof(tmp),CurrDir.c_str());
                                TimeTemp=StrToTime(tmp);
                                DateTimePicker2->Time=TimeTemp;
                       }
                       else
                       {
                                RadioButton4->Checked=true;
                                memset(tmp,0x00,sizeof(tmp));
                                GetPrivateProfileString("DISPWND","DispTime","12:00:00",tmp,sizeof(tmp),CurrDir.c_str());
                                IndexTemp=StrToInt(tmp);
                                ComboBox4->ItemIndex=IndexTemp;
                       }
              }
        }
        //托盘消息
        {

              //ComboBox5->Text="";
              //ComboBox6->Text="";
              //Edit5->Text="";
              //Edit6->Text="";
              memset(tmp,0x00,sizeof(tmp));
              GetPrivateProfileString("DeskBar","MediaIndex","0",tmp,sizeof(tmp),CurrDir.c_str());
              IndexTemp=StrToInt(tmp);
              /*
              //IndexTemp=GetIndexByMediaName(ComboBox5->Text);
              if(IndexTemp!=0)
              {

                       StrTemp=GetNameByMediaIndex(IndexTemp);
                       ComboBox5->Text= StrTemp;
                       memset(tmp,0x00,sizeof(tmp));
                       GetPrivateProfileString("DeskBar","Position","0",tmp,sizeof(tmp),CurrDir.c_str());
                       IndexTemp=StrToInt(tmp);
                       ComboBox6->ItemIndex=IndexTemp;

                       memset(tmp,0x00,sizeof(tmp));
                       GetPrivateProfileString("DeskBar","Height","0",tmp,sizeof(tmp),CurrDir.c_str());
                       //IndexTemp=StrToInt(tmp);
                       Edit5->Text=tmp;

                       memset(tmp,0x00,sizeof(tmp));
                       GetPrivateProfileString("DeskBar","Width","0",tmp,sizeof(tmp),CurrDir.c_str());
                       //IndexTemp=StrToInt(tmp);
                       Edit6->Text=tmp;

              }*/
        }
        //IE首页
        Edit4->Text="";
        memset(tmp,0x00,sizeof(tmp));
        GetPrivateProfileString("HostPage","PageURL","",tmp,sizeof(tmp),CurrDir.c_str());
        if(strlen(tmp)>0)
        Edit4->Text=tmp;


        //定向本地视频
        /*
        memset(tmp,0x00,sizeof(tmp));
        GetPrivateProfileString("LOCALVIDEO","MediaIndex","0",tmp,sizeof(tmp),CurrDir.c_str());
        IndexTemp=StrToInt(tmp);
        ComboBox8->Text="";
        if(IndexTemp!=0)
        {
             StrTemp=GetNameByMediaIndex(IndexTemp);
             ComboBox8->Text= StrTemp;
        }*/
        //硬盘根目录图片
        memset(tmp,0x00,sizeof(tmp));
        GetPrivateProfileString("HardDiskPic","MediaIndex","0",tmp,sizeof(tmp),CurrDir.c_str());
        IndexTemp=StrToInt(tmp);
        ComboBox9->Text="";
        if(IndexTemp!=0)
        {
             StrTemp=GetNameByMediaIndex(IndexTemp);
             ComboBox9->Text= StrTemp;
        }

}
//根据媒体文件的ID获取名称
AnsiString __fastcall TForm6::GetNameByMediaIndex(int MediaIndex)
{
        //TODO: Add your source code here
        AnsiString      StrSql;
        AnsiString      Ret;
        StrSql ="select MName from MediaInfo where ID="+IntToStr(MediaIndex);
        DataModule1->InitAdoQuery(DataModule1->ADOQuery1,StrSql);
        DataModule1->ADOQuery1->Open();
        if(DataModule1->ADOQuery1->RecordCount>0)
        {
                if(!DataModule1->ADOQuery1->FieldByName("MName")->Value.IsNull())
                Ret=DataModule1->ADOQuery1->FieldByName("MName")->Value;
        }
        else
                Ret="";
        return  Ret;
}
//根据资源名称获取资源类别
int __fastcall TForm6::GetTypeByName(AnsiString ResName)
{
        //TODO: Add your source code here
        AnsiString      StrSql;
        int             Ret;
        StrSql ="select MType from MediaInfo where MName='"+ResName+"'";
        DataModule1->InitAdoQuery(DataModule1->ADOQuery1,StrSql);
        DataModule1->ADOQuery1->Open();
        if(DataModule1->ADOQuery1->RecordCount>0)
        {
                Ret=DataModule1->ADOQuery1->FieldByName("MType")->Value;
        }
        else
                Ret=0;
        return  Ret;
}
void __fastcall TForm6::ComboBox7Change(TObject *Sender)
{
        TListItem       *ItemTemp;
        AnsiString      StrTemp;
        ListViewNodeDat *DaTemp;
        int             ResourceType;
        /*
        BOOL            FindFlag=false;
        StrTemp=ComboBox7->Text;
        if(StrTemp!="")
        {
                ResourceType=GetTypeByName(StrTemp);
                if(ResourceType==0)//数据库中不存在该资源
                {
                        ComboBox7->Text="";
                        ShowMessage("请选择列表中的媒体，输入无效！");
                        ComboBox7->SetFocus();
                }
                else
                {
                        if(ResourceType!=2)
                        {
                             ShowMessage("开机画面只支持图片类型，请重新选择！");
                             ComboBox7->SetFocus();
                        }

                }
        }*/
}
//---------------------------------------------------------------------------

void __fastcall TForm6::ComboBox9Change(TObject *Sender)
{
        TListItem       *ItemTemp;
        AnsiString      StrTemp;
        ListViewNodeDat *DaTemp;
        int             ResourceType;

        BOOL            FindFlag=false;
        StrTemp=ComboBox9->Text;
        if(StrTemp!="")
        {
                ResourceType=GetTypeByName(StrTemp);
                if(ResourceType==0)//数据库中不存在该资源
                {
                        ComboBox9->Text="";
                        ShowMessage("请选择列表中的媒体，输入无效！");
                        ComboBox9->SetFocus();
                }
                else
                {
                        if(ResourceType!=2)
                        {
                             ShowMessage("硬盘画面只支持图片类型，请重新选择！");
                             ComboBox9->SetFocus();
                        }

                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm6::ComboBox8Change(TObject *Sender)
{
        /*
        TListItem       *ItemTemp;
        AnsiString      StrTemp;
        ListViewNodeDat *DaTemp;
        int             ResourceType;

        BOOL            FindFlag=false;
        StrTemp=ComboBox8->Text;
        if(StrTemp!="")
        {
                ResourceType=GetTypeByName(StrTemp);
                if(ResourceType==0)//数据库中不存在该资源
                {
                        ComboBox8->Text="";
                        ShowMessage("请选择列表中的媒体，输入无效！");
                        ComboBox9->SetFocus();
                }
                else
                {
                        if((ResourceType!=1)&&(ResourceType!=4))
                        {
                             ShowMessage("定向本地视频支持视频或者flash格式，请重新选择！");
                             ComboBox9->SetFocus();
                        }

                }
        }*/
}
//---------------------------------------------------------------------------

