#include "point_shape.h"

void PointShape::Show(HDC hdc)
{
	SetPixel(hdc, xs1, ys1, 0x00000000);
}

void PointShape::DrawRubber(HWND hWnd) {}

Shape* PointShape::copyShape()
{
	return new PointShape;
}

LPCTSTR PointShape::setWindowText()
{
	return  L"Крапка";
}