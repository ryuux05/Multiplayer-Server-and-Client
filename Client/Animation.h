#pragma once
#include"..\[Server]\Common.h"
#include"Novice.h"

class Animation
{
public:
	AnimationObject animation_;

public:
	Animation(AnimationObject animation);
	~Animation();
	void RunAnimation(AnimationObject& animationObject, Vector2& pos, int size);
	void Draw();
};

