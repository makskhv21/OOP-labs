#include "framework.h"
#include "module1.rh"


static INT_PTR CALLBACK Work1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_NEXT)
		{
			EndDialog(hDlg, 1);
			return 1;
		}
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, 0);
			return 1;
		}
		break;
	}
	return 0;
}


int Func_MOD1(HWND hWnd, HINSTANCE hI) {
	return DialogBox(hI, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Work1);
}