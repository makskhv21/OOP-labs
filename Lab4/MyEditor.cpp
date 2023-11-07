#include "framework.h"
#include "MyEditor.h"

MyEditor::MyEditor(void) {}
MyEditor::~MyEditor()
{
	delete[]pcshape;
}
Shape** MyEditor::pcshape = new Shape * [MY_SHAPE_ARRAY_SIZE] {};
int MyEditor::ShapeIndex = 0;

void MyEditor::Start(HWND hWnd, Shape* psh)
{
	currentShape = psh;
	SetWindowText(hWnd, currentShape->setWindowText());
}

void MyEditor::OnLBdown(HWND hWnd)
{
	if (currentShape)
	{
		GetCursorPos(&pt);
		ScreenToClient(hWnd, &pt);
		pcshape[ShapeIndex] = currentShape->copyShape();
		pcshape[ShapeIndex]->SetStart(pt.x, pt.y, pt.x, pt.y);
		isCurrentlyEditing = true;
	}
}

void MyEditor::OnLBup(HWND hWnd)
{
	if (currentShape)
	{
		GetCursorPos(&pt);
		ScreenToClient(hWnd, &pt);
		pcshape[ShapeIndex]->SetEnd(pt.x, pt.y);
		isCurrentlyEditing = false;
		InvalidateRect(hWnd, NULL, TRUE);
		ShapeIndex++;
	}
}

void MyEditor::OnMouseMove(HWND hWnd)
{
	if (isCurrentlyEditing && currentShape)
	{
		pcshape[ShapeIndex]->DrawRubber(hWnd);
		GetCursorPos(&pt);
		ScreenToClient(hWnd, &pt);
		pcshape[ShapeIndex]->SetEnd(pt.x, pt.y);
		pcshape[ShapeIndex]->DrawRubber(hWnd);
	}
}

void MyEditor::OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc;
	hdc = BeginPaint(hWnd, &ps);
	for (int i = 0; i < MY_SHAPE_ARRAY_SIZE; i++)
		if (pcshape[i]) pcshape[i]->Show(hdc);
	EndPaint(hWnd, &ps);
}
