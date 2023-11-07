// Lab4.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Lab4.h"
#include "MyEditor.h"
#include "Toolbar.h"
#include "point_shape.h"
#include "line_shape.h"
#include "rect_shape.h"
#include "ellipse_shape.h"
#include "lineOO_shape.h"
#include "cube_shape.h"




#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB4, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB4));

    MSG msg;

    // Main message loop:
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
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB4));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB4);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

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
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//


MyEditor* myeditor = NULL;
ToolBar toolbar;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        toolbar.OnCreate(hWnd, hInst);
        toolbar.OnTool(hWnd, ID_TOOL_POINT); //selecting point from start
        myeditor = new MyEditor;
        if (myeditor) myeditor->Start(hWnd, new PointShape);
        break;

    case WM_SIZE:
        toolbar.OnSize(hWnd);
        break;

    case WM_NOTIFY:
        toolbar.OnNotify(hWnd, wParam, lParam);
        break;


    case WM_LBUTTONDOWN: 
        if (myeditor) myeditor->OnLBdown(hWnd);
        break;

    case WM_LBUTTONUP: 
        if (myeditor) myeditor->OnLBup(hWnd);
        break;

    case WM_MOUSEMOVE: 
        if (myeditor) myeditor->OnMouseMove(hWnd);
        break;

    case WM_PAINT: 
        
        if (myeditor) myeditor->OnPaint(hWnd);
        break;
    case WM_COMMAND:
        {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case ID_TOOL_POINT:
        case ID_32771:
            toolbar.OnTool(hWnd, ID_TOOL_POINT);
            if (myeditor) myeditor->Start(hWnd, new PointShape);
            break;

        case ID_TOOL_LINE:
        case ID_32772:
            toolbar.OnTool(hWnd, ID_TOOL_LINE);
            if (myeditor) myeditor->Start(hWnd, new LineShape);
            break;

        case ID_TOOL_RECT:
        case ID_32773:
            toolbar.OnTool(hWnd, ID_TOOL_RECT);
            if (myeditor) myeditor->Start(hWnd, new RectShape);
            break;

        case ID_TOOL_ELLIPSE:
        case ID_32774:
            toolbar.OnTool(hWnd, ID_TOOL_ELLIPSE);
            if (myeditor) myeditor->Start(hWnd, new EllipseShape);
            break;

        case ID_TOOL_OOLINE:
        case ID_32775:
            toolbar.OnTool(hWnd, ID_TOOL_OOLINE);
            if (myeditor) myeditor->Start(hWnd, new LineOOShape);
            break;

        case ID_TOOL_CUBE:
        case ID_32776:
            toolbar.OnTool(hWnd, ID_TOOL_CUBE);
            if (myeditor) myeditor->Start(hWnd, new CubeShape);
            break;

        
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;

        case IDM_EXIT:
            if (myeditor) delete myeditor;
            DestroyWindow(hWnd);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }

        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
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
