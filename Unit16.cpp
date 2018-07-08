//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit16.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm16 *Form16;
//---------------------------------------------------------------------------
__fastcall TForm16::TForm16(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TForm16::FormShow(TObject *Sender)
{
        StoreFlag=false;        
}
//---------------------------------------------------------------------------

void __fastcall TForm16::Button2Click(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------

void __fastcall TForm16::Button1Click(TObject *Sender)
{
        if(Edit1->Text!="")
        {
                StoreFlag=true;
                Close();
        }
        else
        {
                ShowMessage("请输入分组名称！");
                Edit1->SetFocus();
        }
}
//---------------------------------------------------------------------------
