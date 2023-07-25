#pragma once
#include"Novice.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include<time.h>

#define maxParticle 100

enum PARTICLESTYLE
{
	mowa,
	fire,
	snow,
	spiral,
	spirit,
	smoke,
	fireball,
};

struct f_Vector2
{
	float x, y;
};

struct pcl_Object
{
	f_Vector2 Pos;
	f_Vector2 Speed;
	f_Vector2 Scale;

	float theta;
	int time;
	int radius;
	float speed;
	bool active;
	int color;
	int alpha;
	int endColor;
};

class Particle
{
private:
	int active_;
	int mouseX;
	int mouseY;
	float speed_;
	int time_;
	BlendMode blend;
	f_Vector2 Scale_;
	int EmitterMax_;
	f_Vector2 pcl_pos_;
	pcl_Object pcl_object_[maxParticle];

public:
	unsigned currTime = time(nullptr);
	Particle(int EmitterMax, float posX, float posY, int times, int radius, float scale, int speed, int color);
	~Particle();
	void Update(int type);
	void Draw(int graph);
};

