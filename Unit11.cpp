//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit11.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm11 *Form11;
//---------------------------------------------------------------------------
__fastcall TForm11::TForm11(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TForm11::Button2Click(TObject *Sender)
{
        StoreFlag=false; 
        Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm11::FormCreate(TObject *Sender)
{
        StoreFlag=false;        
}
//---------------------------------------------------------------------------

void __fastcall TForm11::Button1Click(TObject *Sender)
{
        if(Edit1->Text.Trim()!="")
        {
                if(Edit2->Text.Trim()!="")
                {
                      if(Edit3->Text.Trim()!="")
                      {
                                StoreFlag=true;
                                Close();
                      }
                      else
                      {
                                ShowMessage("������˿ں�!");
                                Edit1->SetFocus();
                      }
                }
                else
                {
                        ShowMessage("������IP��ַ!");
                        Edit1->SetFocus();
                }
        }
        else
        {
                ShowMessage("����������!");
                Edit1->SetFocus();
        }
}
//---------------------------------------------------------------------------
 