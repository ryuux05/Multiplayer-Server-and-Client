#pragma once
#include"Weapon.h"
#include"Novice.h"
#include"Functions.h"

class w_Melee
{
private:
	int cooldown_ = 15;
	int comboCount = 0;
	int facing_;
	bool isAttack_ = false;
	Square hitBox_;

public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="facing"></param>
	w_Melee(int& facing);
	~w_Melee();
	void OnAttack(Square& hitBox, Vector2& pos, float size, int& facing, char* keys, char* preKeys);
	Square GetHitBox() { return hitBox_; };
	void Draw(Vector2 pos);
};

