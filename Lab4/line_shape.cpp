#include "line_shape.h"

void LineShape::Show(HDC hdc)
{
	MoveToEx(hdc, xs1, ys1, NULL);
	LineTo(hdc, xs2, ys2);
}

void LineShape::DrawRubber(HWND hWnd)
{
	HDC hdc;
	HPEN hPenOld, hPen;
	hdc = GetDC(hWnd);
	SetROP2(hdc, R2_NOTXORPEN);
	hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 255));
	hPenOld = (HPEN)SelectObject(hdc, hPen); 
	MoveToEx(hdc, xs1, ys1, NULL);
	LineTo(hdc, xs2, ys2);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc);
}

Shape* LineShape::copyShape()
{
	return new LineShape;
}

LPCTSTR  LineShape::setWindowText()
{
	return  L"Лінія";
}