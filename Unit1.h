//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//#include "bsSkinCtrls.hpp"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <ToolWin.hpp>
#include "trayicon.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TSplitter *Splitter1;
        TScrollBox *Panel1;
        TTreeView *TreeView1;
        TImageList *ImageList1;
        TMainMenu *MainMenu1;
        TMenuItem *S1;
        TMenuItem *E1;
        TMenuItem *V1;
        TMenuItem *T1;
        TMenuItem *S2;
        TMenuItem *H1;
        TMenuItem *A1;
        TStatusBar *StatusBar1;
        TMenuItem *D1;
        TImageList *ImageList2;
        TToolBar *ToolBar1;
        TToolButton *ToolButton1;
        TToolButton *ToolButton2;
        TToolButton *ToolButton3;
        TToolButton *ToolButton4;
        TToolButton *ToolButton5;
        TToolButton *ToolButton6;
        TTrayIcon *TrayIcon1;
        TImageList *ImageList3;
        TPopupMenu *PopupMenu1;
        TMenuItem *D2;
        TMenuItem *E2;
        TToolButton *ToolButton7;
        TToolButton *ToolButton8;
        TToolButton *ToolButton9;
        void __fastcall E1Click(TObject *Sender);
        void __fastcall TreeView1Change(TObject *Sender, TTreeNode *Node);
        void __fastcall bsSkinSpeedButton1Click(TObject *Sender);
        void __fastcall bsSkinSpeedButton2Click(TObject *Sender);
        void __fastcall bsSkinSpeedButton4Click(TObject *Sender);
        void __fastcall bsSkinSpeedButton3Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall D2Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        void __fastcall TurnPage(AnsiString Text);
        void __fastcall LinkToDatabase();
        void __fastcall ShowDBError();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
