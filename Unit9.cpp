//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit9.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm9 *Form9;
//---------------------------------------------------------------------------
__fastcall TForm9::TForm9(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm9::Button2Click(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------


void __fastcall TForm9::FormShow(TObject *Sender)
{
        SelFlag=false;        
}
//---------------------------------------------------------------------------

void __fastcall TForm9::ListView1Click(TObject *Sender)
{
        if(ListView1->SelCount>0)
                Button1->Enabled=true;
        else
                Button1->Enabled=false;

}
//---------------------------------------------------------------------------

void __fastcall TForm9::Button1Click(TObject *Sender)
{
        TListItem       *ItempTemp;
        ItempTemp=ListView1->Selected;
        if(ItempTemp!=NULL)
        {
                if(ItempTemp->Caption=="��Ƶ��Ŀ")
                        SelType=1;
                else    if(ItempTemp->Caption=="ѭ��ͼƬ")
                        SelType=2;
                else    if(ItempTemp->Caption=="webҳ��")
                        SelType=3;
                else    if(ItempTemp->Caption=="Flash��ʾ")
                        SelType=4;
                SelFlag=true;
                Close();
        }
}
//---------------------------------------------------------------------------
