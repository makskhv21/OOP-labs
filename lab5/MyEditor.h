#pragma once
#include "shape.h"
#include "point_shape.h"
#include "line_shape.h"
#include "rect_shape.h"
#include "ellipse_shape.h"

#include "cube_shape.h"
#include "lineOO_shape.h"
#include "Toolbar.h"
#include <string>

#define MY_SHAPE_ARRAY_SIZE		103

class MyEditor
{
private:
	static MyEditor* p_instance;
	MyEditor() {}
	MyEditor(const MyEditor&);
	MyEditor& operator = (MyEditor&);

	ToolBar MaksToolBar;
	Shape** pshape = new Shape * [MY_SHAPE_ARRAY_SIZE] {};;
	int i = 0;
	Shape* parentShape = NULL;
	long xstart = 0, ystart = 0, xend = 0, yend = 0;
public:
	static MyEditor* getInstance();

	void Start(Shape*, HWND, UINT, UINT, LPARAM);
	void OnLBdown(HWND);
	std::wstring OnLBup(HWND);
	void RemoveItem(int);
	void OnMouseMove(HWND);
	void OnPaint(HWND, int);
	void OnCreate(HWND, HINSTANCE);
	void OnNotify(HWND, WPARAM, LPARAM);
	void OnSize(HWND);
};