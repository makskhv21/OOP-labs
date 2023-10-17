#include "framework.h"
#include "shape_editor.h"
#include "shape.h"
#include "editor.h"
#include "ShapeEditor.h"
#include "point_editor.h"
#include "line_editor.h"
#include "rect_editor.h"
#include "ellipse_editor.h"

ShapeEditor* pse = NULL;

ShapeObjectsEditor::ShapeObjectsEditor(void)
{
	pse = NULL;
}

ShapeObjectsEditor::~ShapeObjectsEditor(void) 
{
	delete pse;
}

void ShapeObjectsEditor::StartPointEditor(HWND hWnd)
{
	if (pse) delete pse;
	pse = new PointEditor;
	SetWindowText(hWnd, L"Drawing mode: Крапка");
}

void ShapeObjectsEditor::StartLineEditor(HWND hWnd)
{
	if (pse) delete pse;
	pse = new LineEditor;
	SetWindowText(hWnd, L"Drawing mode: Лінія");
}

void ShapeObjectsEditor::StartRectEditor(HWND hWnd)
{
	if (pse) delete pse;
	pse = new RectEditor;
	SetWindowText(hWnd, L"Drawing mode: Прямокутник");
}

void ShapeObjectsEditor::StartEllipseEditor(HWND hWnd)
{
	if (pse) delete pse;
	pse = new EllipseEditor;
	SetWindowText(hWnd, L"Drawing mode: Еліпс");
}

void ShapeObjectsEditor::OnLBdown(HWND hWnd) {
	if (pse) pse->OnLBdown(hWnd);
}

void ShapeObjectsEditor::OnLBup(HWND hWnd) {
	if (pse) pse->OnLBup(hWnd);
}

void ShapeObjectsEditor::OnMouseMove(HWND hWnd) {
	if (pse) pse->OnMouseMove(hWnd);
}

void ShapeObjectsEditor::OnPaint(HWND hWnd) {
	if (pse) pse->OnPaint(hWnd);
}
