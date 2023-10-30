#pragma once

#include "shape.h"
#include "editor.h"

#define MY_SHAPE_ARRAY_SIZE 102

extern Shape* pcshape[];

class ShapeEditor : public Editor {
protected:
	POINT pt;
	HMENU hMenu, hSubMenu;
	int index = 0;
	int ystart, xend, yend;
	int xstart = NULL;
public:
	ShapeEditor(void);
	virtual void OnLBdown(HWND) = 0;
	virtual void OnLBup(HWND) = 0;
	virtual void OnMouseMove(HWND) = 0;
	void OnPaint(HWND);
};