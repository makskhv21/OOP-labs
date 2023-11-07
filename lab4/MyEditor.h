#pragma once
#include "shape.h"
#define MY_SHAPE_ARRAY_SIZE 103

class MyEditor
{
private:
	static Shape** pcshape;
	Shape* currentShape;
	static int ShapeIndex;
	POINT pt;
	bool isCurrentlyEditing;

public:
	MyEditor(void);
	~MyEditor();
	void Start(HWND, Shape*);
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
	void OnPaint(HWND);
};
