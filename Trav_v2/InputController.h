#pragma once
#include "EntityComponentSystem.h"
#include "Components.h"
#include "Keyboard.h"
class InputController :
	public Component
{
	Transform* transform = nullptr;
	Keyboard& kbd;
	std::bitset<4> keys;
	std::unordered_map<unsigned char, bool> keyDown;
	bool canMove = true;
	Vec2f velocity;
public:
	
	InputController(Keyboard& kbd);
	~InputController();
	virtual void Init()override;
	virtual void Update(const float& dt)override;
	void DisableMovement();
	Vec2f Direction()const { return velocity; }
};

