//---------------------------------------------------------------------------

#ifndef SocketAccessThreadH
#define SocketAccessThreadH
#include <Classes.hpp>
#include "SockFunc.h"
#include "Unit15.h"
//---------------------------------------------------------------------------
struct CmdExecute{
       SOCKET ClientSocket;
       TForm15 *FrmPrc;
};
class TSocketAccessThread : public TThread
{
private:
        CmdExecute      CmeTerminal;
        SOCKET          ClientSocket;
        TForm15         *FrmPrc;
protected:
        void __fastcall Execute();

public:

        __fastcall TSocketAccessThread(bool CreateSuspended,SOCKET ClientSocket,TForm15 *FrmTemp);
};
DWORD WINAPI TradeEatCard(LPVOID lpParam);
#endif
 