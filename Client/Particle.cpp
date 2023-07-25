#include "Particle.h"

Particle::Particle(int EmitterMax, float posX, float posY, int times, int radius, float scale, int speed, int color)
{
	this->EmitterMax_ = EmitterMax;
	this->pcl_pos_.x = posX;
	this->pcl_pos_.y = posY;
	this->Scale_.x = scale;
	this->Scale_.y = scale;
	this->speed_ = speed;
	this->time_ = times;

	this->blend = BlendMode::kBlendModeNone;
	srand(currTime);


	for (int i = 0; i < EmitterMax; i++)
	{
		pcl_object_[i].time = rand() % times / 2 + times;
		pcl_object_[i].Pos.x = posX;
		pcl_object_[i].Pos.y = posY;
		pcl_object_[i].radius = radius;
		pcl_object_[i].theta = (rand() % 720 - 360) / 100.0f;
		pcl_object_[i].speed = speed;
		pcl_object_[i].Scale.x = scale;
		pcl_object_[i].Scale.y = scale;
		pcl_object_[i].active = false;
		pcl_object_[i].color = color;
		pcl_object_[i].alpha = 0x000000CC;
		pcl_object_[i].endColor = pcl_object_[i].color + pcl_object_[i].alpha;
	}
	active_ = rand() % EmitterMax;
	pcl_object_[active_].active = true;
}

Particle::~Particle()
{
}

void Particle::Update(int type)
{
	if (type == mowa)
	{
		active_ = rand() % EmitterMax_;
		pcl_object_[active_].active = true;
		//Mouse
		Novice::GetMousePosition(&mouseX, &mouseY);
		if (Novice::IsPressMouse(0))
		{
			pcl_pos_.x = mouseX;
			pcl_pos_.y = mouseY;
		}

		Novice::ScreenPrintf(10, 10, "Mode : 1.Screen2.Multiply3.Add4.Substract5.CountOfBlend6.Normal7.none");
		//Input
		
		for (size_t i = 0; i < EmitterMax_; i++)
		{
			if (pcl_object_[i].active)
			{

				pcl_object_[i].Scale.x += 0.001f;
				pcl_object_[i].Scale.y += 0.001f;
				pcl_object_[i].alpha -= 2.0f;
				pcl_object_[i].Pos.x += sinf(pcl_object_[i].theta) * pcl_object_[i].speed;
				pcl_object_[i].Pos.y += cosf(pcl_object_[i].theta) * pcl_object_[i].speed;
				pcl_object_[i].time--;
				if (pcl_object_[i].alpha <= 0.0f)
				{
					pcl_object_[i].alpha = 0.0f;
				}
				if (pcl_object_[i].time <= 0)
				{
					pcl_object_[i].Pos = pcl_pos_;
					pcl_object_[i].theta = (rand() % 720 - 360) / 100.0f;
					pcl_object_[i].speed = speed_;
					pcl_object_[i].time = rand() % time_ / 2 + time_;
					pcl_object_[i].Scale.x = Scale_.x;
					pcl_object_[i].Scale.y = Scale_.y;
					pcl_object_[i].alpha = 0x000000CC;
				}
			}
		}
	}

	if (type == snow)
	{
		active_ = rand() % EmitterMax_;
		pcl_object_[active_].active = true;
		blend = BlendMode::kBlendModeAdd;

		for (size_t i = 0; i < EmitterMax_; i++)
		{
			if (pcl_object_[i].active)
			{
				pcl_object_[i].alpha -= 0.1f;
				pcl_object_[i].Pos.x += 0.1f * pcl_object_[i].speed;
				pcl_object_[i].Pos.y += 2.0f;
				pcl_object_[i].time--;
				if (pcl_object_[i].alpha <= 0.0f)
				{
					pcl_object_[i].alpha = 0.0f;
				}
				if (pcl_object_[i].Pos.y >= 720)
				{
					pcl_object_[i].Pos.x = rand() % 1280;
					pcl_object_[i].Pos.y = rand() % 10;
					pcl_object_[i].speed = (rand() % 8 - 4) / 20.0f;
					//pcl_object_[i].time = rand() % time_ / 2 + time_;
					pcl_object_[i].Scale.x = (rand() % 5) / 10.0f;
					pcl_object_[i].Scale.y = (rand() % 5) / 10.0f;
					pcl_object_[i].alpha = 0x000000CC;
				}
			}
			if (!pcl_object_[i].active)
			{
				pcl_object_[i].speed = rand() % 2 - 1;
				pcl_object_[i].Pos.x = rand() % 1280;
				pcl_object_[i].Pos.y = rand() % 10;
				pcl_object_[i].Scale.x = (float)((rand() % 5) / 10.0f);
				pcl_object_[i].Scale.y = (float)((rand() % 5) / 10.0f);
			}
		}

	}

	if (type == spiral)
	{
		active_ = rand() % EmitterMax_;
		pcl_object_[active_].active = true;
		blend = BlendMode::kBlendModeAdd;

		for (size_t i = 0; i < EmitterMax_; i++)
		{
			if (pcl_object_[i].active)
			{
				//pcl_object_[i].alpha -= 0.01f;
				pcl_object_[i].theta += 0.1f;
				pcl_object_[i].Pos.x += pcl_object_[i].theta * 0.1f;
				pcl_object_[i].Pos.y += 2.0f;
				pcl_object_[i].time--;
				if (pcl_object_[i].alpha <= 0.0f)
				{
					pcl_object_[i].alpha = 0.0f;
				}
				if (pcl_object_[i].Pos.y >= 720)
				{
					pcl_object_[i].Pos.x = rand() % 200+100;
					pcl_object_[i].Pos.y = rand() % 10;
					pcl_object_[i].speed = (rand() % 8 - 4) / 20.0f;
					//pcl_object_[i].time = rand() % time_ / 2 + time_;
					pcl_object_[i].Scale.x = (rand() % 20) / 10.0f;
					pcl_object_[i].Scale.y = (rand() % 20) / 10.0f;
					pcl_object_[i].alpha = 0x000000CC;
					pcl_object_[i].theta = 0.0f;
				}
			}
			if (!pcl_object_[i].active)
			{
				pcl_object_[i].speed = rand() % 2 - 1;
				pcl_object_[i].Pos.x = rand() % 200 + 600;
				pcl_object_[i].Pos.y = rand() % 720;
				pcl_object_[i].Scale.x = (float)((rand() % 10) / 10.0f);
				pcl_object_[i].Scale.y = (float)((rand() % 10) / 10.0f);
			}
		}

	}

	if (type == spirit)
	{
		blend = BlendMode::kBlendModeAdd;
		active_ = rand() % EmitterMax_;
		pcl_object_[active_].active = true;
		
		for (size_t i = 0; i < EmitterMax_; i++)
		{
			if (pcl_object_[i].active)
			{
				pcl_object_[i].theta++;
				//pcl_object_[i].Scale.x -= 0.005f;

				//pcl_object_[i].Scale.y += 0.001f;
				pcl_object_[i].alpha -= 1.0f;
				//pcl_object_[i].Pos.x += sinf(pcl_object_[i].theta) * pcl_object_[i].speed;
				pcl_object_[i].Pos.x += 0.01f;
				pcl_object_[i].Pos.y -= pcl_object_[i].speed;
				pcl_object_[i].time--;

				if (pcl_object_[i].Scale.x <= 0)
				{
					pcl_object_[i].Scale.x = 0;
				}
				if (pcl_object_[i].alpha <= 0.0f)
				{
					pcl_object_[i].alpha = 0.0f;
				}
				if (pcl_object_[i].Pos.y <= 300)
				{
					pcl_object_[i].Pos = pcl_pos_;
					pcl_object_[i].Pos.x = (rand() % 25 - 10) + pcl_pos_.x;
					pcl_object_[i].theta = (rand() % 720 - 360) / 100.0f;
					pcl_object_[i].speed = speed_;
					pcl_object_[i].time = rand() % time_ / 2 + time_;
					pcl_object_[i].Scale.x = (float)((rand() % 5) / 10.0f);
					pcl_object_[i].Scale.y = (float)((rand() % 10) / 10.0f);
					pcl_object_[i].alpha = rand() % 256;
					pcl_object_[i].theta = 0.0f;
				}
				if (!pcl_object_[i].active)
				{
					pcl_object_[i].theta = (rand() % 720 - 360) / 100.0f;
					pcl_object_[i].Pos.x = (rand() % 25 - 10) + pcl_pos_.x;
					pcl_object_[i].Scale.x = (float)((rand() % 5) / 10.0f);
					pcl_object_[i].Scale.y = (float)((rand() % 10) / 10.0f);
				}
			}
		}
	}


	if (type == fire)
	{
		blend = BlendMode::kBlendModeAdd;
		active_ = rand() % EmitterMax_;
		pcl_object_[active_].active = true;
		//Mouse

		for (int i = 0; i < 10; i++)
		{
			pcl_object_[i].Pos = pcl_pos_;
		}
		for (int i = 10; i < 20; i++)
		{
			pcl_object_[i].theta = (rand() % 10 - 5) / 100.0f;
			if (pcl_object_[i].active)
			{
				pcl_object_[i].alpha -= 5.0f;
				pcl_object_[i].Pos.x += sinf(pcl_object_[i].theta) * pcl_object_[i].speed;
				pcl_object_[i].Pos.x += cosf(pcl_object_[i].theta) * 0.01f;
				pcl_object_[i].Pos.y -= pcl_object_[i].speed;
				pcl_object_[i].time--;

				if (pcl_object_[i].Scale.x <= 0)
				{
					pcl_object_[i].Scale.x = 0;
				}
				if (pcl_object_[i].alpha <= 0.0f)
				{
					pcl_object_[i].alpha = 0.0f;
				}
				if (pcl_object_[i].alpha <= 0.0f)
				{
					pcl_object_[i].Pos = pcl_pos_;
					pcl_object_[i].theta = (rand() % 10 - 5) / 100.0f;
					pcl_object_[i].speed = speed_;
					pcl_object_[i].Scale.x = Scale_.x;
					//pcl_object_[i].Scale.x = (float)((rand() % 5) / 10.0f);
					pcl_object_[i].Scale.y = (float)((rand() % 10) / 10.0f);
					pcl_object_[i].alpha = rand() % 256;
				}

			}

		}

		for (int i = 20; i < EmitterMax_; i++)
		{
			pcl_object_[i].theta = (rand() % 10 - 5) / 100.0f;
			if (pcl_object_[i].active)
			{
				pcl_object_[i].alpha -= 1.0f;
				pcl_object_[i].Pos.x += sinf(pcl_object_[i].theta) * pcl_object_[i].speed;
				pcl_object_[i].Pos.x += cosf(pcl_object_[i].theta) * 0.01f;
				pcl_object_[i].Pos.y -= pcl_object_[i].speed;
				pcl_object_[i].time--;

				if (pcl_object_[i].Scale.x <= 0)
				{
					pcl_object_[i].Scale.x = 0;
				}
				if (pcl_object_[i].alpha <= 0.0f)
				{
					pcl_object_[i].alpha = 0.0f;
				}
				if (pcl_object_[i].Pos.y <= 0 || !pcl_object_[i].active)
				{
					pcl_object_[i].Pos = pcl_pos_;
					pcl_object_[i].Pos.x = (rand() % 25 - 10) + pcl_pos_.x;
					pcl_object_[i].theta = (rand() % 10 - 5) / 100.0f;
					pcl_object_[i].speed = speed_;
					pcl_object_[i].time = rand() % time_ / 2 + time_;
					pcl_object_[i].Scale.x = Scale_.x;
					//pcl_object_[i].Scale.x = (float)((rand() % 5) / 10.0f);
					pcl_object_[i].Scale.y = (float)((rand() % 10) / 10.0f);
					pcl_object_[i].alpha = rand() % 256;
				}

			}

		}
	}

	if (type == fireball)
	{
		blend = BlendMode::kBlendModeAdd;
		active_ = rand() % EmitterMax_;
		pcl_object_[active_].active = true;
		//Mouse

		for (int i = 0; i < 10; i++)
		{
			pcl_object_[i].Pos.x++;
			pcl_object_[i].Pos.y = pcl_pos_.y;
		}
		for (int i = 10; i < 20; i++)
		{
			pcl_object_[i].theta = (rand() % 10 - 5) / 100.0f;
			if (pcl_object_[i].active)
			{
				pcl_object_[i].alpha -= 5.0f;
				pcl_object_[i].Pos.y += sinf(pcl_object_[i].theta) * pcl_object_[i].speed;
				pcl_object_[i].Pos.y += cosf(pcl_object_[i].theta) * 0.01f;
				pcl_object_[i].Pos.x -= pcl_object_[i].speed;
				pcl_object_[i].time--;

				if (pcl_object_[i].Scale.x <= 0)
				{
					pcl_object_[i].Scale.x = 0;
				}
				if (pcl_object_[i].alpha <= 0.0f)
				{
					pcl_object_[i].alpha = 0.0f;
				}
				if (pcl_object_[i].alpha <= 0.0f)
				{
					pcl_object_[i].Pos.x++;
					//pcl_object_[i].Pos.y = (rand() % 25 - 10) + pcl_pos_.y;
					pcl_object_[i].theta = (rand() % 10 - 5) / 100.0f;
					pcl_object_[i].speed = speed_;
					pcl_object_[i].Scale.x = Scale_.x;
					//pcl_object_[i].Scale.x = (float)((rand() % 5) / 10.0f);
					pcl_object_[i].Scale.y = (float)((rand() % 10) / 10.0f);
					pcl_object_[i].alpha = rand() % 256;
				}

			}

		}

		for (int i = 20; i < EmitterMax_; i++)
		{
			pcl_object_[i].theta = (rand() % 10 - 5) / 100.0f;
			if (pcl_object_[i].active)
			{
				pcl_object_[i].alpha -= 1.0f;
				pcl_object_[i].Pos.y += sinf(pcl_object_[i].theta) * pcl_object_[i].speed;
				pcl_object_[i].Pos.y += cosf(pcl_object_[i].theta) * 0.01f;
				pcl_object_[i].Pos.x -= pcl_object_[i].speed;
				pcl_object_[i].time--;

				if (pcl_object_[i].Scale.x <= 0)
				{
					pcl_object_[i].Scale.x = 0;
				}
				if (pcl_object_[i].alpha <= 0.0f)
				{
					pcl_object_[i].alpha = 0.0f;
				}
				if (pcl_object_[i].Pos.y <= 0 || !pcl_object_[i].active)
				{
					pcl_object_[i].Pos = pcl_pos_;
					pcl_object_[i].Pos.x++;
					pcl_object_[i].Pos.y = (rand() % 25 - 10) + pcl_pos_.y;
					pcl_object_[i].theta = (rand() % 10 - 5) / 100.0f;
					pcl_object_[i].speed = speed_;
					pcl_object_[i].time = rand() % time_ / 2 + time_;
					pcl_object_[i].Scale.x = Scale_.x;
					//pcl_object_[i].Scale.x = (float)((rand() % 5) / 10.0f);
					pcl_object_[i].Scale.y = (float)((rand() % 10) / 10.0f);
					pcl_object_[i].alpha = rand() % 256;
				}

			}

		}
	}
}

void Particle::Draw(int graph)
{
	Novice::SetBlendMode(blend);
	for (int i = 0; i < EmitterMax_; i++)
	{
		if (pcl_object_[i].active)
		{
			Novice::DrawSprite(pcl_object_[i].Pos.x - pcl_object_[i].radius / 2, pcl_object_[i].Pos.y - pcl_object_[i].radius / 2, graph, pcl_object_[i].Scale.x, pcl_object_[i].Scale.x, 0, pcl_object_[i].color + pcl_object_[i].alpha);
		}
	}
}
