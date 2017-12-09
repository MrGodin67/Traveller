#pragma once
#include <d2d1.h>

class D2DPoint : public D2D1_POINT_2F
{
public:
	D2DPoint(const float& _x, const float& _y)
	{
		x = _x; y = _y;
	}
};

class D2DRect : public D2D1_RECT_F
{
public:
	D2DRect(float l, float t, float r, float b)
	{
		left = l; top = t; right = r; bottom = b;
	}
	bool Overlaps(const D2DRect& rect) const
	{
		return top <= rect.bottom && bottom >= rect.top &&
			left <= rect.right && right >= rect.left;
	}
	bool Contains(const float& x,const float& y) const
	{
		return y >= top && y <= bottom && x >= left && x <= right;
	}
};