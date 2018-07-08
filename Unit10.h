//---------------------------------------------------------------------------

#ifndef Unit10H
#define Unit10H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------

struct ListViewNodeDat
{
       int              ID;//记录标示
       int              MType;//媒体类型
};
ListViewNodeDat ListViewNodeList[256];

class TForm10 : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TCheckBox *CheckBox1;
        TCheckBox *CheckBox2;
        TCheckBox *CheckBox3;
        TCheckBox *CheckBox4;
        TGroupBox *GroupBox2;
        TListView *ListView1;
        TImageList *ImageList1;
        TPopupMenu *PopupMenu1;
        TMenuItem *A1;
        TMenuItem *M1;
        TMenuItem *D1;
        TMenuItem *R1;
        TImageList *ImageList2;
        TMenuItem *N1;
        TMenuItem *N2;
        TMenuItem *T1;
        TMenuItem *N3;
        TMenuItem *N4;
        TMenuItem *N5;
        TMenuItem *N6;
        TMenuItem *L1;
        void __fastcall PopupMenu1Popup(TObject *Sender);
        void __fastcall A1Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall CheckBox1Click(TObject *Sender);
        void __fastcall R1Click(TObject *Sender);
        void __fastcall N2Click(TObject *Sender);
        void __fastcall T1Click(TObject *Sender);
        void __fastcall M1Click(TObject *Sender);
        void __fastcall D1Click(TObject *Sender);
        void __fastcall L1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm10(TComponent* Owner);
        int        OrderType;//排序类型：1：按名称；2：按类型；
        AnsiString __fastcall GetFullFileNameExt(TListBox * ListBox);
        void __fastcall LoadMediaInfo(AnsiString       StrSql,TListView * ListView);
        AnsiString __fastcall GetSqlExt();
        void __fastcall GetFileSourceName(AnsiString FullName,TListBox *ListBox);
        void __fastcall DelMediaInfo(int ID);
        bool __fastcall EditMediaInfo(TListView * ListView1);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm10 *Form10;
//---------------------------------------------------------------------------
#endif
