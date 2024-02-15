#include "Globals.h"

string Password = "PMI121";
int percent = 90;

string TestSuperPath = "";

char WindowBuffer[WindowBufferSize];
char FileBuffer[FileBufferSize];
string NameFileInComboBox[1000];
int NFInCB_i = 0;

HWND Set;

LPCSTR FileName = LPCSTR("");

char filename[1000];
OPENFILENAMEA MainOfn, CheckFilesOfn;

HWND hWnd;

DWORD bytesInterated;