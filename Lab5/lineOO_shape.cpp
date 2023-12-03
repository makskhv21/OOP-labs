#include "lineOO_shape.h"

LineOOShape::LineOOShape() {}

Shape* LineOOShape::copyShape()
{
	return new LineOOShape;
}

std::wstring LineOOShape::getName()
{
	return L"Відрізок";
}

void LineOOShape::Draw(HDC hdc)
{
	int x1, x2, y1, y2;

	x1 = xs; y1 = ys; x2 = xend; y2 = yend;

	LineShape::Set(x1, y1, x2, y2);
	LineShape::Draw(hdc);

	EllipseShape::Set(x1 - 10, y1 - 10, x1 + 10, y1 + 10);
	EllipseShape::Draw(hdc);

	EllipseShape::Set(x2 - 10, y2 - 10, x2 + 10, y2 + 10);
	EllipseShape::Draw(hdc);

	Set(x1, y1, x2, y2);

}

void LineOOShape::DrawRubber(HDC hdc)
{
	int x1, x2, y1, y2;

	x1 = xs; y1 = ys; x2 = xend; y2 = yend;

	HPEN hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 255)); // Пунктирна лінія, синій колір
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

	LineShape::Set(x1, y1, x2, y2);
	LineShape::Draw(hdc);

	EllipseShape::Set(x1 - 10, y1 - 10, x1 + 10, y1 + 10);
	EllipseShape::DrawRubber(hdc);

	EllipseShape::Set(x2 - 10, y2 - 10, x2 + 10, y2 + 10);
	EllipseShape::DrawRubber(hdc);

	xs = x1; ys = y1; xend = x2; yend = y2;
}

LPCTSTR LineOOShape::setWindowText()
{
	return  L"Відрізок";
}