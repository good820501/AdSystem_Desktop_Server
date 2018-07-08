//---------------------------------------------------------------------------

#ifndef Unit14H
#define Unit14H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TForm14 : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox4;
        TListView *ListView1;
        TButton *Button2;
        TButton *Button3;
        TButton *Button4;
        TButton *Button5;
        TGroupBox *GroupBox5;
        TGroupBox *GroupBox7;
        TLabel *Label3;
        TCheckBox *CheckBox5;
        TCheckBox *CheckBox6;
        TCheckBox *CheckBox7;
        TCheckBox *CheckBox8;
        TEdit *Edit3;
        TListView *ListView2;
        TImageList *ImageList2;
        TButton *Button1;
        TButton *Button6;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall ListView2DragOver(TObject *Sender, TObject *Source,
          int X, int Y, TDragState State, bool &Accept);
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        int             MediaListID;
        BOOL            StoreFlag;//true:±£´æ;false:²»±£´æ
        AnsiString      OldTerminalList;
        AnsiString      NewTerminalList;
        __fastcall TForm14(TComponent* Owner);
        void __fastcall LoadSelTermList();
        void __fastcall LoadTotalTerm();
        void __fastcall AddToListBox2(TListItem       *ItemTemp);
        AnsiString __fastcall GetTerminalList();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm14 *Form14;
//---------------------------------------------------------------------------
#endif
