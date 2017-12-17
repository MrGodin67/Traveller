#pragma once
#include "Components.h"
class Path :
	public Component
{
	Transform* transform;
	std::vector<Vec2f> positions;
	bool moving = true;
	bool done = false;
	std::size_t currentIndex = 0llu;
public:
	Path();
	Path(const std::vector<Vec2f>& data);
	virtual ~Path();
	virtual void Init()override;
	virtual void Update(const float& dt)override;
	virtual void Draw()override;
	bool Completed()const;
	bool Moving()const;
	void Moving(const bool& value);
};

