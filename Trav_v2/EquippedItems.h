#pragma once
#include "Components.h"
class EquippedItems :
	public Component
{
	Transform* transform;
public:
	EquippedItems();
	~EquippedItems();
	void Init()override
	{
		transform = &owner->Get<Transform>();
	}
	void Draw()override
	{
		RectF rect = transform->Rect();

	}
};

