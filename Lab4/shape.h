#pragma once
#include "framework.h"
class Shape
{
protected:
	long xs1, ys1, xs2, ys2;
public:
	void SetStart(long, long, long, long);
	void SetEnd(long, long);
	virtual void Show(HDC) = 0;
	virtual void DrawRubber(HWND) = 0;
	virtual Shape* copyShape() = 0;
	virtual LPCTSTR setWindowText() = 0;
};