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
        int             MediaListID;    //媒体列表ID
        int             DispNums;       //分流客户端数量
        BOOL            Login;          //登录成功
        BOOL            DLSuccess;      //是否下载完成
        TerminalList    *PNext;         //下一位置
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
        SOCKET          serverfd;               //服务Socket端口
        TerminalList    *PHead;                 //客户端链表头
        TerminalList    *PNow;                 //客户端链表当前位置
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
