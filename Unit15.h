//---------------------------------------------------------------------------

#ifndef Unit15H
#define Unit15H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "SockFunc.h"


struct TerminalList
{
        int             TerID;
        AnsiString      IP;
        AnsiString      MediaName;
        int             MediaListID;    //ý���б�ID
        int             DispNums;       //�����ͻ�������
        BOOL            Login;          //��¼�ɹ�
        BOOL            DLSuccess;      //�Ƿ��������
        TerminalList    *PNext;         //��һλ��
};
//---------------------------------------------------------------------------
class TForm15 : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TTimer *Timer1;
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
        SOCKET          serverfd;               //����Socket�˿�
        TerminalList    *PHead;                 //�ͻ�������ͷ
        TerminalList    *PNow;                 //�ͻ�������ǰλ��
        int             TerminalCount;
        __fastcall TForm15(TComponent* Owner);
        void __fastcall StartSocketService();
        void __fastcall InitTerminalList();
        void __fastcall ClearTerminalList();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm15 *Form15;
//---------------------------------------------------------------------------
#endif
