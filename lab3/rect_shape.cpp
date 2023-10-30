#include "framework.h"
#include "rect_shape.h"

void RectShape::Show(HDC hdc) {
	HBRUSH hBrush, hBrushOld;
	colorfill = RGB(0, 255, 255);
	hBrush = (HBRUSH)CreateSolidBrush(colorfill);
	hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);

	long xStart = xs2 - (xs2 - xs1); 	 //
	long yStart = ys2 - (ys2 - ys1);

	Rectangle(hdc, xStart, yStart, xs2, ys2);
	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
}