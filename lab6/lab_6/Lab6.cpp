﻿#include "stdafx.h"
#include "lab_6.h"
#include "dialog.h"


#define MAX_LOADSTRING 100


HINSTANCE hInst;                               
WCHAR szTitle[MAX_LOADSTRING];                  
WCHAR szWindowClass[MAX_LOADSTRING];           


ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
extern int Dialog(HINSTANCE hInst, HWND hWnd);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB6, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB6));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB6));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB6);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//

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
	int result;
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            switch (wmId)
            {
			case IDM_LABBUTTON:
				result = Dialog(hInst, hWnd);
				break;
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

static INT_PTR CALLBACK Dialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);

    char numbers[10];
    char minimum[10];
    char maximum[10];
    HWND hWndDataCreator;
    COPYDATASTRUCT cds;
    HWND hWndL1;
    int limit = 200;
    int limitNumbers = 64;


    int wmId = LOWORD(wParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_DESTROY: {
        hWndL1 = FindWindow(L"LAB61", NULL);
        if (hWndL1) PostMessage(hWndL1, WM_DESTROY, (WPARAM)wParam, 0);
        break;
    }
    case WM_COMMAND:
        switch (wmId) {
        case IDCANCEL:
            EndDialog(hDlg, 0);
            return (INT_PTR)TRUE;
            break;
        case IDB_CONTINUE:
            GetWindowTextA(GetDlgItem(hDlg, IDC_N), numbers, sizeof(numbers));
            GetWindowTextA(GetDlgItem(hDlg, IDC_MIN), minimum, sizeof(minimum));
            GetWindowTextA(GetDlgItem(hDlg, IDC_MAX), maximum, sizeof(maximum));

            if (numbers[0] == '\0' || minimum[0] == '\0' || maximum[0] == '\0') {
                MessageBox(GetParent(hDlg), L"Введіть непусті дані", L"Помилка", MB_OK);
            }
            else if (atoi(minimum) > limit || atoi(maximum) > limit || atoi(numbers) > limitNumbers || atoi(minimum) >= atoi(maximum)) {
                MessageBox(GetParent(hDlg), L"Введіть коректні дані. Перевищений ліміт одного із параметрів", L"Помилка", MB_OK);
            }
            else {
                long parametres[3] = {atoi(numbers), atoi(minimum), atoi(maximum)};
                cds.dwData = 1;
                cds.cbData = 9;
                cds.lpData = parametres;
                hWndDataCreator = FindWindow(L"LAB61", NULL);

                if (hWndDataCreator == NULL) {
                    WinExec("Object1.exe", SW_SHOW);
                    hWndDataCreator = FindWindow(L"LAB61", NULL);
                }

                SendMessage(hWndDataCreator, WM_COPYDATA, (WPARAM)GetParent(hDlg), (LPARAM)&cds);
            }
            break;
        }
    }

    return (INT_PTR)FALSE;
}

int Dialog(HINSTANCE hInst, HWND hWnd) {
    return DialogBox(hInst, MAKEINTRESOURCE(IDD_MODULE), hWnd, Dialog);
}


