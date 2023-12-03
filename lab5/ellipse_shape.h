#pragma once
#include "shape.h"

class EllipseShape : virtual public Shape
{
public:
	EllipseShape(void);
	Shape* copyShape();

	std::wstring getName();
	void Draw(HDC);
	void DrawRubber(HDC);
	LPCTSTR setWindowText();
};