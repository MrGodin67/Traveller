#pragma once
#include "Components.h"
class Animation : 
	public  Component
{
	Transform* transform;
	ID2D1Bitmap* image;
	RectF srcRect;
	Vec2f image_size;
	float transparency = 1.0f;// opague
	int frames;
	float frameSize;
	float interval;
	bool active = false;
	bool loop;
	bool done = false;
	float timer = 0.0f;
	int index = 0;
	int columns = 0;
public:
	Animation();
	Animation(ID2D1Bitmap* image, const int& frames,const float& frameSize,const float& interval,const bool& loop )
		:image(image),frames(frames),frameSize(frameSize),interval(interval),loop(loop)
	{
		image_size = { image->GetSize().width,image->GetSize().height };
		columns = (int)(image->GetSize().width / (float)frameSize);
	};
	
	~Animation();
	void Init()override;
	void Draw()override;
	void Update(const float& dt)override;
	void Fade(const float& val)override;

	void Stop();
	void Start();
	bool Done()const;
};

