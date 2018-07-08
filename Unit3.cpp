//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit3.h"
#include   <FileCtrl.hpp>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm3::FormShow(TObject *Sender)
{
        StoreFlag=false;        
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Button1Click(TObject *Sender)
{
        if(Edit1->Text.Trim()!="")
        {
                if(Edit2->Text.Trim()!="")
                {
                        StoreFlag=true;
                        Close();
                }
                else
                {
                        ShowMessage("«Î…Ë÷√—≠ª∑Õº∆¨ƒø¬º!");
                }
        }
        else
        {
                ShowMessage("«Î…Ë÷√—≠ª∑Õº∆¨√˚≥∆!");
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Button2Click(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------
void __fastcall TForm3::BitBtn1Click(TObject *Sender)
{
        AnsiString   Dir   =   "C:";
        if  (SelectDirectory(Dir,   TSelectDirOpts()   <<   sdAllowCreate   <<   sdPerformCreate   <<   sdPrompt,1000))
        {
                Edit2->Text = Dir;
        }
}
//---------------------------------------------------------------------------

