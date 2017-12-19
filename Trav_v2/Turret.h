#pragma once
#include "Components.h"
class Turret :
	public Component
{
	Transform* transform;
	D2D1_MATRIX_3X2_F matRotation = D2D1::Matrix3x2F::Identity();
	D2D1_MATRIX_3X2_F matTranslation = D2D1::Matrix3x2F::Identity();
	ID2D1Bitmap* m_image;
	float angle;
public:
	Turret(ID2D1Bitmap* image)
		:m_image(image)
	{};;
	~Turret();
	virtual void Init()override;
	virtual void Draw()override;
	void Rotate(const float& angle);
	void Translate(const Vec2f& offset);
	void Update(const float& dt);
	D2D1_MATRIX_3X2_F Matrix()
	{
		return matRotation * matTranslation;
	}

};

