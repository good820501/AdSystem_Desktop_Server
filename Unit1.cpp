//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit6.h"
#include "Unit8.h"
#include "Unit9.h"
#include "Unit10.h"
#include "Main.h"
#include "DataCtrl.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//#pragma link "bsSkinCtrls"
#pragma link "trayicon"
#pragma resource "*.dfm"
TForm1 *Form1;
TForm *FormTemp=NULL;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::E1Click(TObject *Sender)
{
        Application->Terminate();            
}
//---------------------------------------------------------------------------



void __fastcall TForm1::TurnPage(AnsiString Text)
{
        //TODO: Add your source code here
        if(FormTemp)
        {
                FormTemp->Close();
        }
        FormTemp=NULL;
        if(Text=="编辑节目表")
                {
                        try
                        {
                                if(Form8==NULL)
                                        Form8=new TForm8(Application);
                                FormTemp=Form8;
                        }
                        catch(Exception &exception)
                        {
                                delete Form8;
                                Form8=NULL;
                        }
                }
        else    if(Text=="基本媒体信息")
                {
                        try
                        {
                                if(Form10==NULL)
                                        Form10=new TForm10(Application);
                                 FormTemp=Form10;
                        }
                        catch(Exception &exception)
                        {
                                delete Form10;
                                Form10=NULL;
                        }
                }
        else    if(Text=="管理客户端")
                {
                        try
                        {
                                if(Form12==NULL)
                                        Form12=new TForm12(Application);
                                 FormTemp=Form12;
                        }
                        catch(Exception &exception)
                        {
                                delete Form12;
                                Form12=NULL;
                        }
                }
        else
        {
                
        }
        if(FormTemp!=NULL)
        {
                FormTemp->Parent=Panel1;
                FormTemp->Left=2;
                FormTemp->Top=2;
                FormTemp->Height=Panel1->Height-6;
                FormTemp->Width=Panel1->Width-10;
                Form1->Caption="网吧广告播放管理系统-"+FormTemp->Caption;
                FormTemp->Show();
        }
        else
                Form1->Caption="网吧广告播放管理系统";
}
void __fastcall TForm1::TreeView1Change(TObject *Sender, TTreeNode *Node)
{
        TurnPage(Node->Text);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::bsSkinSpeedButton1Click(TObject *Sender)
{
        /*
        if(Form6!=NULL)
                Form6->ShowModal();*/
}
//---------------------------------------------------------------------------

void __fastcall TForm1::bsSkinSpeedButton2Click(TObject *Sender)
{
        if(ToolBar1->Visible)
        {
                ToolBar1->Visible=false;
                T1->Checked=false;
        }
        else
        {
                ToolBar1->Visible=true;
                T1->Checked=true;
                //bsSkinSpeedButton2->Down=true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::bsSkinSpeedButton4Click(TObject *Sender)
{
        if(StatusBar1->Visible)
        {
                StatusBar1->Visible=false;
                S2->Checked=false;
               // bsSkinSpeedButton4->Down=false;
        }
        else
        {
                StatusBar1->Visible=true;
                S2->Checked=true;
               // bsSkinSpeedButton4->Down=true;
        }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::bsSkinSpeedButton3Click(TObject *Sender)
{
        //
        if(Form2!=NULL)
                Form2->ShowModal();       
}
//---------------------------------------------------------------------------


void __fastcall TForm1::LinkToDatabase()
{
        //TODO: Add your source code here
        AnsiString      FullDBName;
        AnsiString      ExeName;

        ExeName=ExtractFilePath(Application->ExeName);
        ExeName+="DB\\OwnData.mdb";

        if(!DataModule1->InitDBLinkWithoutCfg(ExeName))
        {
                ShowDBError();
                //FreeReAndExit();
        }        
}
void __fastcall TForm1::FormCreate(TObject *Sender)
{
        LinkToDatabase();        
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ShowDBError()
{
        //TODO: Add your source code here
       ShowMessage("数据库连接失败，请联系软件供应商解决此问题！");
}
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
        Action=caNone;
        TrayIcon1->Minimize();
        //Application->Minimize();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::D2Click(TObject *Sender)
{
        TrayIcon1->Restore();
        //Application->Restore();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormShow(TObject *Sender)
{
        TrayIcon1->Visible=true;
}
//---------------------------------------------------------------------------



