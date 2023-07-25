#pragma once
#include"Weapon.h"
#include"Novice.h"

class w_Ranged
{
private:
	int w_Damage_ = 5;
	int cooldown_ = 30;
	int bulletCount_ = 0;
	static const int maxBullet_ = 5;
	Vector2 playerPos_;
	int facing_ = RIGHT;
	int reload_ = 0;

public:
	w_Ranged(int damage, int speed, Bullet* bullet, Vector2& base_pos, int facing);
	~w_Ranged();
	void OnAttack(float& fElapsedTime, char* keys, char* preKeys, Bullet* bullet, Vector2& base_pos, bool& isSquat);
	//void Draw(Bullet bullet[]);
};

