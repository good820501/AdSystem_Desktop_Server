//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <ToolWin.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
struct TreeNodeDat
{
        int             Flag;//��־���ڵ�Ĳ㼶
        AnsiString      Data;//�ڵ������������
};
struct ListViewNodeDatEx
{
       int              ID;//��¼��ʾ
       int              Flag;
       int              DBType;
       AnsiString       Caption;
       AnsiString       IP;
       AnsiString       Port;
       AnsiString       UserName;
       AnsiString       Password;
       int              NodeType;   //1���ն˽ڵ㣻2���ն˷���

};

class TForm12 : public TForm
{
__published:	// IDE-managed Components
        TImageList *ImageList1;
        TListView *ListView1;
        TPopupMenu *PopupMenu1;
        TMenuItem *A2;
        TMenuItem *R2;
        TPopupMenu *PopupMenu2;
        TMenuItem *A3;
        TMenuItem *C2;
        TMenuItem *R3;
        TMenuItem *O2;
        TMenuItem *L1;
        TMenuItem *F2;
        TMenuItem *P1;
        TMenuItem *S1;
        TMenuItem *T1;
        TMenuItem *G1;
        TMenuItem *P2;
        TMenuItem *E1;
        void __fastcall E1Click(TObject *Sender);
        void __fastcall TreeView1Change(TObject *Sender, TTreeNode *Node);
        void __fastcall S2Click(TObject *Sender);
        void __fastcall T2Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall PopupMenu2Popup(TObject *Sender);
        void __fastcall A3Click(TObject *Sender);
        void __fastcall O2Click(TObject *Sender);
        void __fastcall F2Click(TObject *Sender);
        void __fastcall L1Click(TObject *Sender);
        void __fastcall C2Click(TObject *Sender);
        void __fastcall R3Click(TObject *Sender);
        void __fastcall B1Click(TObject *Sender);
        void __fastcall N1Click(TObject *Sender);
        void __fastcall P1Click(TObject *Sender);
        void __fastcall S1Click(TObject *Sender);
        void __fastcall G1Click(TObject *Sender);
        void __fastcall ListView1DblClick(TObject *Sender);
        void __fastcall P2Click(TObject *Sender);
        void __fastcall ListView1DragDrop(TObject *Sender, TObject *Source,
          int X, int Y);
        void __fastcall ListView1DragOver(TObject *Sender, TObject *Source,
          int X, int Y, TDragState State, bool &Accept);
private:	// User declarations
public:		// User declarations
        int             CurrentRoot;    //��ǰ���ڵ�Ĳ�Σ�0��Ϊ��߲�Σ�����Ϊ��������ı��
        AnsiString      CopName;
        AnsiString      SelOption;//ѡ���ڵ�������ǰ׺
        __fastcall TForm12(TComponent* Owner);
        void __fastcall TurnPage(AnsiString Text);
        void __fastcall InitSysTree();
        void __fastcall LoadDeviceList(AnsiString       SqlTemp,TListView * ListView);
        void __fastcall DeleteDevInfo(int DevID);
        int __fastcall  GetItemCount(int Flag, AnsiString OptionName);
        BOOL __fastcall IsNameRight(AnsiString Name,int ID=0);
        void __fastcall DispGroupDevices(int GroupIndex, TListView * ItemTemp);
        void __fastcall AddUpHandle(TListView * ListView);
        void __fastcall ChangeDeviceGroup(int DeviceID, int GroupID);
        void __fastcall DeleteGroup(int GroupIndex);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm12 *Form12;
//---------------------------------------------------------------------------
#endif
