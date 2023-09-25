#include "framework.h"
#include "module2.rh"

static INT_PTR CALLBACK Work2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return 1;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_BACK11)
		{
			EndDialog(hDlg, 1);
			return 1;
		}
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, 0);
			return 1;
		}
		break;
	}
	return 0;
}

int Func_MOD2(HWND hWnd, HINSTANCE hI) {
	return DialogBox(hI, MAKEINTRESOURCE(IDD_DIALOG11), hWnd, Work2);
}