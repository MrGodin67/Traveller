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
	float angle = 0.0f;
	float speed = 0.1f;
	float maxSpeed = 10.0f;
public:
	
	InputController(Keyboard& kbd);
	~InputController();
	virtual void Init()override;
	virtual void Update(const float& dt)override;
	void DisableMovement();
	Vec2f Direction()const { return velocity; }
};

