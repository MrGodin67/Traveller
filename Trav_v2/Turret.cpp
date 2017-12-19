#include "stdafx.h"
#include "Turret.h"





Turret::~Turret()
{
}

void Turret::Init()
{
	transform = &owner->Get<Transform>();
}

void Turret::Draw()
{
	Locator::Graphics()->DrawSprite(Matrix(),
		transform->Rect().ToD2D(), m_image);
}

void Turret::Rotate(const float & angle)
{
	matRotation = D2D1::Matrix3x2F::Rotation(angle, owner->Get<Transform>().Center().ToD2DPointF());
}

void Turret::Translate(const Vec2f & offset)
{
	matTranslation =  D2D1::Matrix3x2F::Translation({ offset.x,offset.y });
}

void Turret::Update(const float & dt)
{
	angle += 1.1f;
	Rotate(angle);
}
