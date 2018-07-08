//---------------------------------------------------------------------------

#ifndef Unit6H
#define Unit6H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>

#include "Unit7.h"
#include <ComCtrls.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TForm6 : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox3;
        TLabel *Label1;
        TEdit *Edit1;
        TGroupBox *GroupBox4;
        TGroupBox *GroupBox5;
        TButton *Button2;
        TButton *Button3;
        TButton *Button4;
        TButton *Button5;
        TGroupBox *GroupBox6;
        TCheckBox *CheckBox1;
        TCheckBox *CheckBox2;
        TCheckBox *CheckBox3;
        TCheckBox *CheckBox4;
        TLabel *Label2;
        TEdit *Edit2;
        TGroupBox *GroupBox7;
        TLabel *Label3;
        TCheckBox *CheckBox5;
        TCheckBox *CheckBox6;
        TCheckBox *CheckBox7;
        TCheckBox *CheckBox8;
        TEdit *Edit3;
        TListView *ListView1;
        TImageList *ImageList1;
        TListView *ListView2;
        TButton *Button6;
        TButton *Button7;
        TGroupBox *GroupBox9;
        TLabel *Label6;
        TLabel *Label7;
        TDateTimePicker *DateTimePicker1;
        TDateTimePicker *DateTimePicker4;
        TGroupBox *GroupBox1;
        TRadioButton *RadioButton1;
        TRadioButton *RadioButton2;
        TLabel *Label4;
        TComboBox *ComboBox1;
        TGroupBox *GroupBox8;
        TLabel *Label8;
        TComboBox *ComboBox3;
        TGroupBox *GroupBox10;
        TRadioButton *RadioButton3;
        TDateTimePicker *DateTimePicker2;
        TRadioButton *RadioButton4;
        TComboBox *ComboBox4;
        TGroupBox *GroupBox14;
        TEdit *Edit4;
        TGroupBox *GroupBox16;
        TLabel *Label12;
        TComboBox *ComboBox9;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall RadioButton5Click(TObject *Sender);
        void __fastcall Edit2Change(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall ListView2DragDrop(TObject *Sender, TObject *Source,
          int X, int Y);
        void __fastcall ListView2DragOver(TObject *Sender, TObject *Source,
          int X, int Y, TDragState State, bool &Accept);
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall ListView2DblClick(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall ComboBox1Change(TObject *Sender);
        void __fastcall ComboBox7Change(TObject *Sender);
        void __fastcall ComboBox9Change(TObject *Sender);
        void __fastcall ComboBox8Change(TObject *Sender);
private:	// User declarations
public:		// User declarations
        int     SelIndex;//当前选定的子窗口
        BOOL    StoreFlag;//保存标志
        int     ShowType;//1:添加；2：修改
        int     MediaID;
        int     ListNodeCount;
        __fastcall TForm6(TComponent* Owner);
        void __fastcall InitFormState();

        TForm7 * __fastcall GetChildWnd(int Num, int index);
        void __fastcall ClearChildWnd();
        void __fastcall UpdateWindowState(int SelIndex);
        void __fastcall AddToWndList(TForm7 * ForTemp);
        void __fastcall ClearSplitList();
        void __fastcall AddSplitter(int Flag);
        void __fastcall LoadMediaName(AnsiString SqlTemp, TListView * ListView);
        AnsiString __fastcall GetSqlExt(BOOL    Flag);
        void __fastcall LoadAllMedia();
        void __fastcall AddToListBox2(TListItem       *ItemTemp);
        void __fastcall UpdateComboBox(AnsiString Caption);
        AnsiString __fastcall GetMediaList();
        BOOL __fastcall StoreMediaInfo();
        AnsiString __fastcall GetCfgFileName();
        void __fastcall MakeMediaList(int MediaID);
        void __fastcall AddToDownloadList(AnsiString FileName,BOOL  DelFlag);
        int __fastcall GetIndexByMediaName(AnsiString MediaName);
        void __fastcall GetInitCfg();
        AnsiString __fastcall GetNameByMediaIndex(int MediaIndex);
        int __fastcall GetTypeByName(AnsiString ResName);

};
//---------------------------------------------------------------------------
extern PACKAGE TForm6 *Form6;
//---------------------------------------------------------------------------
#endif
