#include "line_shape.h"

LineShape::LineShape() {}

Shape* LineShape::copyShape()
{
	return new LineShape;
}

std::wstring LineShape::getName()
{
	return L"Лінія";
}

void LineShape::Draw(HDC hdc)
{
	MoveToEx(hdc, xs, ys, NULL);
	LineTo(hdc, xend, yend);
}

void LineShape::DrawRubber(HDC hdc)
{
    SetROP2(hdc, R2_NOTXORPEN); // Зміна режиму малювання
    HPEN hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 255)); // Синій колір
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

    // Ваша логіка малювання гумового сліду
    Draw(hdc);

    SelectObject(hdc, hOldPen);
    DeleteObject(hPen);
}

LPCTSTR  LineShape::setWindowText()
{
	return  L"Лінія";
}