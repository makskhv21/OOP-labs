#include "ShapeEditor.h"
#include "point_shape.h"
#include "point_editor.h"
#include "Resource.h"

void PointEditor::OnMouseMove(HWND hWnd) {}

void PointEditor::OnLBdown(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	xstart = xend = pt.x;
	ystart = xend = pt.y;
}

void PointEditor::OnLBup(HWND hWnd) {
	pcshape[index] = new PointShape;
	pcshape[index]->Set(xstart, ystart, xend, yend);
	index++;
	InvalidateRect(hWnd, NULL, TRUE);
};