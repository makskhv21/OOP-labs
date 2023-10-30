#include "framework.h"
#include "point_shape.h"

void PointShape::Show(HDC hdc) {
	color = 0x00000000;
	SetPixel(hdc, xs1, ys1, color);
}