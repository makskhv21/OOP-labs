#include "shape.h"

void Shape::SetStart(long x1, long y1, long x2, long y2)
{
	xs1 = x1;
	ys1 = y1;

	xs2 = x2;
	ys2 = y2;
}

void Shape::SetEnd(long x1, long y1)
{
	xs2 = x1;
	ys2 = y1;
}