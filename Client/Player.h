#pragma once
#include "ClientInterface.h"
#include "Map.h"
#include "Easing.h"
#include "w_Ranged.h"
#include "w_Melee.h"
#include"Animation.h"


#define P_BLOCK_SIZE 64
#define P_BLOCK_SIZEX 48

#define maxShakeTime 60
#define PlayerCoolDown 60;

class Player : public ClientInterface
{
private:
	//Graph
	int graph1_; // RIGHT face
	int graph2_; // LEFT face
	
	
	ShakeElement p_Shake;
	Square9 p_Square;
	Square9 p_SquareCells;
	Easing p_Easing;
	Vector2 p_w_Pos;

	int attackCounter = 0;

	//Bool Player movement
	bool p_isShooting = false;
	bool p_isMelee = false;
	bool p_isTackle = false;
	bool p_canDash[2]; //0 right 1 left
	bool p_isJump = false;
	bool p_win = false;
	bool p_lose = false;

	float fElapsedTime = 0.0f;
	float fFrameTimer = 0;
	int nFrameCount = 0;
	int nLastFPS = 0;
	std::chrono::time_point<std::chrono::system_clock> m_tp1, m_tp2;

	Animation* p_animation = new Animation(mapObjects[nPlayerID].animObj);
	w_Ranged* p_range = new w_Ranged(1.0f, 150.0f, mapObjects[nPlayerID].bullet, mapObjects[nPlayerID].p_Pos, mapObjects[nPlayerID].facing);
	w_Melee* p_melee = new w_Melee(mapObjects[nPlayerID].facing);
public:
	
	

	Map map;
	Player();
	~Player();
	void Init();
	void Move2(char* keys, char* preKeys, float fElapsedTime);
	void CollisionCheck(float fElapsedTime);
	void TilesCheck(float posX, float posY);
	void Shake(int max, int min);
	void Update(char* keys, char* preKeys);
	void AnimationController(char* keys, char* preKeys);
	void Respawn();
	Vector2 GetScreenPos();
	void Draw();

	bool GetWin() { return p_win; };
	bool GetLose() { return p_lose; };
	void SetWin(bool val) { p_win = val; mapObjects[nPlayerID].win = val; };
	void SetLose(bool val) { p_lose = val;  mapObjects[nPlayerID].lose = val;};
	//Skill
	void Skill(char* keys, char* preKeys);

	
};


