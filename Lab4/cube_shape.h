#pragma once
#include "line_shape.h"
#include "rect_shape.h"

class CubeShape : public LineShape, public RectShape {
public:
	void Show(HDC);
	void DrawRubber(HWND);
	Shape* copyShape();
	LPCTSTR setWindowText();
};