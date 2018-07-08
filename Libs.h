#ifndef FCLIBS_H
#define FCLIBS_H

#include <vcl.h>

//错误消息
void GetLastErrMsg(char *buf);
void WriteLastErrMsg(void);

//在指定位置贴图，图形是文件
int StretchPicture(TCanvas * Canvas,TRect DispRect,AnsiString FileName);

#define CONFIGFILE	"./SysSet.ini"
int  GetCfgInt(char *lpAppName, char *lpKeyName, int nDefault);
int  GetCfgStr(char *lpAppName, char *lpKeyName, char *lpDefault, char *lpvalue, int nSize);
void SetCfgInt(char *lpAppName, char *lpKeyName, int nValue);
void SetCfgStr(char *lpAppName, char *lpKeyName, char	*lpValue);
void ChangeServerIP(char *buf);

//重起、关机
bool    ChangePrivileges(void);
void    ShutDown(HWND hWnd);
void    Reboot(HWND hWnd);

void SetSystemTime(char *buf);
void GetIniStr(char *req, char *rsp);
void SetIniStr(char *req, char *rsp);
long GetFileData(char *req, char **ppdata);
long GetDBFileData(char *req, char **ppdata);
long GetCfgFileData(char *req, char **ppdata);
void SaveFileDataBin(char *fileinfo, int nfileinfolen, char *rsp);
void SaveFileDataAsc(char *fileinfo, int nfileinfolen, char *rsp);
int  PathOrFile(char *pathfile);
void GetValue(char *buf, char *value, int *start);
//远程启动其他程序
void StartupPlug(char *req, char *rsp);
void ClosePlug(void);

// 时间函数
/*
fmt:
$Y year(0000)	$m month(00)	$d day(00)
$H hour(00)	$M minute(00)	$S second(00)
*******************************************************************************/
char *Sstrftime(char *buf, const size_t maxsize, const char *fmt);

// 加锁
HANDLE GetMutex(LPSTR lpszMutexName, DWORD dwWaitMilliseconds=1000*20);
// 解锁
void FreeMutex(HANDLE &hMutex);

#endif
