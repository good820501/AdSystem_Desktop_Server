#ifndef DEBUGH
#define DEBUGH
//---------------------------------------------------------------------------
#include <vcl.h>

#define DEBUG

class Sh_Err
{
private:
        int             nflag;          //�Ƿ�д�ļ�
        AnsiString      sMsgFile;       //��Ϣ�ļ���
        AnsiString      sErrFile;       //�����ļ���

public:
        Sh_Err();
        ~Sh_Err();

        void    SetMsgFile(AnsiString sFile);   //ָ����¼��Ϣ�ļ���
        void    ShowMsg(int i);                 //��ʾ����
        void    ShowMsg(AnsiString sMsg);       //��ʾָ����Ϣ
        void    WriteMsg(AnsiString sMsg);      //��¼��Ϣ
        void    RemoveMsgFile(void);            //ɾ����Ϣ�ļ�

        void    SetErrFile(AnsiString sFile);   //ָ����¼������Ϣ���ļ���
        void    ShowErr(int i);                 //��ʾ����
        void    ShowErr(AnsiString sMsg);       //��ʾָ������
        void    WriteErr(AnsiString sErr);      //��¼����
        void    RemoveErrFile(void);            //ɾ�������ļ�
};
extern Sh_Err   MonitorErr;
//---------------------------------------------------------------------------
#endif
