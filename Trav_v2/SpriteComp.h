#pragma once
#include "Components.h"
#include "Utils2D_v2.h"

struct AnimationSeq
{
	int indexY;
	int speed;
	float timer = 0.0f;
	std::vector<std::size_t> indices;
	AnimationSeq() = default;
	AnimationSeq(const std::vector<std::size_t>& indices, const int& i, const int& s)
		:indices(indices), indexY(i), speed(s)
	{}
};

class Sprite : public Component
{
	RectF srcRect;
	RectF destRect;
	ID2D1Bitmap* image;
	Transform* transform = nullptr;
	bool animated = false;
	std::unordered_map<std::string, AnimationSeq> animations;
	AnimationSeq* p_currentAnimation = nullptr;
	float transparency = 1.0f;
public:
	Sprite() = default;
	Sprite(ID2D1Bitmap& image, const RectF& srcRect  );
	virtual ~Sprite() {}
	virtual void Update(const float& dt)override;
	virtual void Init()override;
	virtual void Draw()override;
	void AddAnimationSequence(const std::string& id, const AnimationSeq& seq);
	void SetCurrentAnimationSeq(const std::string& id);
	void Fade(const float& val)override;
	void SetSourceRect(const RectF& rect);

};