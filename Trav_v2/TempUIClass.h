#pragma once
#include "IUserInterface.h"

class Temp :
	public IUserInterface
{

public:
	Temp();
	
	virtual ~Temp();
	// Inherited via IUserInterface
	virtual UIReturn OnMouseClick(const std::size_t & x, const std::size_t & y) override;
	virtual UIReturn OnMouseMove(const std::size_t & x, const std::size_t & y) override;
	virtual UIReturn OnKeyPress(const unsigned char & key) override;
	virtual void Draw() override;
	virtual void Update(const float & dt) override;
	virtual void SetAnchor(const UIPoint& pos);
};