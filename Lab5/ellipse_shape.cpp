#include "ellipse_shape.h"

EllipseShape::EllipseShape() {}

Shape* EllipseShape::copyShape()
{
	return new EllipseShape;
}

std::wstring EllipseShape::getName()
{
	return L"Еліпс";
}

void EllipseShape::Draw(HDC hdc)
{
	HBRUSH hBrush, hBrushOld;
	hBrush = (HBRUSH)
	CreateSolidBrush(RGB(255, 255, 255));
	hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);

	Ellipse(hdc, xs, ys, xend, yend);

	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
}

void EllipseShape::DrawRubber(HDC hdc)
{
	HPEN hPenOld, hPen;
	SetROP2(hdc, R2_NOTXORPEN);
	hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	Ellipse(hdc, xs, ys, xend, yend);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

LPCTSTR EllipseShape::setWindowText()
{
	return  L"Еліпс"; 
}