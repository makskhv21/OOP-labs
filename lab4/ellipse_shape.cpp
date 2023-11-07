#include "framework.h"
#include "ellipse_shape.h"

void EllipseShape::Show(HDC hdc) {
	Ellipse(hdc, xs1, ys1, xs2, ys2);
}

void EllipseShape::DrawRubber(HWND hWnd)
{
	HDC hdc;
	HPEN hPenOld, hPen;
	hdc = GetDC(hWnd);
	SetROP2(hdc, R2_NOTXORPEN);
	hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	Ellipse(hdc, xs1, ys1, xs2, ys2);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc);
}

Shape* EllipseShape::copyShape()
{
	return new EllipseShape;
}

LPCTSTR EllipseShape::setWindowText()
{
	return  L"Еліпс";
}