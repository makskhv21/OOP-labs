#include "rect_shape.h"

RectShape::RectShape() {}

Shape* RectShape::copyShape()
{
	return new RectShape;
}

std::wstring RectShape::getName()
{
	return L"Прямокутник";
}

void RectShape::Draw(HDC hdc)
{
	HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 255)); // Створення синьої кисті
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	int xStart = xend - (2 * (xend - xs));
	int yStart = yend - (2 * (yend - ys));

	POINT points[] = { {xStart, yStart}, {xend, yStart}, {xend, yend}, {xStart, yend} };
	Polygon(hdc, points, 4);

	MoveToEx(hdc, xStart, yStart, NULL);
	LineTo(hdc, xend, yStart);
	LineTo(hdc, xend, yend);
	LineTo(hdc, xStart, yend);
	LineTo(hdc, xStart, yStart);
	

}

void RectShape::DrawRubber(HDC hdc)
{
    

	int xStart = xend - (2 * (xend - xs));
	int yStart = yend - (2 * (yend - ys));

	SetROP2(hdc, R2_NOTXORPEN); // Зміна режиму малювання на пунктирну лінію
	HPEN hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 255)); // Пунктирна лінія, синій колір
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

	// Оригінальна логіка малювання гумового сліду
	MoveToEx(hdc, xStart, yStart, NULL);
	LineTo(hdc, xend, yStart);
	LineTo(hdc, xend, yend);
	LineTo(hdc, xStart, yend);
	LineTo(hdc, xStart, yStart);

	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);
}

LPCTSTR RectShape::setWindowText()
{
	return  L"Прямокутник";
}