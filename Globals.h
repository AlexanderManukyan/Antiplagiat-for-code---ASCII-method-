#pragma once
#include "resource.h"
#include <string>
#include <iostream>
#include <windows.h>
#include <sstream>
#include <shlobj.h>

using std::string;

#define WindowBufferSize			20000
#define FileBufferSize				200000

extern string Password;
extern int percent;

extern string TestSuperPath;


extern char WindowBuffer[WindowBufferSize];
extern char FileBuffer[FileBufferSize];
extern string NameFileInComboBox[1000];
extern int NFInCB_i;

extern HWND Set;

extern LPCSTR FileName;

extern char filename[1000];
extern OPENFILENAMEA MainOfn, CheckFilesOfn;

extern HWND hWnd;

extern DWORD bytesInterated;