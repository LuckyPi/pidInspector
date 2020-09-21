/*******************************************************************************************************************************/
// Project: pidInspector 
// Filename: pidInspector.c 
// Description: Aids in vulnerability research by identifying the immediate executing application commonly used in exe/dll hijacking. 
//              pidInspector.exe and pidInspector_dll.dll log the executing DateTime, userID, pI.exe path, pI.exe PID, parent
//              application fullPath, parentPID and if the process has writeAccess to the system folder. The appendable log file is 
//              created in the public writable documents folder C:\\Users\\Public\\Documents\\pidInspector.txt
//              This application makes for a nice way to verify a hijacking condition without having to generate msf/cbs/other payloads.
//              I wanted to try something different, please forgive the butchering of C/C++,
// Usage: Find your suspect hijack using procmon filters. A few I use are "Result | is | Name Not Found, Path | ends with | exe, 
//        Path | ends with | exe, Path | ends with | exe, User | contains | SYSTEM.
// Author: JT, jtestman@gmail.com 
/*******************************************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#include <tlhelp32.h>
#include <Lmcons.h>

// get PPID
DWORD getppid()
{
    HANDLE hSnapshot;
    PROCESSENTRY32 pe32;
    DWORD ppid = 0, pid = GetCurrentProcessId();

    hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    __try {
        if (hSnapshot == INVALID_HANDLE_VALUE) __leave;

        ZeroMemory(&pe32, sizeof(pe32));
        pe32.dwSize = sizeof(pe32);
        if (!Process32First(hSnapshot, &pe32)) __leave;

        do {
            if (pe32.th32ProcessID == pid) {
                ppid = pe32.th32ParentProcessID;
                break;
            }
        } while (Process32Next(hSnapshot, &pe32));
    }
    __finally {
        if (hSnapshot != INVALID_HANDLE_VALUE) CloseHandle(hSnapshot);
    }
    return ppid;
}

// Attempt to create file in System32 folder
CHAR* fileAccess()
{
    FILE* fpa;
    fpa = fopen("C:\\Windows\\System32\\probe", "a");
    if (fpa == 0)
    {
        puts("No Write Access to System32");
        
        char* str = "NO";
        return str;
        return (false);
    }
    else (fpa == 1);
    {
        puts("Can Write to System32");
        fclose(fpa);

        char* str = "YES";
        return str;
        return (true);
     }
}

VOID main()
{
    // Date/Time
    time_t now = time(0);    
    char* dt = ctime(&now);
    if (dt[strlen(dt) - 1] == '\n') dt[strlen(dt) - 1] = '\0';

    // User
    char username[UNLEN + 1];
    DWORD username_len = UNLEN + 1;
    GetUserName(username, &username_len);

    // PID path
    DWORD pid = _getpid();
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, false, pid);
    DWORD value = MAX_PATH;
    char pidpath[MAX_PATH];
    QueryFullProcessImageName(hProcess, 0, pidpath, &value);
    printf("EXE Path: %s\n", pidpath);
            
    // PPID path
    DWORD ppid = getppid();
    HANDLE hProcess1 = OpenProcess(PROCESS_QUERY_INFORMATION, false, ppid);
    DWORD value1 = MAX_PATH;
    char ppidpath[MAX_PATH];
    QueryFullProcessImageName(hProcess1, 0, ppidpath, &value1);
    printf("EXE Path: %s\n", ppidpath);

    // write results
    FILE* fp;
    fp = fopen("C:\\Users\\Public\\Documents\\pidInspector.txt", "a");
    fprintf(fp, "exe, %s, %s, %s, %d, %s, %d, %s\n", dt, username, pidpath, _getpid(), ppidpath, getppid(), fileAccess());
    fclose(fp);

    return 0;
}