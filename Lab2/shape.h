#pragma once
#include <windows.h>
#include <iostream>

class Shape
{
protected:
	long xs1, ys1, xs2, ys2;
	long color, colorfill;
public:
	void Set(long x1, long y1, long x2, long y2);
	virtual void Show(HDC) = 0;
};