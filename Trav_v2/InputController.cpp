#include "stdafx.h"
#include "InputController.h"





InputController::InputController(Keyboard& kbd)
	:kbd(kbd)
{
}


InputController::~InputController()
{
}

void InputController::Init()
{
	transform = &owner->Get<Transform>();
}

void InputController::Update(const float & dt)
{
	Keyboard::Event kbd_event = kbd.ReadKey();
	 bool isMove = false;
	
	
		if (kbd.KeyIsPressed(VK_UP))
		{
			transform->acceleration -= speed;
			isMove = true;
		}
		if (kbd.KeyIsPressed(VK_DOWN))
		{
			transform->acceleration += speed;
			isMove = true;
		}
		if (kbd.KeyIsPressed(VK_LEFT))
		{
			transform->angle -= 1.5f;

		}
		if (kbd.KeyIsPressed(VK_RIGHT))
		{

			transform->angle += 1.5f;
		}
		
		if(!isMove)
		{
			transform->acceleration *= 0.989f;
		}
		
	transform->Rotate();
	transform->velocity = transform->Facing();
}

void InputController::DisableMovement()
{
	canMove = false;
}
