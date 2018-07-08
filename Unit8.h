//---------------------------------------------------------------------------

#ifndef Unit8H
#define Unit8H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <ImgList.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm8 : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TGroupBox *GroupBox2;
        TListView *ListView1;
        TGroupBox *GroupBox3;
        TListView *ListView2;
        TListView *ListView3;
        TButton *Button1;
        TButton *Button2;
        TButton *Button3;
        TPopupMenu *PopupMenu1;
        TMenuItem *A1;
        TMenuItem *M1;
        TMenuItem *D1;
        TMenuItem *R1;
        TImageList *ImageList1;
        TImageList *ImageList2;
        TPopupMenu *PopupMenu2;
        TMenuItem *E1;
        TMenuItem *R2;
        TSplitter *Splitter1;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall ListView1Click(TObject *Sender);
        void __fastcall ListView2DblClick(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall ListView1Change(TObject *Sender, TListItem *Item,
          TItemChange Change);
        void __fastcall PopupMenu1Popup(TObject *Sender);
        void __fastcall R1Click(TObject *Sender);
        void __fastcall E1Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm8(TComponent* Owner);
        void __fastcall LoadMListFull();
        LoadMediaDetail(AnsiString MediaList,TListView *ListView2);
        void __fastcall LoadTerminalList(int MediaID);
        BOOL __fastcall DeleteListInfo(int ListID, BOOL HintFlag);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm8 *Form8;
//---------------------------------------------------------------------------
#endif
