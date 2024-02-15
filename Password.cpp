#include "SoftwareDefenitions.h"

static int PercentParam;
HWND Edit, hPassWnd;
WNDPROC DefEditProc;

HWND PassWindow(HINSTANCE hInst, int PercentParam) {

	::PercentParam = PercentParam;

	MessageBoxA(NULL, "Введите пароль", "ВНИМАНИЕ", MB_ICONINFORMATION | MB_DEFBUTTON1);

	WNDCLASS PasswordWindowClass = { 0 };

	PasswordWindowClass.hbrBackground = CreatePatternBrush(LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1)));
	PasswordWindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	PasswordWindowClass.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));
	PasswordWindowClass.hInstance = hInst;
	PasswordWindowClass.lpszClassName = L"PasswordWindClass";
	PasswordWindowClass.lpfnWndProc = PassWndProc;

	int x = GetSystemMetrics(SM_CXSCREEN) / 2;
	int y = GetSystemMetrics(SM_CYSCREEN) / 2;

	int w = 300;
	int h = 55;

	HWND PasswordWindow;

	if (!RegisterClassW(&PasswordWindowClass)) {

		PasswordWindow = CreateWindowA("PasswordWindClass", "Ведите пароль", WS_OVERLAPPEDWINDOW | WS_VISIBLE, x - (w / 2), y - (h / 2), w, h, ::hWnd, NULL, NULL, NULL);
		SendMessage(PasswordWindow, WM_CHANGEUISTATE, MAKEWPARAM(UIS_SET, UISF_HIDEFOCUS), 0);

	}

	else {

		PasswordWindow = CreateWindowA("PasswordWindClass", "Ведите пароль", WS_OVERLAPPEDWINDOW | WS_VISIBLE, x - (w / 2), y - (h / 2), w, h, ::hWnd, NULL, NULL, NULL);
		SendMessage(PasswordWindow, WM_CHANGEUISTATE, MAKEWPARAM(UIS_SET, UISF_HIDEFOCUS), 0);

	}

	::hPassWnd = PasswordWindow;

	MSG PassMsg = { 0 };

	while (GetMessage(&PassMsg, NULL, NULL, NULL)) {

		TranslateMessage(&PassMsg);
		DispatchMessage(&PassMsg);

	}

	return PasswordWindow;

}

void PassWindAddWidgets(HWND hPassWnd) {

	Edit = CreateWindowA("edit", "", WS_VISIBLE | WS_CHILD | ES_PASSWORD | ES_AUTOHSCROLL, 0, 0, 300, 14, hPassWnd, NULL, NULL, NULL);
	SendMessage(Edit, EM_SETPASSWORDCHAR, '*', 0);

	DefEditProc = (WNDPROC)GetWindowLongPtr(Edit, GWLP_WNDPROC);
	SetWindowLongPtr(Edit, GWLP_WNDPROC, (LONG_PTR)PassEditProc);

	SetFocus(Edit);

}

LRESULT CALLBACK PassEditProc(HWND hPassWnd, UINT msg, WPARAM wp, LPARAM lp) {

	switch (msg) {

	case WM_KEYDOWN: {

		if (wp == VK_RETURN) {

			string Str;

			GetWindowTextA(hPassWnd, WindowBuffer, WindowBufferSize);
			Str = WindowBuffer;
			memset(&WindowBuffer[0], 0, sizeof(WindowBuffer));

			if (Str == Password) {

				if (PercentParam == 0) {

					MessageBoxA(NULL, "Выберите путь до папки с отчетами программы", "ВНИМАНИЕ", MB_ICONINFORMATION | MB_DEFBUTTON1);

					BROWSEINFO bi = { hWnd, NULL, NULL, NULL, BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_EDITBOX | BIF_BROWSEFORCOMPUTER, NULL, NULL, 0 };

					LPCITEMIDLIST lpItemDList;
					if (!(lpItemDList = SHBrowseForFolder(&bi))) {}

					WCHAR path[400];
					SHGetPathFromIDListW(lpItemDList, path);

					char ch[400];
					char DefChar = ' ';
					WideCharToMultiByte(CP_ACP, 0, path, -1, ch, 400, &DefChar, NULL);

					TestSuperPath = string(ch) + "\\";

					string TSP = TestSuperPath + "codes";
					CreateDirectoryW((std::wstring(TSP.begin(), TSP.end())).c_str(), NULL);
					TSP = TestSuperPath + "reports";
					CreateDirectoryW((std::wstring(TSP.begin(), TSP.end())).c_str(), NULL);

					MessageBoxA(NULL, (LPSTR)(("Процент схожести равен " + std::to_string(percent) + "%").c_str()), "ВНИМАНИЕ", MB_ICONINFORMATION | MB_DEFBUTTON1);

					SendMessageA(::hPassWnd, WM_CLOSE, true, 0);

				}

				else {

					percent = PercentParam;
					MessageBoxA(NULL, (LPSTR)(("Процент схожести равен " + std::to_string(PercentParam) + "%").c_str()), "ВНИМАНИЕ", MB_ICONINFORMATION | MB_DEFBUTTON1);
					SendMessageA(::hPassWnd, WM_CLOSE, true, 0);


				}

			}

			else {

				MessageBoxA(NULL, "Неверный пароль!", "ОШИБКА", MB_ICONWARNING | MB_DEFBUTTON1);

				SetWindowTextA(Edit, "");

				SetFocus(Edit);

			}

		}

		break;

	}

	default: {

		return CallWindowProc(DefEditProc, hPassWnd, msg, wp, lp);

	}

	}

}

LRESULT CALLBACK PassWndProc(HWND hPassWnd, UINT msg, WPARAM wp, LPARAM lp) {

	switch (msg) {

	case WM_CREATE: {

		PassWindAddWidgets(hPassWnd);

		break;

	}

	case WM_DESTROY: {

		PostQuitMessage(0);

		break;

	}

	default: {

		return DefWindowProc(hPassWnd, msg, wp, lp);

	}

	}

}