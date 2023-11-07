#include "lineOO_shape.h"

void LineOOShape::Show(HDC hdc)
{
	long x1, x2, y1, y2;

	x1 = xs1; y1 = ys1; x2 = xs2; y2 = ys2;

	LineShape::SetStart(x1, y1, x2, y2);
	LineShape::Show(hdc);

	EllipseShape::SetStart(x1 - 10, y1 - 10, x1 + 10, y1 + 10);
	EllipseShape::Show(hdc);

	EllipseShape::SetStart(x2 - 10, y2 - 10, x2 + 10, y2 + 10);
	EllipseShape::Show(hdc);

	xs1 = x1; ys1 = y1; xs2 = x2; ys2 = y2;
}

void LineOOShape::DrawRubber(HWND hWnd)
{
	HDC hdc;
	hdc = GetDC(hWnd);
	long x1, x2, y1, y2;

	x1 = xs1; y1 = ys1; x2 = xs2; y2 = ys2;

	LineShape::SetStart(x1, y1, x2, y2);
	LineShape::DrawRubber(hWnd);

	EllipseShape::SetStart(x1 - 10, y1 - 10, x1 + 10, y1 + 10);
	EllipseShape::DrawRubber(hWnd);

	EllipseShape::SetStart(x2 - 10, y2 - 10, x2 + 10, y2 + 10);
	EllipseShape::DrawRubber(hWnd);

	xs1 = x1; ys1 = y1; xs2 = x2; ys2 = y2;
}

Shape* LineOOShape::copyShape()
{
	return new LineOOShape;
}

LPCTSTR LineOOShape::setWindowText()
{
	return  L"Відрізок";
}