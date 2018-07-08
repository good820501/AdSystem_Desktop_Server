#include <stdio.h>
#include "Debug.h"

#include "Libs.h"
//---------------------------------------------------------------------------

Sh_Err   MonitorErr;
//---------------------------------------------------------------------------

//指定默认记录文件
Sh_Err::Sh_Err()
{
        char            buf[256];
        SYSTEMTIME	systime;

	memset(&systime, 0x00, sizeof(systime));
	GetLocalTime(&systime);

        nflag = GetCfgInt("Log", "WriteLog", 0);

        memset(buf, 0x00, sizeof(buf));
        sprintf(buf, ".\\log\\PDJServer%04d%02d", systime.wYear, systime.wMonth);
        sMsgFile = (AnsiString)buf + ".log";
        sErrFile = (AnsiString)buf + ".err";

        CreateDirectory(".\\log", NULL);
}
//---------------------------------------------------------------------------
Sh_Err::~Sh_Err()
{
        //把消息临时文件删除
//        RemoveMsgFile();
}
//---------------------------------------------------------------------------
//指定消息记录文件
void    Sh_Err::SetMsgFile(AnsiString sFile)
{
        sMsgFile = sFile;
}
//---------------------------------------------------------------------------
//用消息框显示整数内容，在正式版中不出现消息框
void    Sh_Err::ShowMsg(int i)
{
        char    str[16];
        sprintf(str,"%u",i);
        ShowMsg(str);
}
//---------------------------------------------------------------------------
//用消息框显示消息内容，在正式版中不显示消息框
void    Sh_Err::ShowMsg(AnsiString sMsg)
{
        #ifdef DEBUG
                ShowMessage(sMsg);
        #endif
}
//---------------------------------------------------------------------------
//把消息写入文件
void    Sh_Err::WriteMsg(AnsiString sMsg)
{
        if(!nflag){
                return;
        }
        AnsiString sDataTime = DateTimeToStr(Now()) + " ";
        FILE    *fp = fopen(sMsgFile.c_str(),"a+");
        if(fp)
        {
                fputs(sDataTime.c_str(), fp);
                fputs(sMsg.c_str(), fp);
                fputs("\n", fp);
                fclose(fp);
        }
}
//---------------------------------------------------------------------------
//删除消息文件
void    Sh_Err::RemoveMsgFile(void)
{
        DeleteFile(sMsgFile);
}
//---------------------------------------------------------------------------
//指定错误记录文件
void    Sh_Err::SetErrFile(AnsiString sFile)
{
        sErrFile = sFile;
}
//---------------------------------------------------------------------------
//用消息框显示整数内容，在正式版中不出现消息框
void    Sh_Err::ShowErr(int i)
{
        char    str[16];
        sprintf(str,"%u",i);
        ShowErr(str);
}
//---------------------------------------------------------------------------
//用消息框显示错误内容，在正式版中不显示消息框
void    Sh_Err::ShowErr(AnsiString sErr)
{
        #ifdef DEBUG
                ShowMessage(sErr);
        #endif
}
//---------------------------------------------------------------------------
//把错误写入文件
void    Sh_Err::WriteErr(AnsiString sErr)
{
        if(!nflag){
                return;
        }
        FILE    *fp = fopen(sErrFile.c_str(),"a+");
        if(fp)
        {
                fputs(sErr.c_str(),fp);
                fclose(fp);
        }
}
//---------------------------------------------------------------------------
//删除错误文件
void    Sh_Err::RemoveErrFile(void)
{
        DeleteFile(sErrFile);
}
//---------------------------------------------------------------------------



