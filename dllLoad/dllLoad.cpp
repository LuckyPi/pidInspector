/*******************************************************************************************************************************/
// Project: dllLoad 
// Filename: dllLoad.cpp 
// Description: loads the pidInspector_dll.dll for testing without having a hijack
// Author: JT, jtestman@gmail.com
/*******************************************************************************************************************************/

#include <windows.h>

typedef int(WINAPI* ShellAboutProc)(HWND, LPCSTR, LPCSTR, HICON);

int main()
{
    HMODULE hModule = LoadLibrary(TEXT("pidInspector_dll.dll"));

    FreeLibrary(hModule);
}