#pragma once


#include "Utils2D_v2.h"
class Camera 
{
	
public:
	Camera(const float& width, const float& height);
	Vec2f GetPosition()const;
	void ConfineToMap(const RectF& map_frame);
	void Resize(const float& w, const float& h);
	void UpdatePosition(const Vec2f& in_pos);
	Vec2f ConvertToWorldSpace(const Vec2f& in_pos);
	RectF Frustum()const;
	void Scroll(const Vec2f& dir);
private:
	
	Vec2f m_pos;
	Vec2f m_center;
	Vec2f m_scroll_pos;
    RectF m_mapFrame;
	RectF m_viewFrame;
	float m_screen_width;
	float m_screen_height;
};
