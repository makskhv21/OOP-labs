

#include "stdafx.h"
#include "lab_6.2.h"
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_LOADSTRING 100

HINSTANCE hInst;                                
WCHAR szTitle[MAX_LOADSTRING];                  
WCHAR szWindowClass[MAX_LOADSTRING];            
vector<float> numbersVector;


ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
long Clipboard(HWND, char *, long);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB62, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB62));

    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}




//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB62));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB62);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; 

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	char text[700] = {};
	string str;
    int width = 200;
    int height = 700;
    int startX = 326;
    int startY = 40;

    switch (message)
    {
	    case WM_CREATE: 
	    {
		    SetWindowPos(hWnd, HWND_NOTOPMOST, startX, startY, width, height, SWP_DEFERERASE);
	    }
	    case IDR_REBOOT: 
	    {
		    numbersVector.clear();
		    Clipboard(hWnd, text, 700);
		    str = text;
		    string number;
		    while (str != "") {
			    number = str.substr(0, str.find_first_of("\n"));
			    char buffer[100] = {};
			    numbersVector.push_back(stod(number));
			    str = str.substr(str.find_first_of("\n") + 1);
		    }
		    sort(numbersVector.begin(), numbersVector.end());
		    InvalidateRect(hWnd, NULL, TRUE);
	    }
        case WM_COMMAND:
            {
                int wmId = LOWORD(wParam);
                switch (wmId)
                {
                case IDM_ABOUT:
                    DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                    break;
                case IDM_EXIT:
                    DestroyWindow(hWnd);
                    break;
                default:
                    return DefWindowProcW(hWnd, message, wParam, lParam);
                }
            }
            break;
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            for (int i = 0; i < numbersVector.size(); i++) {
                int number = numbersVector[i];
                int count = 0;
                while (number) {
                    number /= 10;
                    count++;
                }
                char buffer[100] = {};
                sprintf_s(buffer, "%f", numbersVector[i]);
                TextOutA(hdc, 10 + int(i / 32) * 100, (i % 32) * 20, buffer, count + 7);
            }
            EndPaint(hWnd, &ps);
        }
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProcW(hWnd, message, wParam, lParam);
        }
    return 0;
}


INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

long Clipboard(HWND hWnd, char* dest, long maxsize) {
    if (!IsClipboardFormatAvailable(CF_TEXT) || !OpenClipboard(hWnd)) return 0;

    HANDLE hglb = GetClipboardData(CF_TEXT);
    if (hglb == NULL) {
        CloseClipboard();
        return 0;
    }

    const char* lptstr = static_cast<const char*>(GlobalLock(hglb));
    if (lptstr == NULL) {
        CloseClipboard();
        return 0;
    }

    long size = strlen(lptstr);
    if (size >= maxsize) {
        GlobalUnlock(hglb);
        CloseClipboard();
        return 0;
    }

    strcpy_s(dest, maxsize, lptstr);
    GlobalUnlock(hglb);
    CloseClipboard();
    return size;
}

