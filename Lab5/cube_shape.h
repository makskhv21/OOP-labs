#pragma once
#include "line_shape.h"
#include "rect_shape.h"

class CubeShape : public LineShape, public RectShape
{
public:
	CubeShape(void);
	Shape* copyShape();

	std::wstring getName();
	void Draw(HDC);
	void DrawRubber(HDC);
	LPCTSTR setWindowText();
};