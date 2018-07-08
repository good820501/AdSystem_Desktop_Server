//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm5 *Form5;
//---------------------------------------------------------------------------
__fastcall TForm5::TForm5(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm5::Button1Click(TObject *Sender)
{
        AnsiString      OldDir;
        AnsiString      StrTemp;
        OldDir=ExtractFilePath(Application->ExeName);
        if(MediaType==1)
                OpenDialog1->Filter="Flash�ļ�|*.swf";
        else
                OpenDialog1->Filter="��Ƶ�ļ�|*.avi;*.asf;*.mpeg;*.wm;*.wmv;*.mpg";
        if(OpenDialog1->Execute())
        {
                for(int i=0;i<OpenDialog1->Files->Count;i++)
                {
                        StrTemp=OpenDialog1->Files->Strings[i];
                        ListBox1->Items->Add(StrTemp);
                }
                SetCurrentDir(OldDir);
        }        
}
//---------------------------------------------------------------------------
void __fastcall TForm5::Button5Click(TObject *Sender)
{
        if(MessageBox(Handle,"����ļ��б�ȷ����","ɾ��ȷ��",MB_OKCANCEL)==1)
        {
                ListBox1->Items->Clear();
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm5::FormShow(TObject *Sender)
{
        StoreFlag=false;        
}
//---------------------------------------------------------------------------

void __fastcall TForm5::Button4Click(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------

void __fastcall TForm5::Button3Click(TObject *Sender)
{
        if(Edit1->Text!="")
        {
                if(ListBox1->Items->Count>0)
                {
                        StoreFlag=true;
                        Close();        
                }
                else
                {
                        ShowMessage("��ѡ����Ƶ�ļ�!");
                }
        }
        else
        {
                ShowMessage("��������Ƶ��Ŀ���ƣ�");
                return;
        }        
}
//---------------------------------------------------------------------------

void __fastcall TForm5::Button2Click(TObject *Sender)
{
        int     SelIndex=ListBox1->ItemIndex;
        if(MessageBox(Handle,"ɾ����Flash�ļ���ȷ����","ɾ��ȷ��",MB_OKCANCEL)==1)
        {
                ListBox1->Items->Delete(SelIndex);
        }
}
//---------------------------------------------------------------------------

