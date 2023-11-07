#include "cube_shape.h"

void CubeShape::Show(HDC hdc)
{
	int x1, x2, y1, y2;

	RectShape::Show(hdc);

	x1 = xs1; y1 = ys1; x2 = xs2; y2 = ys2;

	int xStart = x2 - (2 * (x2 - x1));
	int yStart = y2 - (2 * (y2 - y1));

	int xEnd = 2 * x2 - x1;
	int yEnd = y1 - (2 * (y2 - y1));

	LineShape::SetStart(x1, y1, xStart, y2);
	LineShape::Show(hdc);

	LineShape::SetStart(xStart, yStart, x1, yEnd);
	LineShape::Show(hdc);

	LineShape::SetStart(x2, yStart, xEnd, yEnd);
	LineShape::Show(hdc);

	LineShape::SetStart(x2, y2, xEnd, y1);
	LineShape::Show(hdc);

	LineShape::SetStart(x1, y1, x1, yEnd);
	LineShape::Show(hdc);

	LineShape::SetStart(x1, yEnd, xEnd, yEnd);
	LineShape::Show(hdc);

	LineShape::SetStart(xEnd, yEnd, xEnd, y1);
	LineShape::Show(hdc);

	LineShape::SetStart(xEnd, y1, x1, y1);
	LineShape::Show(hdc);

	xs1 = x1; ys1 = y1; xs2 = x2; ys2 = y2;
}

void CubeShape::DrawRubber(HWND hWnd)
{
	HDC hdc;
	HPEN hPenOld, hPen;
	hdc = GetDC(hWnd);
	SetROP2(hdc, R2_NOTXORPEN);
	hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	int x1, x2, y1, y2;

	RectShape::DrawRubber(hWnd);

	x1 = xs1; y1 = ys1; x2 = xs2; y2 = ys2;

	int xStart = x2 - (2 * (x2 - x1));
	int yStart = y2 - (2 * (y2 - y1));
	int xEnd = 2 * x2 - x1;
	int yEnd = y1 - (2 * (y2 - y1));

	LineShape::SetStart(x1, y1, xStart, y2);
	LineShape::DrawRubber(hWnd);

	LineShape::SetStart(xStart, yStart, x1, yEnd);
	LineShape::DrawRubber(hWnd);

	LineShape::SetStart(x2, yStart, xEnd, yEnd);
	LineShape::DrawRubber(hWnd);

	LineShape::SetStart(x2, y2, xEnd, y1);
	LineShape::DrawRubber(hWnd);

	LineShape::SetStart(x1, y1, x1, yEnd);
	LineShape::DrawRubber(hWnd);

	LineShape::SetStart(x1, yEnd, xEnd, yEnd);
	LineShape::DrawRubber(hWnd);

	LineShape::SetStart(xEnd, yEnd, xEnd, y1);
	LineShape::DrawRubber(hWnd);

	LineShape::SetStart(xEnd, y1, x1, y1);
	LineShape::DrawRubber(hWnd);

	xs1 = x1; ys1 = y1; xs2 = x2; ys2 = y2;
}

Shape* CubeShape::copyShape()
{
	return new CubeShape;
}

LPCTSTR CubeShape::setWindowText()
{
	return  L"Куб";
}