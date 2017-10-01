#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND hEdit1, hEdit2, hEdit3;
	switch (msg)
	{
	case WM_CREATE:
		CreateWindow(TEXT("STATIC"), TEXT("キーボードの種類:"), WS_VISIBLE | WS_CHILD | SS_RIGHT, 10, 10, 256, 24, hWnd, 0, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		hEdit1 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), 0, WS_VISIBLE | WS_CHILD | ES_READONLY, 266, 10, 256, 24, hWnd, 0, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		CreateWindow(TEXT("STATIC"), TEXT("Original Equipment Manufacturer:"), WS_VISIBLE | WS_CHILD | SS_RIGHT, 10, 50, 256, 24, hWnd, 0, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		hEdit2 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), 0, WS_VISIBLE | WS_CHILD | ES_READONLY, 266, 50, 256, 24, hWnd, 0, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		CreateWindow(TEXT("STATIC"), TEXT("ファンクションキーの数:"), WS_VISIBLE | WS_CHILD | SS_RIGHT, 10, 90, 256, 24, hWnd, 0, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		hEdit3 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), 0, WS_VISIBLE | WS_CHILD | ES_READONLY, 266, 90, 256, 24, hWnd, 0, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		LPCTSTR p;
		switch (GetKeyboardType(0))
		{
		case 1:p = TEXT("IBM PC/XT または互換キーボード（83 キー）"); break;
		case 2:p = TEXT("Olivetti ICO キーボード（102 キー）"); break;
		case 3:p = TEXT("IBM PC/AT または類似のキーボード（84 キー）"); break;
		case 4:p = TEXT("IBM 拡張キーボード（101 キー、または 102 キー）"); break;
		case 5:p = TEXT("Nokia 1050 または類似のキーボード"); break;
		case 6:p = TEXT("Nokia 9140 または類似のキーボード"); break;
		case 7:p = TEXT("日本語キーボード"); break;
		default:p = TEXT("不明なキーボード");
		}
		SetWindowText(hEdit1, p);
		switch (GetKeyboardType(1))
		{
		case 0x00:p = TEXT("101キーボード(DOS/V)"); break;
		case 0x01:p = TEXT("AX"); break;
		case 0x02:p = TEXT("106キーボード"); break;
		case 0x04:p = TEXT("EPSON"); break;
		case 0x05:p = TEXT("富士通"); break;
		case 0x07:p = TEXT("日本IBM"); break;
		case 0x0A:p = TEXT("松下電器"); break;
		case 0x0D:p = TEXT("日本電気"); break;
		case 0x12:p = TEXT("TOSHIBA"); break;
		default:p = TEXT("不明");
		}
		SetWindowText(hEdit2, p);
		switch (GetKeyboardType(2))
		{
		case 1:p = TEXT("10"); break;
		case 2:p = TEXT("12 or 18"); break;
		case 3:p = TEXT("10"); break;
		case 4:case 12:p = TEXT("12"); break;
		case 5:p = TEXT("10"); break;
		case 6:p = TEXT("24"); break;
		default:p = TEXT("不明");
		}
		SetWindowText(hEdit3, p);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst, LPSTR pCmdLine, int nCmdShow)
{
	TCHAR szClassName[] = TEXT("Window");
	MSG msg;
	WNDCLASS wndclass = {
		CS_HREDRAW | CS_VREDRAW,
		WndProc,
		0,
		0,
		hInstance,
		0,
		LoadCursor(0,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		0,
		szClassName
	};
	RegisterClass(&wndclass);
	HWND hWnd = CreateWindow(
		szClassName,
		TEXT("キーボードの情報"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		0,
		CW_USEDEFAULT,
		0,
		0,
		0,
		hInstance,
		0
	);
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}
