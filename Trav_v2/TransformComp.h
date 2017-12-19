#pragma once
#include "Components.h"
#include "Utils2D_v2.h"
class Transform : public Component
{
	
	D2D1_MATRIX_3X2_F matTrans = D2D1::Matrix3x2F::Identity();
	D2D1_MATRIX_3X2_F matScale = D2D1::Matrix3x2F::Identity();
	D2D1_MATRIX_3X2_F matRotation = D2D1::Matrix3x2F::Identity();
	Vec2f center = { 0.0f,0.0f };
	Vec2f size = { 0.0f,0.0f };
	const float velocityCap = 6.5f;
public:
	Transform() = default;
	Transform(const Vec2f& p, const Vec2f& v, const Vec2f& s)
		:position(p), velocity(v),size(s)
	{}
	void CapVelocity()
	{
		velocity.x = std::min(velocity.x,velocityCap);
		velocity.x = std::max(velocity.x,-velocityCap);
		velocity.y = std::min(velocity.y, velocityCap);
		velocity.y = std::max(velocity.y, -velocityCap);
	}
	virtual void Update(const float& dt)override
	{
		position += velocity * acceleration * dt;
		center = Vec2f(position + (size * 0.5f));
	}
	virtual void Init()override 
	{
		center = Vec2f(position + (size * 0.5f));
	};
	Vec2f Center()const
	{
		return center;
	}
	Vec2f Dimensions()const
	{
		return size;
	}
	Vec2f Facing()
	{
		return{ matRotation._11,matRotation._12 };
	}
	RectF Rect()
	{
		return{position.x,position.y,position.x + size.width,position.y + size.height};
	}
	void Resize(const Vec2f& dimensions)
	{
		size = dimensions;
		center = Vec2f(position + (size * 0.5f));
	}
	D2D1_MATRIX_3X2_F Matrix()
	{
		Translate(matRotation);
		Translate(matScale);
		return  matTrans ;
	}
	void  Rotate(const float& angle)
	{
		matRotation = D2D1::Matrix3x2F::Rotation(angle, center.ToD2DPointF());
	
	}
	void  Rotate()
	{
		matRotation = D2D1::Matrix3x2F::Rotation(angle, center.ToD2DPointF());

	}
	void  Scale(const Vec2f& dimensions)
	{
		
		matScale = D2D1::Matrix3x2F::Scale({dimensions.width, dimensions.height	},
			center.ToD2DPointF());
	}
	void Translate(const Vec2f& offset)
	{
		matTrans = D2D1::Matrix3x2F::Translation({ offset.x,offset.y });
	}
	void Translate(const D2D1_MATRIX_3X2_F& mat)
	{
		matTrans = mat * matTrans;
	}
public:
	Vec2f position = { 0.0f,0.0f };
	Vec2f velocity = { 0.0f,0.0f };
	float acceleration = 0.0f;
	float angle = 0.0f;
	
};