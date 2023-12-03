#include "point_shape.h"
#include "framework.h"

PointShape::PointShape() {}

Shape* PointShape::copyShape()
{
	return new PointShape;
}

std::wstring PointShape::getName()
{
	xs = xend;
	ys = yend;
	xend = 0;
	yend = 0;
	return L"Крапка";
}

void PointShape::Draw(HDC hdc)
{
	SetPixel(hdc, xs, ys, 0x00000000);
}

void PointShape::DrawRubber(HDC hdc) {}

LPCTSTR PointShape::setWindowText()
{
	return  L"Крапка";
}