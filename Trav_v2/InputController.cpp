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
	velocity = { 0.0f,0.0f };
	if (canMove)
	{
		if (kbd.KeyIsPressed(VK_UP))
		{
			velocity.y = -1.0f;

		}
		if (kbd.KeyIsPressed(VK_DOWN))
		{
			velocity.y = 1.0f;

		}
		if (kbd.KeyIsPressed(VK_LEFT))
		{
			velocity.x = -1.0f;

		}
		if (kbd.KeyIsPressed(VK_RIGHT))
		{

			velocity.x = 1.0f;
		}
		
	}
	
	if (!canMove)
		canMove = kbd.KeyIsEmpty();//kbd_event.IsRelease();

	
	
}

void InputController::DisableMovement()
{
	canMove = false;
}
