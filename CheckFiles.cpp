#include "SoftwareDefenitions.h"
#define IDC_COMBOBOX_TEXT 1

HWND Set1, Set2, ComboBox;

HWND WinCheckFiles(HINSTANCE hInst) {

	WNDCLASS CheckFilesWindowClass = { 0 };

	CheckFilesWindowClass.hbrBackground = CreatePatternBrush(LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1)));
	CheckFilesWindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	CheckFilesWindowClass.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));
	CheckFilesWindowClass.hInstance = hInst;
	CheckFilesWindowClass.lpszClassName = L"CheckFilesWindClass";
	CheckFilesWindowClass.lpfnWndProc = CheckFilesProc;

	int x = GetSystemMetrics(SM_CXSCREEN) / 2;
	int y = GetSystemMetrics(SM_CYSCREEN) / 2;

	int w = 1028;
	int h = 445;

	HWND CheckFilesWindow;

	if (!RegisterClassW(&CheckFilesWindowClass)) {

		CheckFilesWindow = CreateWindowA("CheckFilesWindClass", "Окно проверки файлов", WS_OVERLAPPEDWINDOW | WS_VISIBLE, x - (w / 2), y - (h / 2), w, h, ::hWnd, NULL, NULL, NULL);
		SendMessage(CheckFilesWindow, WM_CHANGEUISTATE, MAKEWPARAM(UIS_SET, UISF_HIDEFOCUS), 0);

	}

	else {
	
		CheckFilesWindow = CreateWindowA("CheckFilesWindClass", "Окно проверки файлов", WS_OVERLAPPEDWINDOW | WS_VISIBLE, x - (w / 2), y - (h / 2), w, h, ::hWnd, NULL, NULL, NULL);
		SendMessage(CheckFilesWindow, WM_CHANGEUISTATE, MAKEWPARAM(UIS_SET, UISF_HIDEFOCUS), 0);
	
	}

	MSG CheckFilesMsg = { 0 };
	while (GetMessage(&CheckFilesMsg, NULL, NULL, NULL)) {

		TranslateMessage(&CheckFilesMsg);
		DispatchMessage(&CheckFilesMsg);

	}

	return CheckFilesWindow;

}

void CheckFilesWindAddWidgets(HWND hWnd) {

	HFONT hf;

	HWND Static = CreateWindowA("static", "", WS_VISIBLE | WS_CHILD | ES_CENTER | WS_HSCROLL, 4, 16, 500, 60, hWnd, NULL, NULL, NULL);

	ComboBox = CreateWindowA("combobox", "", WS_VISIBLE | WS_CHILD | ES_CENTER | CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_VSCROLL, 508, 16, 500, 445, hWnd, (HMENU)IDC_COMBOBOX_TEXT, NULL, NULL);

	for (int i = 0; i < ::NFInCB_i; SendMessageA(ComboBox, CB_ADDSTRING, 0, (LPARAM)NameFileInComboBox[i++].c_str()));

	hf = CreateFontA(16, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);

	SendMessage(Static, WM_SETFONT, (WPARAM)hf, MAKELPARAM(TRUE, 0));

	SetWindowTextA(Static, ::FileName);

	Set1 = CreateWindowA("edit", "", WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_VSCROLL | WS_HSCROLL, 4, 70, 500, 290, hWnd, NULL, NULL, NULL);
	SendMessage(Set1, EM_SETREADONLY, true, 0);
	
	memset(&FileBuffer[0], 0, sizeof(FileBuffer));

	string FilePath = TestSuperPath + "codes\\" + ::FileName;

	HANDLE File;
	File = CreateFileA(FilePath.c_str(), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(File, FileBuffer, FileBufferSize, &bytesInterated, NULL);
	CloseHandle(File);

	int wideLength = MultiByteToWideChar(CP_ACP, 0, FileBuffer, -1, nullptr, 0);
	std::wstring WFileBuffer(wideLength - 1, '\0');
	MultiByteToWideChar(CP_ACP, 0, FileBuffer, -1, &WFileBuffer[0], wideLength);

	SetWindowTextW(Set1, (LPCWSTR)WFileBuffer.c_str());

	Set2 = CreateWindowA("edit", "", WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_VSCROLL | WS_HSCROLL, 508, 70, 500, 290, hWnd, NULL, NULL, NULL);
	SendMessage(Set2, EM_SETREADONLY, true, 0);

}

LRESULT CALLBACK CheckFilesProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {

	switch (msg) {

	case WM_CREATE: {

		CheckFilesWindAddWidgets(hWnd);

		break;

	}

	case WM_COMMAND: {
	
		switch (LOWORD(wp)) {
		
		case IDC_COMBOBOX_TEXT: {

			switch (HIWORD(wp)) {
			
			case CBN_SELCHANGE: {
			
				int ItemIndex = SendMessage(ComboBox, CB_GETCURSEL, 0, 0);
				wchar_t ListItem[512];
				SendMessage(ComboBox, CB_GETLBTEXT, ItemIndex, (LPARAM)ListItem);
				std::wstring WCheckName = ListItem;

				WIN32_FIND_DATAA wfd;
				HANDLE hFind = FindFirstFileA(((string)(TestSuperPath + "codes\\*")).c_str(), &wfd);

				if (INVALID_HANDLE_VALUE != hFind) {

					int CountDo = 0;
					do {

						if (CountDo++ > 1) {

							int wideLength = MultiByteToWideChar(CP_ACP, 0, wfd.cFileName, -1, nullptr, 0);
							std::wstring wfdName(wideLength - 1, '\0');
							MultiByteToWideChar(CP_ACP, 0, wfd.cFileName, -1, &wfdName[0], wideLength);

							if (WCheckName == wfdName) {

								memset(&FileBuffer[0], 0, sizeof(FileBuffer));

								string FilePath = TestSuperPath + "codes\\";
								FilePath += wfd.cFileName;

								HANDLE File;
								File = CreateFileA(FilePath.c_str(), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
								ReadFile(File, FileBuffer, FileBufferSize, &bytesInterated, NULL);
								CloseHandle(File);

								SetWindowTextA(Set2, FileBuffer);

								goto gt;

							}

						}

					} while (NULL != FindNextFileA(hFind, &wfd));

					FindClose(hFind);

				}

				gt:

				break;
			
			}
			
			}

			break;
		
		}
		
		}

		break;
	
	}

	case WM_MOUSEWHEEL: {
	
		SendMessage(Set1, msg, wp, lp);
		SendMessage(Set2, msg, wp, lp);
		break;
	
	}

	case WM_DESTROY: {

		PostQuitMessage(0);

		break;

	}

	default: {

		return DefWindowProc(hWnd, msg, wp, lp);

	}

	}

}