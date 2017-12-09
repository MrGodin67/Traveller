
#include "stdafx.h"
#include "Camera.h"


Camera::Camera(const float& width, const float& height)
	:
	m_pos({ 0.0f,0.0f }),
	m_center({ width / 2.0f,height / 2.0f }),
	m_screen_width(width),
	m_screen_height(height)
{
	
	m_viewFrame.left = m_pos.x;
	m_viewFrame.top = m_pos.y;
	m_viewFrame.right = m_viewFrame.left + m_screen_width;
	m_viewFrame.bottom = m_viewFrame.top + m_screen_height;
	Resize(width, height);
	m_scroll_pos = m_center;
}

void Camera::Scroll(const Vec2f& dir)
{
	
	m_scroll_pos += dir;
	if (m_scroll_pos.x < m_center.x)m_scroll_pos.x = m_center.x;
	if (m_scroll_pos.x > m_mapFrame.right -m_center.x)m_scroll_pos.x = m_mapFrame.right - m_center.x;
	if (m_scroll_pos.y < m_center.y)m_scroll_pos.y = m_center.y;
	if (m_scroll_pos.y > m_mapFrame.bottom - m_center.y)m_scroll_pos.y = m_mapFrame.bottom - m_center.y;

	this->UpdatePosition(m_scroll_pos);

}


Vec2f Camera::GetPosition()const 
{ 
	return m_pos; 
}
void Camera::ConfineToMap(const RectF& map_frame) 
{ 
	m_mapFrame = map_frame; 
}

Vec2f Camera:: ConvertToWorldSpace(const Vec2f& in_pos)
{
	return Vec2f (in_pos + m_pos);
}
RectF Camera::Frustum()const
{
	return m_viewFrame;
}
void Camera::Resize(const float& w, const float& h)
{
	m_screen_width = w;
	m_screen_height = h;
	m_center = Vec2f(m_screen_width / 2, m_screen_height / 2);
	m_viewFrame.left = m_pos.x;
	m_viewFrame.top = m_pos.y;
	m_viewFrame.right = m_viewFrame.left + m_screen_width;
	m_viewFrame.bottom = m_viewFrame.top + m_screen_height;

};

void Camera::UpdatePosition(const Vec2f& in_pos)
{
	
	m_pos = in_pos  - m_center ;
	m_pos.x = std::max(m_pos.x, m_mapFrame.left);
	m_pos.y = std::max(m_pos.y, m_mapFrame.top);
	m_pos.x = std::min(m_pos.x, m_mapFrame.right - m_screen_width);
	m_pos.y = std::min(m_pos.y, (m_mapFrame.bottom - m_screen_height) );
	m_viewFrame = { m_pos.x, m_pos.y,m_pos.x + m_screen_width,m_pos.y + m_screen_height };
	
}
