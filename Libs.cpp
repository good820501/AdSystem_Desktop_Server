
#include <io.h>
#include <stdio.h>
#include <dir.h>
#include <sys/stat.h>
#include <time.h>
#include "Debug.h"
//#include "DwComm.h"
#include "Libs.h"
//#include "StrLib.h"
#include <Urlmon.h>//添加头文件引用，郭，调用API:URLDownloadToFile
//#include "uPlay.h"
//---------------------------------------------------------------------------

//取错误消息
void GetLastErrMsg(char *buf)
{
        LPVOID lpMsgBuf;
        FormatMessage(
                FORMAT_MESSAGE_ALLOCATE_BUFFER |
                FORMAT_MESSAGE_FROM_SYSTEM |
                FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,
                GetLastError(),
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                (LPTSTR) &lpMsgBuf,
                0,
                NULL
        );
        //MessageBox( NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION );
        // Free the buffer.
        if(buf){
                strcpy(buf, (char *)lpMsgBuf);
        }
        LocalFree( lpMsgBuf );
}
//---------------------------------------------------------------------------

//写错误消息
void WriteLastErrMsg(void)
{
        char    buf[1024];

        GetLastErrMsg(buf);
        //delenter(buf);
        MonitorErr.WriteMsg(buf);
}
//---------------------------------------------------------------------------

//在指定位置贴图，图形是文件
int StretchPicture(TCanvas * Canvas,TRect DispRect,AnsiString FileName)
{
        Graphics::TBitmap *BrushBmp = new Graphics::TBitmap;
        try
        {
                if(FileExists(FileName))
                {
                        BrushBmp->LoadFromFile(FileName);
                        Canvas->StretchDraw(DispRect, BrushBmp);
                }
        }
        __finally
        {
        }
        delete BrushBmp;
        return 0;
}
//---------------------------------------------------------------------------

int GetCfgInt(char *lpAppName, char *lpKeyName, int nDefault)
{
	return GetPrivateProfileInt(lpAppName, lpKeyName, nDefault, CONFIGFILE);
}


int GetCfgStr(char *lpAppName, char *lpKeyName, char *lpDefault, char *lpvalue, int nSize)
{
	return GetPrivateProfileString(lpAppName, lpKeyName, lpDefault, lpvalue, nSize, CONFIGFILE);
}

void SetCfgInt(char *lpAppName, char *lpKeyName, int nValue)
{
	char	str[16];

	sprintf(str, "%d", nValue);
	WritePrivateProfileString(lpAppName, lpKeyName, str, CONFIGFILE);
}

void SetCfgStr(char *lpAppName, char *lpKeyName, char	*lpValue)
{
	WritePrivateProfileString(lpAppName, lpKeyName, lpValue, CONFIGFILE);
}

//---------------------------------------------------------------------------

//修改服务器IP地址参数
void ChangeServerIP(char *buf)
{
        SetCfgStr("Server", "ServIP", buf);
        strcpy(buf, "修改成功");
}
//---------------------------------------------------------------------------

//修改进程权限，使其具有重启、关机权限
bool    ChangeShutdownPrivilege(void)
{
        HANDLE          th;
        HANDLE          handle = GetCurrentProcess();//线程Handle
        if(!OpenProcessToken(handle,TOKEN_WRITE,&th))
        {
                CloseHandle(handle);
                return false;
        }
        CloseHandle(handle);

        TOKEN_PRIVILEGES        tp;
        LUID                    luid;

        tp.PrivilegeCount = 1;
        if(!LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &luid))
        {
                return false;
        }
        tp.Privileges[0].Luid = luid;
        tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

        if(!AdjustTokenPrivileges(th,false,&tp,0,NULL,NULL))
        {
                WriteLastErrMsg();
                return false;
        }
        CloseHandle(th);
        return true;
}
//---------------------------------------------------------------------------

//修改进程权限，使其具有修改时间权限
bool    ChangeChangeTimePrivilege(void)
{
        HANDLE          th;
        HANDLE          handle = GetCurrentProcess();//线程Handle
        if(!OpenProcessToken(handle,TOKEN_WRITE,&th))
        {
                CloseHandle(handle);
                return false;
        }
        CloseHandle(handle);

        TOKEN_PRIVILEGES        tp;
        LUID                    luid;

        tp.PrivilegeCount = 1;
        if(!LookupPrivilegeValue(NULL, SE_SYSTEMTIME_NAME, &luid))
        {
                return false;
        }
        tp.Privileges[0].Luid = luid;
        tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

        if(!AdjustTokenPrivileges(th,false,&tp,0,NULL,NULL))
        {
                WriteLastErrMsg();
                return false;
        }
        CloseHandle(th);
        return true;
}
//---------------------------------------------------------------------------

//关闭机器
void    ShutDown(HWND hWnd)
{
        char    buff[1024];
        OSVERSIONINFO osver;

        osver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
        GetVersionEx(&osver);
        if (osver.dwPlatformId == VER_PLATFORM_WIN32_NT)
        {
                ChangeShutdownPrivilege();
                ExitWindowsEx(EWX_POWEROFF|EWX_FORCE,0);//关机
        }
        else
        {
                ExitWindowsEx(EWX_SHUTDOWN|EWX_FORCE, 0);
        }
}
//---------------------------------------------------------------------------

//重起机器
void    Reboot(HWND hWnd)
{
        char    buff[1024];
        ChangeShutdownPrivilege();
        ExitWindowsEx(EWX_REBOOT|EWX_FORCE,0);//重起机器
        WriteLastErrMsg();
}
//---------------------------------------------------------------------------

//设置系统时间
void    SetSystemTime(char *buf)
{
        int i = 0;
        while(i < 14){
                if(buf[i] < '0' || buf[i] > '9'){
                        strcpy(buf, "01接收到的系统时间格式错误");
                        return;
                }
                i++;
        }

        char    tmp[16];
        SYSTEMTIME      m_newsystime;
        strncpy(tmp, buf, 4);
        tmp[4] = 0;
        m_newsystime.wYear      = atoi(tmp);
        strncpy(tmp, buf+4, 2);
        tmp[2] = 0;
        m_newsystime.wMonth     = atoi(tmp);
        strncpy(tmp, buf+4+2, 2);
        tmp[2] = 0;
        m_newsystime.wDay       = atoi(tmp);
        strncpy(tmp, buf+4+2+2, 2);
        tmp[2] = 0;
        m_newsystime.wHour      = atoi(tmp);
        strncpy(tmp, buf+4+2+2+2, 2);
        tmp[2] = 0;
        m_newsystime.wMinute    = atoi(tmp);
        strncpy(tmp, buf+4+2+2+2+2, 2);
        tmp[2] = 0;
        m_newsystime.wSecond    = atoi(tmp);
        m_newsystime.wMilliseconds = 0;
        ChangeChangeTimePrivilege();
        if(SetLocalTime((CONST SYSTEMTIME *)&m_newsystime)){
                strcpy(buf, "00系统时间更新成功");
        }
        else{
                strcpy(buf, "02系统时间更新错误");
        }
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

int Strcspn( char *res, char *des )
{
    int  len, len0;
    int  i;

    len  = strlen( res );
    len0 = strlen( des );

    for( i=0; i<len; i++ )
    {
        if( i+len0 > len )
            return len;

        if( strncmp( res+i, des, len0 ) == 0 )
            break;
    }

    return i;
}

void DrvWiz16( char *recv )
{
    int  pos, pos0;
    int  endfpno, curfpno;
    char buffer[1024];
    char inipath[256];

    memset( buffer, 0x00, sizeof( buffer ) );
    memset( inipath, 0x00, sizeof( inipath ) );
    strcpy( inipath, "..\\sys\\ini\\jqinfo.ini" );
    endfpno = GetPrivateProfileInt( "printfp", "endfpno", 2, inipath );
    curfpno = GetPrivateProfileInt( "printfp", "currentfpno", 0, inipath );

    if( endfpno - curfpno + 1 > 2 )
    {
        return;
    }

    pos = Strcspn( recv, "|5" );
    if( pos == ( int )strlen( recv ) )
    {
        return;
    }

    pos0 = Strcspn( recv + pos + strlen( "|5" ), "|" );
    memcpy( buffer, recv, pos+3 );
    sprintf( buffer + strlen( buffer ), "603010打印机缺纸%s", recv + pos + strlen( "|5" ) + pos0 );
    sprintf( recv, "%s", buffer );

}
//---------------------------------------------------------------------------

//获取数据文件
long GetDBFileData(char *req, char **ppdata)
{
        AnsiString      FileName;
        char            FilePath[512];
        memset(FilePath,0x00,sizeof(FilePath));
        GetCfgStr("DB","DBName","",FilePath,sizeof(FilePath));
        //sprintf(FilePath,"%s","E:\\SkypeSetup.exe");
        return GetFileData(FilePath,ppdata);
}
//获取配置文件
long GetCfgFileData(char *req, char **ppdata)
{
        //
        AnsiString      FileName;
        char            FilePath[512];
        memset(FilePath,0x00,sizeof(FilePath));
        FileName=GetCurrentDir();
        FileName+="\\PDJServer.ini";
        //GetCfgStr("DB","DBName","",FilePath,sizeof(FilePath));
        sprintf(FilePath,"%s",FileName);
        return GetFileData(FilePath,ppdata);
}
long GetFileData(char *req, char **ppdata)
{
        FILE *fp;
        int  filesize;

        if(access(req, 0 ) == -1)
        {
                *ppdata = (char *)malloc(128);
                if (*ppdata != NULL)
                {
                        memset(*ppdata, 0x00, 128);
                        sprintf(*ppdata, "002901文件不存在");
                }
                return strlen(*ppdata);
        }

        fp = fopen(req, "rb");
        if (fp == NULL)
        {
                *ppdata = (char *)malloc(128);
                if (*ppdata != NULL)
                {
                        memset(*ppdata, 0x00, 128);
                        sprintf(*ppdata, "002902打开文件错误");
                }
                return strlen(*ppdata);
        }
        fseek(fp, 0L, SEEK_END);
        filesize = ftell(fp);
        fseek(fp, 0L, SEEK_SET);

        *ppdata = (char *)malloc(filesize + 18);
        if (*ppdata != NULL)
        {
                memset(*ppdata, 0x00, filesize + 18);
                sprintf(*ppdata+6,"%12d",filesize);
                fread(*ppdata+12+6, 1, filesize, fp);
        }
        fclose(fp);
        return filesize+18;
}


int  PathOrFile(char *pathfile)
{
        int     i;
        char    tmppathfile[256];
	struct _stat status;

        strcpy(tmppathfile, pathfile);
        if (strlen(tmppathfile) <= 0)
        {
                return 0;
        }
        for (i = strlen(tmppathfile)-1; i >= 0 && (tmppathfile[i] == '/' || tmppathfile[i] == '\\'); i--)
        {
                tmppathfile[i] = 0;
        }
	if (_stat(tmppathfile, &status) < 0)/*not path or file*/
	{
		return 0;
	}
	else if ((status.st_mode & S_IFMT) != S_IFDIR)/*File*/
	{
		return 1;
	}
	else/*Directory*/
	{
		return 2;
	}
}

void GetWorkDir(char *prg, char *dir)
{
        int     i;

        strcpy(dir, ".");
        for(i=strlen(prg)-1; i>0; i--)
        {
                if (prg[i] == '/' || prg[i] == '\\')
                {
                        memcpy(dir, prg, i);
                        dir[i] = 0;
                        break;
                }
        }
}

void StartupPlug(char *req, char *rsp)
{
        char    tmp[256];
        char    WinClassName[256];
        char    WinCaption[256];
        char    PathFile[256];
        char    Path[256];
        HWND    hWnd;
        BOOL    b;
        STARTUPINFO si;
        PROCESS_INFORMATION pi;

        memset(tmp, 0x00, sizeof(tmp));
        memset(WinClassName, 0x00, sizeof(WinClassName));
        memset(WinCaption, 0x00, sizeof(WinCaption));
        memset(PathFile, 0x00, sizeof(PathFile));
        memset(Path, 0x00, sizeof(Path));

        if (atoi(req) > GetCfgInt("Plug", "Number", -1))
        {
                strcpy(rsp, "01配置文件中无该编号的程序");
                return;
        }

        sprintf(tmp, "WinClassName%s", req);
        GetCfgStr("Plug", tmp, "NOTFOUND", WinClassName, sizeof(WinClassName));
        if (strcmp(WinClassName, "NOTFOUND") == 0)
        {
                strcpy(rsp, "02程序类名没有定义");
                return;
        }
        sprintf(tmp, "WinCaption%s", req);
        GetCfgStr("Plug", tmp, "NOTFOUND", WinCaption, sizeof(WinCaption));
        if (strcmp(WinCaption, "NOTFOUND") == 0)
        {
                strcpy(rsp, "03程序窗口名没有定义");
                return;
        }
        sprintf(tmp, "PathFile%s", req);
        GetCfgStr("Plug", tmp, "NOTFOUND", PathFile, sizeof(PathFile));
        if (strcmp(PathFile, "NOTFOUND") == 0)
        {
                strcpy(rsp, "04程序路径没有定义");
                return;
        }

        hWnd = FindWindow(WinClassName, WinCaption);
        if (hWnd == NULL)
        {
                ZeroMemory(&si, sizeof(STARTUPINFO));
                si.cb=sizeof(STARTUPINFO);
                ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

                GetWorkDir(PathFile, Path);
                b = CreateProcess(PathFile      //lpApplicationName
                        , NULL                  //lpCommandLine
                        , NULL                  //lpProcessAttributes
                        , NULL                  //lpThreadAttributes
                        , false                 //bInheritHandles
                        , NULL                  //dwCreationFlags
                        , NULL                  //lpEnvironment
                        , Path                  //lpCurrentDirectory
                        , &si                   //lpStartupInfo
                        , &pi);                 //lpProcessInformation

                if (!b)
                {
                        strcpy(rsp, "05启动程序失败");
                        return;
                }
                else
                {
                        CloseHandle(pi.hProcess);
                        CloseHandle(pi.hThread);
                }

                Sleep(1000);
                hWnd = FindWindow(WinClassName, WinCaption);
        }

        if (hWnd)
        {
                SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
                ShowWindow(hWnd, SW_SHOW);
                strcpy(rsp, "00启动程序成功");
        }
        else
        {
                strcpy(rsp, "06没找到程序窗口");
        }
}

void ClosePlug(void)
{
        int     i;
        int     n;
        char    tmp[256];
        char    WinClassName[256];
        char    WinCaption[256];
        HWND    hWnd;
        HANDLE  handle;
        DWORD   dwProcessId;

        n = GetCfgInt("Plug", "Number", -1);
        for (i=1; i<=n; i++)
        {
                memset(tmp, 0x00, sizeof(tmp));
                memset(WinClassName, 0x00, sizeof(WinClassName));
                memset(WinCaption, 0x00, sizeof(WinCaption));

                sprintf(tmp, "WinClassName%d", i);
                GetCfgStr("Plug", tmp, "", WinClassName, sizeof(WinClassName));
                sprintf(tmp, "WinCaption%d", i);
                GetCfgStr("Plug", tmp, "", WinCaption, sizeof(WinCaption));
                hWnd = FindWindow(WinClassName, WinCaption);
                if (hWnd != NULL)
                {
                        GetWindowThreadProcessId(hWnd, &dwProcessId);
                        handle = OpenProcess(PROCESS_TERMINATE|PROCESS_QUERY_INFORMATION, TRUE, dwProcessId);
                        if (handle != NULL)
                        {
                                if (SendMessageTimeout(hWnd, WM_CLOSE, 0, 0, SMTO_NORMAL, 1000*5, NULL) == 0)
                                {
                                        TerminateProcess(handle, 0);
                                }
                                CloseHandle(handle);
                        }
                }
        }
}
//---------------------------------------------------------------------------

/*
fmt:
$Y year(0000)	$m month(00)	$d day(00)
$H hour(00)	$M minute(00)	$S second(00)
*******************************************************************************/
char *Sstrftime(char *buf, const size_t maxsize, const char *fmt)
{
	time_t t;
	struct tm *ptm;
	static char buff[1024];

	time(&t);
	ptm = localtime(&t);
	if(buf == NULL)
        {
		strftime((char *)buff, 1024, fmt, ptm);
		return (char *)buff;
	}
	else
        {
		strftime(buf, maxsize, fmt, ptm);
		return buf;
	}
}
//---------------------------------------------------------------------------

// 加锁
HANDLE GetMutex(LPSTR lpszMutexName, DWORD dwWaitMilliseconds)
{
	DWORD	dwReturn;
	HANDLE	hMutex;

	hMutex = CreateMutex(NULL, FALSE, lpszMutexName);

	if (hMutex == NULL)
	{
		return hMutex;
	}

	dwReturn = WaitForSingleObject(hMutex, dwWaitMilliseconds);

	if (dwReturn == WAIT_OBJECT_0)
	{
		return hMutex;
	}
	else
	{
		ReleaseMutex(hMutex);
		return NULL;
	}
}
//---------------------------------------------------------------------------

// 解锁
void FreeMutex(HANDLE &hMutex)
{
        CloseHandle(hMutex);
        ReleaseMutex(hMutex);
}
//---------------------------------------------------------------------------
void SaveFileDataBin(char *fileinfo, int nfileinfolen, char *rsp)
{
        int     i;
        FILE    *fp;
        char    filename[256];
        char    LenStr[16];
        int     Length;
        i = 0;
        memset(filename, 0x00, sizeof(filename));
        memset(LenStr, 0x00, sizeof(LenStr));
        memcpy(LenStr,fileinfo,12);
        Length=StrToInt(LenStr);
        GetCfgStr("DB","DBName","",filename,sizeof(filename));
        fp = fopen(filename, "wb");
        if (fp == NULL)
        {
                strcpy(rsp, "003101打开文件错误");
                return;
        }
        fwrite(fileinfo+12, 1, Length, fp);
        fclose(fp);
        strcpy(rsp, "003100");
}

void SaveFileDataAsc(char *fileinfo, int nfileinfolen, char *rsp)
{
        int     i;
        FILE    *fp;
        char    filename[256];
        char    LenStr[16];
        int     Length;
        i = 0;
        memset(filename, 0x00, sizeof(filename));
        //GetValue(fileinfo, filename, &i);
        sprintf(filename,"%s%s%s",GetCurrentDir(),"\\","PDJServer.ini");
        memset(LenStr, 0x00, sizeof(LenStr));
        memcpy(LenStr,fileinfo,12);
        Length=StrToInt(LenStr);

        fp = fopen(filename, "wb");
        if (fp == NULL)
        {
                strcpy(rsp, "003101打开文件错误");
                return;
        }
        fwrite(fileinfo+12, 1, Length, fp);
        fclose(fp);
        strcpy(rsp, "003300");
}
/*把字符串左边的空格或制表符删除
*************************************************************************/
char *ltrim(char *source)
{
	int n = 0;

	while(*(source + n) && (*(source + n) == ' ' || *(source + n) == '\t'))
	{
		n++;
	}
	strcpy(source,source+n);
	return source;
}

/*把字符串右边的空格或制表符删除
*************************************************************************/
char *rtrim(char *source)
{
	int	n = strlen(source) - 1;

	if(n < 0) return source;
	
	while((*(source + n ) == ' ' || *(source + n ) == '\t') && n >= 0)
	{
		*(source + n) = 0;
		n--;
	}
	return source;
}
/*把字符串左边和右边的空格或制表符删除
*************************************************************************/
char *trim(char *source)
{
	ltrim(source);
	return rtrim(source);
}
/*从原字符串中取指定起始位置开始
以'|'间隔的字串中的一个字段值,位置自动后移
*************************************************************************/
void GetValue(char *buf, char *value, int *start)
{
        int     len = 0;

        while((unsigned int)(*start+len) < strlen(buf) && buf[*start+len] != '|') len++;
        memcpy(value, buf+*start, len);
        value[len] = 0;
        trim(value);
        *start = *start+len+1;
}
