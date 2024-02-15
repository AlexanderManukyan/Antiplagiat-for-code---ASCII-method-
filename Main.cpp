#include "SoftwareDefenitions.h"

HINSTANCE hInst;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPr, LPSTR args, int nCmdShow) {

	::hInst = hInst;																						

	WNDCLASS MainWindowClass = { 0 };																		

	MainWindowClass.hbrBackground = CreatePatternBrush(LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1)));	
	MainWindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);													
	MainWindowClass.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));									
	MainWindowClass.hInstance = hInst;
	MainWindowClass.lpszClassName = L"MainWindClass";														
	MainWindowClass.lpfnWndProc = MainProc;																	

	if (!RegisterClassW(&MainWindowClass)) {

		return -1;

	}

	int x = GetSystemMetrics(SM_CXSCREEN) / 2;																
	int y = GetSystemMetrics(SM_CYSCREEN) / 2;

	int w = 460;																							
	int h = 353;

	HWND MainWindow = CreateWindowA("MainWindClass", "Антиплагиат", WS_OVERLAPPEDWINDOW | WS_VISIBLE, x - (w / 2), y - (h / 2), w, h, NULL, NULL, NULL, NULL);
	SendMessage(MainWindow, WM_CHANGEUISTATE, MAKEWPARAM(UIS_SET, UISF_HIDEFOCUS), 0);

	::hWnd = MainWindow;																						

	MSG MainMsg = { 0 };																					

	while (GetMessage(&MainMsg, NULL, NULL, NULL)) {														

		TranslateMessage(&MainMsg);																			
		DispatchMessage(&MainMsg);																			

	}

}

void MainWindAddMenu(HWND hWnd) {																			

	HMENU RootMenu = CreateMenu();																			
	HMENU SubMenu = CreateMenu();																			

	AppendMenuA(RootMenu, MF_STRING, OnClearFields, "Очистить поле");										
	AppendMenuA(RootMenu, MF_STRING, PathSettings, "Настройка путей");
	AppendMenuA(RootMenu, MF_POPUP, (UINT_PTR)SubMenu, "Процент схожести");
	AppendMenuA(RootMenu, MF_STRING, CheckFiles, "Проверить файлы");

	AppendMenuA(SubMenu, MF_STRING, PercentSettings100, "100%");
	AppendMenuA(SubMenu, MF_STRING, PercentSettings90, "90%");											
	AppendMenuA(SubMenu, MF_STRING, PercentSettings80, "80%");
	AppendMenuA(SubMenu, MF_STRING, PercentSettings70, "70%");
	AppendMenuA(SubMenu, MF_STRING, PercentSettings60, "60%");
	AppendMenuA(SubMenu, MF_STRING, PercentSettings50, "50%");
	AppendMenuA(SubMenu, MF_STRING, PercentSettings40, "40%");
	AppendMenuA(SubMenu, MF_STRING, PercentSettings30, "30%");
	AppendMenuA(SubMenu, MF_STRING, PercentSettings20, "20%");
	AppendMenuA(SubMenu, MF_STRING, PercentSettings10, "10%");												

	SetMenu(hWnd, RootMenu);																				
}

void MainWindAddWidgets(HWND hWnd) {																		

	HFONT hf;																								

	HWND Button = CreateWindowA("button", "Прочитать файл", WS_VISIBLE | WS_CHILD | ES_CENTER, 190, 18, 180, 40, hWnd, (HMENU)OnReadFile, NULL, NULL);

	hf = CreateFontA(24, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);

	SendMessage(Button, WM_SETFONT, (WPARAM)hf, 0);																																		

	HWND Static = CreateWindowA("static", "Результат проверки:", WS_VISIBLE | WS_CHILD | ES_CENTER, 10, 70, 94, 39, hWnd, NULL, NULL, NULL);

	hf = CreateFontA(18, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);

	SendMessage(Static, WM_SETFONT, (WPARAM)hf, 0);

	HWND Set = CreateWindowA("edit", "", WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_VSCROLL, 115, 70, 320, 215, hWnd, NULL, NULL, NULL);

	SendMessage(Set, EM_SETREADONLY, true, 0);

	::Set = Set;

}

void MainSetOpenFileParams(HWND hWnd) {

	ZeroMemory(&MainOfn, sizeof(MainOfn));
	MainOfn.lStructSize = sizeof(MainOfn);
	MainOfn.hwndOwner = hWnd;
	MainOfn.lpstrFile = filename;
	MainOfn.nMaxFile = sizeof(filename);
	MainOfn.lpstrFilter = "C++ Файлы(*.cpp; *.h)\0*.cpp; *.h\0Все файлы\0*.*\0";
	MainOfn.lpstrFileTitle = NULL;
	MainOfn.nMaxFileTitle = NULL;
	MainOfn.lpstrInitialDir = NULL;
	MainOfn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

}

LRESULT CALLBACK MainProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {

	switch (msg) {

		case WM_COMMAND: {

			switch (wp) {

				case OnReadFile: {

					if (GetOpenFileNameA(&MainOfn)) {

						ReadFile(filename);

					}

					break;

				}

				case CheckFiles: {
				
					WinCheckFiles(hInst);

					break;
				
				}

				case OnClearFields: {

					SetWindowTextA(Set, "");
					break;

				}

				case PathSettings: {

					PassWindow(hInst, 0);

					break;

				}

				case PercentSettings100: {

					PassWindow(hInst, 100);

					break;

				}

				case PercentSettings90: {

					PassWindow(hInst, 90);

					break;

				}

				case PercentSettings80: {

					PassWindow(hInst, 80);

					break;

				}

				case PercentSettings70: {

					PassWindow(hInst, 70);

					break;

				}

				case PercentSettings60: {

					PassWindow(hInst, 60);

					break;

				}

				case PercentSettings50: {

					PassWindow(hInst, 50);

					break;

				}

				case PercentSettings40: {

					PassWindow(hInst, 40);

					break;

				}

				case PercentSettings30: {

					PassWindow(hInst, 30);

					break;

				}

				case PercentSettings20: {

					PassWindow(hInst, 20);

					break;

				}

				case PercentSettings10: {

					PassWindow(hInst, 10);

					break;

				}

				default: {

					break;

				}

			}

			break;

		}

		case WM_CREATE: {

			MainWindAddMenu(hWnd);
			MainWindAddWidgets(hWnd);
			MainSetOpenFileParams(hWnd);
			PassWindow(hInst, 0);

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