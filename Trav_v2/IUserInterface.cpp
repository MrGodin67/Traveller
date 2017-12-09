#include "stdafx.h"
#include "IUserInterface.h"

UIColor IUserInterface::m_mouseOverColor;
UIColor IUserInterface::m_frameColor;
UIColor IUserInterface::m_textColor;

IUserInterface::IUserInterface()
{
}

IUserInterface::IUserInterface(const int & type, const int & returnAction)
	:m_Type(type),m_ReturnAction(returnAction)
{
}


IUserInterface::~IUserInterface()
{
}
void IUserInterface::SetColors(const UIColor & frame, const UIColor & mouseOver, const UIColor & text)
{
	m_frameColor = frame;
	m_mouseOverColor = mouseOver;
	m_textColor = text;
}

void IUserInterface::SetImage(ID2D1Bitmap * image)
{
	m_image = image;
}

bool IUserInterface::Selected() const
{
	return m_selected;
}

void IUserInterface::Selected(const bool & val)
{
	m_selected = val;
}

void IUserInterface::DrawFrame(const bool & val)
{
	m_drawFrame = val;
}

void IUserInterface::ShowHightlight(const bool & val)
{
	m_showHightlight = val;
}

UIReturn IUserInterface::OnMouseClick(const std::size_t & x, const std::size_t & y)
{
	m_selected = m_frame.Contains(x, y);
	if (m_selected)
		return{ m_Type,m_ReturnAction };

	return UIReturn();
	
}

UIReturn IUserInterface::OnMouseMove(const std::size_t & x, const std::size_t & y)
{
	m_mouseOver = m_frame.Contains(x, y);
	return UIReturn();
}
