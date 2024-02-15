#pragma once
#include "Globals.h"

#define OnReadFile					1
#define PathSettings				2
#define CheckFiles					3

#define OnClearFields				7

#define PercentSettings100			29
#define PercentSettings90			30
#define PercentSettings80			31
#define PercentSettings70			32
#define PercentSettings60			33
#define PercentSettings50			34
#define PercentSettings40			35
#define PercentSettings30			36
#define PercentSettings20			37
#define PercentSettings10			38

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPr, LPSTR args, int nCmdShow);
void MainWindAddMenu(HWND hWnd);
void MainWindAddWidgets(HWND hWnd);
void MainSetOpenFileParams(HWND hWnd);
LRESULT CALLBACK MainProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

HWND PassWindow(HINSTANCE hInst, int PercentParam);
void PassWindAddWidgets(HWND hPassWnd);
LRESULT CALLBACK PassWndProc(HWND hPassWnd, UINT msg, WPARAM wp, LPARAM lp);
LRESULT CALLBACK PassEditProc(HWND hPassWnd, UINT msg, WPARAM wp, LPARAM lp);

HWND WinCheckFiles(HINSTANCE hInst);
void CheckFilesWindAddWidgets(HWND hWnd);
LRESULT CALLBACK CheckFilesProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

void TestFile(HANDLE& File1);
void ReadFile(LPSTR path);