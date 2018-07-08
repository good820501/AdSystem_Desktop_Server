#include <stdio.h>
#include "Debug.h"

#include "Libs.h"
//---------------------------------------------------------------------------

Sh_Err   MonitorErr;
//---------------------------------------------------------------------------

//ָ��Ĭ�ϼ�¼�ļ�
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
        //����Ϣ��ʱ�ļ�ɾ��
//        RemoveMsgFile();
}
//---------------------------------------------------------------------------
//ָ����Ϣ��¼�ļ�
void    Sh_Err::SetMsgFile(AnsiString sFile)
{
        sMsgFile = sFile;
}
//---------------------------------------------------------------------------
//����Ϣ����ʾ�������ݣ�����ʽ���в�������Ϣ��
void    Sh_Err::ShowMsg(int i)
{
        char    str[16];
        sprintf(str,"%u",i);
        ShowMsg(str);
}
//---------------------------------------------------------------------------
//����Ϣ����ʾ��Ϣ���ݣ�����ʽ���в���ʾ��Ϣ��
void    Sh_Err::ShowMsg(AnsiString sMsg)
{
        #ifdef DEBUG
                ShowMessage(sMsg);
        #endif
}
//---------------------------------------------------------------------------
//����Ϣд���ļ�
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
//ɾ����Ϣ�ļ�
void    Sh_Err::RemoveMsgFile(void)
{
        DeleteFile(sMsgFile);
}
//---------------------------------------------------------------------------
//ָ�������¼�ļ�
void    Sh_Err::SetErrFile(AnsiString sFile)
{
        sErrFile = sFile;
}
//---------------------------------------------------------------------------
//����Ϣ����ʾ�������ݣ�����ʽ���в�������Ϣ��
void    Sh_Err::ShowErr(int i)
{
        char    str[16];
        sprintf(str,"%u",i);
        ShowErr(str);
}
//---------------------------------------------------------------------------
//����Ϣ����ʾ�������ݣ�����ʽ���в���ʾ��Ϣ��
void    Sh_Err::ShowErr(AnsiString sErr)
{
        #ifdef DEBUG
                ShowMessage(sErr);
        #endif
}
//---------------------------------------------------------------------------
//�Ѵ���д���ļ�
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
//ɾ�������ļ�
void    Sh_Err::RemoveErrFile(void)
{
        DeleteFile(sErrFile);
}
//---------------------------------------------------------------------------



