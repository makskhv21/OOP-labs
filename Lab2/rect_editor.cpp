#include "ShapeEditor.h"
#include "rect_shape.h"
#include "rect_editor.h"
#include "Resource.h"

void RectEditor::OnLBdown(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	xstart = xend = pt.x;
	ystart = yend = pt.y;
}
void RectEditor::OnMouseMove(HWND hWnd) {
	if (!xstart) return;
	HPEN hPenOld, hPen;
	HDC hdc;

	hdc = GetDC(hWnd);
	SetROP2(hdc, R2_NOTXORPEN);
	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	hPenOld = (HPEN)SelectObject(hdc, hPen);

	long xStart = xend - (xend - xstart); 	 
	long yStart = yend - (yend - ystart);
	Rectangle(hdc, xStart, yStart, xend, yend);

	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	xend = pt.x; 
	yend = pt.y;

	xStart = xend - (xend - xstart); 	 
	yStart = yend - (yend - ystart);
	Rectangle(hdc, xStart, yStart, xend, yend);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc);
}

void RectEditor::OnLBup(HWND hWnd) {
	pcshape[index] = new RectShape;
	pcshape[index]->Set(xstart, ystart, xend, yend);
	index++;
	InvalidateRect(hWnd, NULL, TRUE);
	xstart = NULL;
};