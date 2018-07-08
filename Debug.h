#ifndef DEBUGH
#define DEBUGH
//---------------------------------------------------------------------------
#include <vcl.h>

#define DEBUG

class Sh_Err
{
private:
        int             nflag;          //是否写文件
        AnsiString      sMsgFile;       //消息文件名
        AnsiString      sErrFile;       //错误文件名

public:
        Sh_Err();
        ~Sh_Err();

        void    SetMsgFile(AnsiString sFile);   //指定记录消息文件名
        void    ShowMsg(int i);                 //显示整数
        void    ShowMsg(AnsiString sMsg);       //显示指定消息
        void    WriteMsg(AnsiString sMsg);      //记录消息
        void    RemoveMsgFile(void);            //删除消息文件

        void    SetErrFile(AnsiString sFile);   //指定记录错误信息的文件名
        void    ShowErr(int i);                 //显示整数
        void    ShowErr(AnsiString sMsg);       //显示指定错误
        void    WriteErr(AnsiString sErr);      //记录错误
        void    RemoveErrFile(void);            //删除错误文件
};
extern Sh_Err   MonitorErr;
//---------------------------------------------------------------------------
#endif
