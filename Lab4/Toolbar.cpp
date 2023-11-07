#include "framework.h"
#include "resource.h"
#include "Toolbar.h"

#include <commctrl.h>


ToolBar::ToolBar(void) {}

void ToolBar::OnCreate(HWND hWnd, HINSTANCE hInst)
{
    TBBUTTON tbb[6]; 
    ZeroMemory(tbb, sizeof(tbb));
    tbb[0].iBitmap = 0; // Number image
    tbb[0].fsState = TBSTATE_ENABLED; //element active and available for interaction
    tbb[0].fsStyle = TBSTYLE_BUTTON; // element is button
    tbb[0].idCommand = ID_TOOL_POINT; // element identification

    tbb[1].iBitmap = 1;
    tbb[1].fsState = TBSTATE_ENABLED;
    tbb[1].fsStyle = TBSTYLE_BUTTON;
    tbb[1].idCommand = ID_TOOL_LINE;

    tbb[2].iBitmap = 2;
    tbb[2].fsState = TBSTATE_ENABLED;
    tbb[2].fsStyle = TBSTYLE_BUTTON;
    tbb[2].idCommand = ID_TOOL_RECT;

    tbb[3].iBitmap = 3;
    tbb[3].fsState = TBSTATE_ENABLED;
    tbb[3].fsStyle = TBSTYLE_BUTTON;
    tbb[3].idCommand = ID_TOOL_ELLIPSE;

    tbb[4].iBitmap = 4;
    tbb[4].fsState = TBSTATE_ENABLED;
    tbb[4].fsStyle = TBSTYLE_BUTTON;
    tbb[4].idCommand = ID_TOOL_OOLINE;

    tbb[5].iBitmap = 5;
    tbb[5].fsState = TBSTATE_ENABLED;
    tbb[5].fsStyle = TBSTYLE_BUTTON;
    tbb[5].idCommand = ID_TOOL_CUBE;



    SendMessage(hwndToolBar, TB_ADDBUTTONS, 6, (LPARAM)&tbb);

    hwndToolBar = CreateToolbarEx(hWnd, 
        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPSIBLINGS | CCS_TOP |
        TBSTYLE_TOOLTIPS,
        IDC_MY_TOOLBAR, 
        6,
        hInst,
        IDB_BITMAP1,
        tbb, 
        6, 
        24, 24, 24, 24,
        sizeof(TBBUTTON));
}

void ToolBar::OnSize(HWND hWnd)
{
    RECT rc, rw;
    if (hwndToolBar)
    {
        GetClientRect(hWnd, &rc); 
        GetWindowRect(hwndToolBar, &rw); 
        MoveWindow(hwndToolBar, 0, 0, rc.right - rc.left, rw.bottom - rw.top, FALSE);
    }
}

void ToolBar::OnTool(HWND hWnd, LPARAM lParam)
{
    if (oldlParam)
    {
        SendMessage(hwndToolBar, TB_PRESSBUTTON, oldlParam, 0); 
    }
    SendMessage(hwndToolBar, TB_PRESSBUTTON, lParam, 1); 
    oldlParam = lParam;
}

void ToolBar::OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    LPNMHDR pnmh = (LPNMHDR)lParam;
    if (pnmh->code == TTN_NEEDTEXT)
    {
        LPTOOLTIPTEXT lpttt = (LPTOOLTIPTEXT)lParam;
        switch (lpttt->hdr.idFrom)
        {

        case ID_TOOL_POINT:
            lstrcpy(lpttt->szText, L"Крапка");
            break;

        case ID_TOOL_LINE:
            lstrcpy(lpttt->szText, L"Лінія");
            break;

        case ID_TOOL_RECT:
            lstrcpy(lpttt->szText, L"Прямокутник");
            break;

        case ID_TOOL_ELLIPSE:
            lstrcpy(lpttt->szText, L"Еліпс");
            break;

        case ID_TOOL_OOLINE:
            lstrcpy(lpttt->szText, L"Відрізок");
            break;

        case ID_TOOL_CUBE:
            lstrcpy(lpttt->szText, L"Куб");
            break;

        default: lstrcpy(lpttt->szText, L"Фігури немає");
        }
    }
}