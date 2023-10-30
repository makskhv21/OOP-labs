#pragma once

#include <windows.h>
#include <iostream>
#include "editor.h"

class ShapeObjectsEditor
{
public:
	ShapeObjectsEditor(void);
	~ShapeObjectsEditor();

	void StartPointEditor(HWND);
	void StartLineEditor(HWND);
	void StartRectEditor(HWND);
	void StartEllipseEditor(HWND);
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
	void OnPaint(HWND);
};