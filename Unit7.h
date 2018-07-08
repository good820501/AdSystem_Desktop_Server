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
        int     WndIndex;//窗口标示
        int     MediaIndex;
        BOOL    HideFlag;//隐藏标示，表示该窗口是否有效；0-窗口有效；1：窗口无效
        __fastcall TForm7(TComponent* Owner);
        void __fastcall LostFocusPrc();
        void __fastcall OnGetFocus();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm7 *Form7;
//---------------------------------------------------------------------------
#endif
