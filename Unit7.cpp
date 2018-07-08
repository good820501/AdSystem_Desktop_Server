//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit7.h"
#include "Unit6.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm7 *Form7;
//---------------------------------------------------------------------------
__fastcall TForm7::TForm7(TComponent* Owner)
        : TForm(Owner)
{
      WndIndex=0;
      HideFlag=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm7::FormShow(TObject *Sender)
{
        int     FormHeight,FormWidth;
        int     ImgLeft,ImgTop;

        FormHeight=this->Height/2;
        FormWidth=this->Width/2;

        Image1->Left=FormWidth-Image1->Width/2;
        Image1->Top=FormHeight-Image1->Height/2;

        Image1->Canvas->Brush->Color=clBtnFace;
        Image1->Canvas->FillRect(Image1->ClientRect);
        if(WndIndex==1)
                ImageList1->Draw(Image1->Canvas,0,0,0,true);
        else    if(WndIndex==2)
                ImageList1->Draw(Image1->Canvas,0,0,3,true);
        else    if(WndIndex==3)
                ImageList1->Draw(Image1->Canvas,0,0,4,true);
        else    if(WndIndex==4)
                ImageList1->Draw(Image1->Canvas,0,0,6,true);
        else    if(WndIndex==5)
                ImageList1->Draw(Image1->Canvas,0,0,8,true);
        else    if(WndIndex==6)
                ImageList1->Draw(Image1->Canvas,0,0,10,true);
        Image1->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TForm7::Panel1Click(TObject *Sender)
{
        //
        if(Form6!=NULL)
                {
                        Form6->UpdateWindowState(WndIndex);
                        Form6->Edit4->Text=IntToStr(WndIndex);

                }
}
//---------------------------------------------------------------------------
void __fastcall TForm7::Panel1Exit(TObject *Sender)
{
        LostFocusPrc();
}
//---------------------------------------------------------------------------
void __fastcall TForm7::FormMouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
        //
}
//---------------------------------------------------------------------------
void __fastcall TForm7::LostFocusPrc()
{
        //TODO: Add your source code here
        Panel1->BevelInner=bvRaised;
        Panel1->BevelOuter=bvRaised;
        Panel1->BorderStyle=bsNone;
        if(WndIndex==1)
                ImageList1->Draw(Image1->Canvas,0,0,0,true);
        else    if(WndIndex==2)
                ImageList1->Draw(Image1->Canvas,0,0,2,true);
        else    if(WndIndex==3)
                ImageList1->Draw(Image1->Canvas,0,0,4,true);
        else    if(WndIndex==4)
                ImageList1->Draw(Image1->Canvas,0,0,6,true);
        else    if(WndIndex==5)
                ImageList1->Draw(Image1->Canvas,0,0,8,true);
        else    if(WndIndex==6)
                ImageList1->Draw(Image1->Canvas,0,0,10,true);
        Image1->Repaint();
}
void __fastcall TForm7::OnGetFocus()
{
        //TODO: Add your source code here
        Panel1->BevelInner=bvLowered;
        Panel1->BevelOuter=bvLowered;
        Panel1->BorderStyle=bsSingle;
        if(WndIndex==1)
                ImageList1->Draw(Image1->Canvas,0,0,1,true);
        else    if(WndIndex==2)
                ImageList1->Draw(Image1->Canvas,0,0,3,true);
        else    if(WndIndex==3)
                ImageList1->Draw(Image1->Canvas,0,0,5,true);
        else    if(WndIndex==4)
                ImageList1->Draw(Image1->Canvas,0,0,7,true);
        else    if(WndIndex==5)
                ImageList1->Draw(Image1->Canvas,0,0,9,true);
        else    if(WndIndex==6)
                ImageList1->Draw(Image1->Canvas,0,0,11,true);
        Image1->Repaint();
        if(Form6!=NULL)
        {
                Form6->SelIndex=WndIndex;
        }
}
void __fastcall TForm7::FormResize(TObject *Sender)
{
        FormShow(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TForm7::Panel1DragOver(TObject *Sender, TObject *Source,
      int X, int Y, TDragState State, bool &Accept)
{
        //
        TListItem       *ItemTemp;
        TListView       *ViewTemp;
        ViewTemp=(TListView  *)Source;
        if(ViewTemp==Form6->ListView2)
        {
                Panel1Click(Sender);
        }
}
//---------------------------------------------------------------------------



void __fastcall TForm7::Panel1DragDrop(TObject *Sender, TObject *Source,
      int X, int Y)
{
        Image1DragDrop(Sender,Source,X,Y);
}
//---------------------------------------------------------------------------

void __fastcall TForm7::Image1DragDrop(TObject *Sender, TObject *Source,
      int X, int Y)
{

        TListItem       *ItemTemp;
        TListView       *ViewTemp;
        ViewTemp=(TListView  *)Source;
        if(ViewTemp==Form6->ListView2)
        {
                ItemTemp=ViewTemp->Selected;
                Form6->ComboBox1->Text=ItemTemp->Caption;
                Form6->ComboBox1Change(Sender);
        }
}
//---------------------------------------------------------------------------

