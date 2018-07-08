//---------------------------------------------------------------------------

#ifndef Unit7H
#define Unit7H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TForm7 : public TForm
{
__published:	// IDE-managed Components
        TImageList *ImageList1;
        TPanel *Panel1;
        TImage *Image1;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall Panel1Click(TObject *Sender);
        void __fastcall Panel1Exit(TObject *Sender);
        void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall Panel1DragOver(TObject *Sender, TObject *Source,
          int X, int Y, TDragState State, bool &Accept);
        void __fastcall Panel1DragDrop(TObject *Sender, TObject *Source,
          int X, int Y);
        void __fastcall Image1DragDrop(TObject *Sender, TObject *Source,
          int X, int Y);
private:	// User declarations
public:		// User declarations
        int     WndIndex;//���ڱ�ʾ
        int     MediaIndex;
        BOOL    HideFlag;//���ر�ʾ����ʾ�ô����Ƿ���Ч��0-������Ч��1��������Ч
        __fastcall TForm7(TComponent* Owner);
        void __fastcall LostFocusPrc();
        void __fastcall OnGetFocus();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm7 *Form7;
//---------------------------------------------------------------------------
#endif
