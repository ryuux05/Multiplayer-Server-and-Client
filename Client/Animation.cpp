#include "Animation.h"

Animation::Animation(AnimationObject animation)
{
	/*this->animation_.maxFrame = animation.maxFrame;
	this->animation_.currentFrame= animation.currentFrame;
	this->animation_.timeCount = animation.timeCount;
	this->animation_.graph = animation.graph;
	this->animation_.repeat = animation.repeat;
	this->animation_.frameTime = animation.frameTime;
	this->animation_.resetFrame = animation.resetFrame;*/
}

void Animation::RunAnimation(AnimationObject& animationObject, Vector2& pos, int size)
{
	animationObject.timeCount++;
	if (animationObject.timeCount >= animationObject.frameTime)
	{
		animationObject.currentFrame++;
		animationObject.timeCount = 0;
	}
	if (animationObject.repeat)
	{
		if (animationObject.currentFrame >= animationObject.maxFrame)
		{
			animationObject.currentFrame = animationObject.resetFrame;
		}
	}
}


