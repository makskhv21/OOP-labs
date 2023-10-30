#include "ShapeEditor.h"
#include "ellipse_shape.h"
#include "ellipse_editor.h"
#include "Resource.h"

void EllipseEditor::OnLBdown(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	xstart = xend = pt.x;
	ystart = yend = pt.y;
}
void EllipseEditor::OnMouseMove(HWND hWnd) {
	if (!xstart) return;
	HPEN hPenOld, hPen;
	HDC hdc;

	hdc = GetDC(hWnd);
	SetROP2(hdc, R2_NOTXORPEN);
	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	long xStart = xend - (2 * (xend - xstart));
	long yStart = yend - (2 * (yend - ystart));
	Arc(hdc, xStart, yStart, xend, yend, 0, 0, 0, 0);
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);

	xend = pt.x;
	yend = pt.y;

	xStart = xend - (2 * (xend - xstart));
	yStart = yend - (2 * (yend - ystart));
	Arc(hdc, xStart, yStart, xend, yend, 0, 0, 0, 0);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc);
}

void EllipseEditor::OnLBup(HWND hWnd) {
	pcshape[index] = new EllipseShape;
	pcshape[index]->Set(xstart, ystart, xend, yend);
	index++;
	InvalidateRect(hWnd, NULL, TRUE);
	xstart = NULL;
};