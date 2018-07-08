//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DataCtrl.h"
#include "Debug.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include "Libs.h"
TDataModule1 *DataModule1;

//---------------------------------------------------------------------------
__fastcall TDataModule1::TDataModule1(TComponent* Owner)
        : TDataModule(Owner)
{
}
//获取数据库连接字符串
/****************************************************
Access:Provider=Microsoft.Jet.OLEDB.4.0;
Jet OLEDB:Database Password=111111;
User ID=admin;Data Source=E:\pdj\ServicePDJ\DB\Statdb.mdb;
Persist Security Info=True

SqlServer:Provider=SQLOLEDB.1;Password=123456;
Persist Security Info=True;User ID=sa;Initial Catalog=Service;
Data Source=2NDSPACE-C3ZRQD

*****************************************************/
AnsiString __fastcall TDataModule1::GetLinkString(int DBType,int HasPass,AnsiString DBName,AnsiString DBServerName,AnsiString DBPass,AnsiString  UserName)
{
        AnsiString      StrSql;
        AnsiString      LinkStr;

        if(DBType==1)//Access
        {
              LinkStr="Provider=Microsoft.Jet.OLEDB.4.0;";
              if(HasPass==1)
              {
                  LinkStr+="Jet OLEDB:Database Password=";
                  LinkStr+=DBPass;
                  LinkStr+=";";
              }
              LinkStr+="User ID=";
              LinkStr+=UserName;
              LinkStr+=";Data Source=";
              LinkStr+=DBName;
              if(HasPass==1)
              {
                        LinkStr+=";Persist Security Info=True";
              }                                            
              else
                        LinkStr+=";Persist Security Info=False";
        }
        else    if(DBType==2)//Sql Server
        {
              LinkStr="Provider=SQLOLEDB.1;Password=";
              LinkStr+=DBPass;
              LinkStr+=";Persist Security Info=True;User ID=";
              LinkStr+=UserName;
              LinkStr+=";Initial Catalog=";
              LinkStr+=DBName;
              LinkStr+=";Data Source=";
              LinkStr+=DBServerName;
        }
        return  LinkStr;

}
//---------------------------------------------------------------------------

//获取数据库配置
void __fastcall TDataModule1::GetDBParams(int &DBType,int &HasPass, AnsiString & DBName, AnsiString & DBPass, AnsiString & UserName)
{
        //TODO: Add your source code here
        char            CfgTemp[256];

        DBType=GetCfgInt("DB","Type",1);
        HasPass=GetCfgInt("DB","HasPass",1);
        memset(CfgTemp,0x00,sizeof(CfgTemp));

        GetCfgStr("DB","DBName","PDJInfo.mdb",CfgTemp,sizeof(CfgTemp));
        DBName=CfgTemp;

        GetCfgStr("DB","User","admin",CfgTemp,sizeof(CfgTemp));
        UserName=CfgTemp;

        GetCfgStr("DB","Password","111111",CfgTemp,sizeof(CfgTemp));
        DBPass=CfgTemp;
}

//测试数据库连接是否有效 :有效返回true;无效返回false;
bool __fastcall TDataModule1::TestDBConn(int  DBType, int  HasPass, AnsiString  DBName,AnsiString DBServerName, AnsiString  DBPass, AnsiString User,AnsiString &ErrorInfo)
{
        //TODO: Add your source code here
       //TODO: Add your source code here
        AnsiString      LinkStr;
        AnsiString      OldLinkStr;
        BOOL            ConnectState;
        LinkStr=GetLinkString(DBType,HasPass,DBName,DBServerName,DBPass,User);
        ConnectState=ADOConnection1->Connected;
        OldLinkStr=ADOConnection1->ConnectionString;
        if(LinkStr=="")
                return false;
        //MonitorErr.WriteMsg("\t\t\t数据库连接测试---LinkStr="+LinkStr);

        ADOConnection1->Connected=false;
        ADOConnection1->ConnectionString=LinkStr;
        try
        {
              ADOConnection1->Connected=true;
        }
        catch(Exception &Exp)
        {
              ADOConnection1->Connected=false;
              ADOConnection1->ConnectionString=OldLinkStr;
              ADOConnection1->Connected=ConnectState;
              ErrorInfo=Exp.Message;
              //MonitorErr.WriteMsg("\t\t\t数据库连接测试---失败:"+Exp.Message);
              return    false;
        }
        ADOConnection1->Connected=false;
        ADOConnection1->ConnectionString=OldLinkStr;
        ADOConnection1->Connected=ConnectState;
        //MonitorErr.WriteMsg("\t\t\t数据库连接测试---成功!");
        return    true;
}
//保存数据库配置
void __fastcall TDataModule1::SetDBParams(int DBType, int HasPass, AnsiString DBName, AnsiString DBPass, AnsiString User)
{
        //TODO: Add your source code here
        SetCfgInt("DB","Type",DBType);
        SetCfgInt("DB","HasPass",DBType);
        SetCfgStr("DB","DBName",DBName.c_str());
        SetCfgStr("DB","User",User.c_str());
        SetCfgStr("DB","Password",DBPass.c_str());
}

void __fastcall TDataModule1::InitAdoQuery(TADOQuery * ADOQuery1, AnsiString StrSql)
{
        //TODO: Add your source code here
        if(ADOQuery1->Active)
                ADOQuery1->Close();
        ADOQuery1->SQL->Clear();
        ADOQuery1->SQL->Add(StrSql);
}
//建立数据库连接，成功返回true，失败返回false；
bool __fastcall TDataModule1::InitDBLink(AnsiString &ErrorMsg)
{
        //TODO: Add your source code here
        int             DBType;
        int             HasPass;
        AnsiString      DBName;
        AnsiString      DBPass;
        AnsiString      UserName;
        AnsiString      StrSql;
        GetDBParams(DBType,HasPass,DBName,DBPass,UserName);
        /*StrSql=GetLinkString(DBType,HasPass,DBName,DBPass,UserName);
        try
        {
                ADOConnection1->Connected=false;
                ADOConnection1->ConnectionString=StrSql;
                ADOConnection1->Connected=true;
                MonitorErr.WriteMsg("\t\t\t初始化数据库连接---成功!");
                return true;
        }
        catch(Exception &Exp)
        {
                ErrorMsg=Exp.Message;
                MonitorErr.WriteMsg("\t\t\t初始化数据库连接---失败:!"+ErrorMsg);
                return false;
        }*/
}

bool __fastcall TDataModule1::InitDBLinkWithoutCfg(AnsiString DBFullName)
{
        //TODO: Add your source code here
        //TODO: Add your source code here
        int             DBType;
        int             HasPass;
        AnsiString      DBName;
        AnsiString      DBPass;
        AnsiString      DBServerName;
        AnsiString      UserName;
        AnsiString      StrSql;
        //GetDBParams(DBType,HasPass,DBName,DBServerName,DBPass,UserName);
        DBType=1;
        HasPass=1;
        DBName=DBFullName;
        DBServerName ="";
        DBPass ="820501";
        UserName="admin";
        StrSql=GetLinkString(DBType,HasPass,DBName,DBServerName,DBPass,UserName);
        try
        {
                ADOConnection1->Connected=false;
                ADOConnection1->ConnectionString=StrSql;
                ADOConnection1->Connected=true;
                //MonitorErr.WriteMsg("\t\t\t初始化数据库连接---成功!");
                return true;
        }
        catch(Exception &Exp)
        {
                //ErrorMsg=Exp.Message;
                //MonitorErr.WriteMsg("\t\t\t初始化数据库连接---失败:!"+ErrorMsg);
                return false;
        }
}
