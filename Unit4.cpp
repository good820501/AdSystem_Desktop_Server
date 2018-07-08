//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit4.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Button2Click(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------
void __fastcall TForm4::FormShow(TObject *Sender)
{
        StoreFlag=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Button1Click(TObject *Sender)
{
        if(Edit1->Text.Trim()!="")
        {


                        if(Edit3->Text!="")
                        {
                                StoreFlag=true;
                                Close();
                        }
                        else
                        {
                                ShowMessage("请输入web页面的URL地址!");
                        }


        }
        else
        {
                ShowMessage("请输入web页面名称!");
        }
}
//---------------------------------------------------------------------------


