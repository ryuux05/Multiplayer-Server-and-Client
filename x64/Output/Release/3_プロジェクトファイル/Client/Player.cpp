#include "Player.h"

Player::Player()
{
	Init();
	this->p_Shake.IsShaking = false;
	this->p_Shake.shakePos = { 0.0f,0.0f };
	this->p_Shake.shakeTime = maxShakeTime;

	this->p_Square = { 0 };
	this->p_SquareCells = { 0 };

	//Initialize Easing
	this->p_Easing.time = 0;
	this->p_Easing.startPos = 0;
	this->p_Easing.duration = 0.2f;
	this->p_Easing.change = 10;

	this->p_canDash[0] = false;
	this->p_canDash[1] = false;

	mapObjects[nPlayerID].p_Vel.x = 0.0f;
	mapObjects[nPlayerID].p_Vel.y = 0.0f;
	mapObjects[nPlayerID].p_OnGround = false;
	mapObjects[nPlayerID].isHitted = false;
	mapObjects[nPlayerID].win = false;
	mapObjects[nPlayerID].lose = false;

	mapObjects[nPlayerID].p_Hp.currentHp = 10.0f;

	mapObjects[nPlayerID].facing = RIGHT;
	//Count elapsedTime
	m_tp1 = std::chrono::system_clock::now();
	m_tp2 = std::chrono::system_clock::now();

	//Animation initialize

	graph1_ = Novice::LoadTexture("./Resources/player-animation.png");
	graph2_ = Novice::LoadTexture("./Resources/player-animation-reverse.png");


}

Player::~Player()
{

}

void Player::Init()
{
	ClientInterface::OnUserCreate();
}

void Player::Move2(char* keys, char* preKeys, float fElapsedTime)
{
	
	mapObjects[nPlayerID].p_Vel.x = 0.0f;
	//mapObjects[nPlayerID].p_Vel.y = 0.0f;
	//Gravity
	mapObjects[nPlayerID].p_Vel.y += 880.0f * fElapsedTime;
	
	//Clamp
	if (mapObjects[nPlayerID].p_Vel.y >= 1280.0f)
	{
		mapObjects[nPlayerID].p_Vel.y = 1280.0f;
	}

	mapObjects[nPlayerID].p_Old_Pos.x = mapObjects[nPlayerID].p_Pos.x;
	mapObjects[nPlayerID].p_Old_Pos.y = mapObjects[nPlayerID].p_Pos.y;

	if (keys[DIK_D])
	{
		mapObjects[nPlayerID].facing = RIGHT;
		mapObjects[nPlayerID].p_Vel.x = 200.0f;
	}
	if (keys[DIK_A])
	{
		mapObjects[nPlayerID].facing = LEFT;
		mapObjects[nPlayerID].p_Vel.x = -200.0f;
	}
	if (keys[DIK_W])
	{
		mapObjects[nPlayerID].p_Vel.y = -100.0f;
	}
	if (keys[DIK_S])
	{
		mapObjects[nPlayerID].p_Vel.y += 900.0f;
		mapObjects[nPlayerID].isSquat = true;
	}
	else
	{
		mapObjects[nPlayerID].isSquat = false;
	}
	if (keys[DIK_SPACE] && mapObjects[nPlayerID].canJump)
	{
		mapObjects[nPlayerID].p_OnGround = false;
		mapObjects[nPlayerID].p_Vel.y = -550.0f;
		mapObjects[nPlayerID].canJump = false;
		p_isJump = true;
	}

	if (mapObjects[nPlayerID].p_OnGround == 1)
	{
		mapObjects[nPlayerID].canJump = true;
	}
	if (keys[DIK_R])
	{
		Respawn();
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Dash
	if (p_Easing.time <= p_Easing.duration)
	{
		p_Easing.time += 0.01;
	}
	else
	{
		p_canDash[LEFT] = false;
		p_canDash[RIGHT] = false;

	}
	if (keys[DIK_Q])
	{
		p_canDash[mapObjects[nPlayerID].facing] = true;
	}
	
	if (p_canDash[LEFT])
	{
		mapObjects[nPlayerID].p_Vel.x -= EaseInOutQuad(p_Easing) * 100.0f;

	}
	else if (p_canDash[RIGHT])
	{
		mapObjects[nPlayerID].p_Vel.x += EaseInOutQuad(p_Easing) * 100.0f;
	}

	else
	{
		p_Easing.time = 0;
		p_Easing.change = 10;
		p_Easing.startPos = 0;
	}


	float p_newPosX = mapObjects[nPlayerID].p_Pos.x + mapObjects[nPlayerID].p_Vel.x * fElapsedTime;
	float p_newPosY = mapObjects[nPlayerID].p_Pos.y + mapObjects[nPlayerID].p_Vel.y * fElapsedTime;
	TilesCheck(p_newPosX, mapObjects[nPlayerID].p_Pos.y);


	//mapObjects[nPlayerID].p_OnGround = false;
	//Go left
	if (mapObjects[nPlayerID].p_Vel.x < 0)
	{
		if (map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y) / BLOCK_SIZE) + 2][(int)(p_SquareCells.middleBot.x)] == map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y) / BLOCK_SIZE) + 2][(int)(p_SquareCells.bottomLeft.x)])
		{
			if (map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y) / BLOCK_SIZE)][(int)(p_SquareCells.topLeft.x)] != NONE || map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y + P_BLOCK_SIZE) / BLOCK_SIZE)][(int)(p_SquareCells.bottomLeft.x)] != NONE || map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y + (P_BLOCK_SIZE / 2)) / BLOCK_SIZE)][(int)(p_SquareCells.middleLeft.x)] != NONE)
			{
				mapObjects[nPlayerID].p_Vel.x = 0;
			//	Novice::ScreenPrintf(50, 50, "BUMPED 11");
			}
			else
			{
				mapObjects[nPlayerID].p_Pos.x = p_newPosX;
				mapObjects[nPlayerID].animObj.repeat = true;
				mapObjects[nPlayerID].animObj.maxFrame = 9;
				mapObjects[nPlayerID].animObj.frameTime = 15;
				mapObjects[nPlayerID].animObj.resetFrame = 2;

			}
		}
		if (map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y) / BLOCK_SIZE) + 2][(int)(p_SquareCells.middleBot.x)] != NONE || map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y) / BLOCK_SIZE) + 2][(int)(p_SquareCells.middleBot.x)] != map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y) / BLOCK_SIZE) + 2][(int)(p_SquareCells.bottomLeft.x)] && (int)(mapObjects[nPlayerID].p_Pos.y) % BLOCK_SIZE == 0)
		{
			if (map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y) / BLOCK_SIZE)][(int)(p_SquareCells.topLeft.x)] != NONE || map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y + P_BLOCK_SIZE) / BLOCK_SIZE) - 1][(int)(p_SquareCells.bottomLeft.x)] != NONE || map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y + (P_BLOCK_SIZE / 2)) / BLOCK_SIZE)][(int)(p_SquareCells.middleLeft.x)] != NONE)
			{
				mapObjects[nPlayerID].p_Vel.x = 0;
				//Novice::ScreenPrintf(50, 50, "BUMPED 12");
			}
			else
			{
				mapObjects[nPlayerID].p_Pos.x = p_newPosX;
				mapObjects[nPlayerID].animObj.repeat = true;
				mapObjects[nPlayerID].animObj.maxFrame = 9;
				mapObjects[nPlayerID].animObj.frameTime = 15;
				mapObjects[nPlayerID].animObj.resetFrame = 2;
			}
		}
	}
	else if (mapObjects[nPlayerID].p_Vel.x > 0)
	{
		if (map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y) / BLOCK_SIZE) + 2][(int)(p_SquareCells.middleBot.x)] == map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y) / BLOCK_SIZE) + 2][(int)(p_SquareCells.bottomRight.x)] && map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y) / BLOCK_SIZE) + 2][(int)(p_SquareCells.bottomRight.x)] == NONE)
		{
			//Novice::ScreenPrintf(100, 100, "UP");
			if (map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y) / BLOCK_SIZE)][(int)(p_SquareCells.topRight.x)] != NONE || map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y + P_BLOCK_SIZE) / BLOCK_SIZE)][(int)(p_SquareCells.bottomRight.x)] != NONE || map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y + (P_BLOCK_SIZE / 2)) / BLOCK_SIZE)][(int)(p_SquareCells.middleRight.x)] != NONE)
			{
				mapObjects[nPlayerID].p_Vel.x = 0;
				//Novice::ScreenPrintf(50, 60, "BUMPED 21");
			}
			else
			{
				mapObjects[nPlayerID].p_Pos.x = p_newPosX;
				mapObjects[nPlayerID].animObj.repeat = true;
				mapObjects[nPlayerID].animObj.maxFrame = 9;
				mapObjects[nPlayerID].animObj.frameTime = 15;
				mapObjects[nPlayerID].animObj.resetFrame = 2;
			}
		}
		if (map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y) / BLOCK_SIZE) + 2][(int)(p_SquareCells.middleBot.x)] != NONE || map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y) / BLOCK_SIZE) + 2][(int)(p_SquareCells.middleBot.x)] != map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y) / BLOCK_SIZE) + 2][(int)(p_SquareCells.bottomRight.x)] && (int)(mapObjects[nPlayerID].p_Pos.y) % BLOCK_SIZE == 0)
		{
			//Novice::ScreenPrintf(100, 130, "down");
			if (map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y) / BLOCK_SIZE)][(int)(p_SquareCells.topRight.x)] != NONE || map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y + P_BLOCK_SIZE) / BLOCK_SIZE) - 1][(int)(p_SquareCells.bottomRight.x)] != NONE || map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y + (P_BLOCK_SIZE / 2)) / BLOCK_SIZE)][(int)(p_SquareCells.middleRight.x)] != NONE)
			{
				mapObjects[nPlayerID].p_Vel.x = 0;
				//Novice::ScreenPrintf(50, 60, "BUMPED 22");
			}
			else
			{
				mapObjects[nPlayerID].p_Pos.x = p_newPosX;
				mapObjects[nPlayerID].animObj.repeat = true;
				mapObjects[nPlayerID].animObj.maxFrame = 9;
				mapObjects[nPlayerID].animObj.frameTime = 15;
				mapObjects[nPlayerID].animObj.resetFrame = 2;
			}
		}
	}
	
	TilesCheck(mapObjects[nPlayerID].p_Pos.x, p_newPosY);
	if (mapObjects[nPlayerID].p_Vel.y < 0)//Moving up
	{
		if (map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y) / BLOCK_SIZE) + 2][(int)(p_SquareCells.middleBot.x)] != map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y) / BLOCK_SIZE) + 2][(int)(p_SquareCells.bottomLeft.x)] || map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y) / BLOCK_SIZE) + 2][(int)(p_SquareCells.middleBot.x)] != map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y) / BLOCK_SIZE)][(int)(p_SquareCells.bottomRight.x)] || map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y) / BLOCK_SIZE)][(int)(p_SquareCells.middleBot.x)] != map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y) / BLOCK_SIZE) + 2][(int)(p_SquareCells.bottomRight.x)])
		{
			if (map.Tiles[(int)(p_SquareCells.topLeft.y)][(int)((mapObjects[nPlayerID].p_Pos.x) / BLOCK_SIZE)] != NONE/*koko*/ || map.Tiles[(int)(p_SquareCells.topRight.y)][(int)((mapObjects[nPlayerID].p_Pos.x + P_BLOCK_SIZEX) / BLOCK_SIZE)] != NONE || map.Tiles[(int)(p_SquareCells.middleTop.y)][(int)((mapObjects[nPlayerID].p_Pos.x + (P_BLOCK_SIZEX / 2)) / BLOCK_SIZE)] != NONE)
			{
				//Novice::ScreenPrintf(50, 50, "BUMPED 31");
				mapObjects[nPlayerID].p_Vel.y = 0;
			}
			else
			{
				mapObjects[nPlayerID].p_Pos.y = p_newPosY;
			}
		}
		else if (map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y) / BLOCK_SIZE) + 2][(int)(p_SquareCells.middleBot.x)] == map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y) / BLOCK_SIZE) + 2][(int)(p_SquareCells.bottomLeft.x)] || map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y) / BLOCK_SIZE) + 2][(int)(p_SquareCells.middleBot.x)] == map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y) / BLOCK_SIZE) + 2][(int)(p_SquareCells.bottomRight.x)])
		{
			if (map.Tiles[(int)(p_SquareCells.topLeft.y)][(int)((mapObjects[nPlayerID].p_Pos.x) / BLOCK_SIZE)] != NONE || map.Tiles[(int)(p_SquareCells.topRight.y)][(int)((mapObjects[nPlayerID].p_Pos.x + P_BLOCK_SIZEX) / BLOCK_SIZE) - 1] != NONE || map.Tiles[(int)(p_SquareCells.middleTop.y)][(int)((mapObjects[nPlayerID].p_Pos.x + (P_BLOCK_SIZEX / 2)) / BLOCK_SIZE)] != NONE)
			{
				//Novice::ScreenPrintf(50, 50, "BUMPED 32");
				mapObjects[nPlayerID].p_Vel.y = 0;
				//mapObjects[nPlayerID].p_Vel.x = 0;
			}
			else
			{
				mapObjects[nPlayerID].p_Pos.y = p_newPosY;
			}
		}
	}
	else if(mapObjects[nPlayerID].p_Vel.y > 0)
	{
		if (map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y) / BLOCK_SIZE) + 2][(int)(p_SquareCells.middleBot.x)] != map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y) / BLOCK_SIZE) + 2][(int)(p_SquareCells.bottomLeft.x)] || map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y) / BLOCK_SIZE) + 2][(int)(p_SquareCells.middleBot.x)] != map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y) / BLOCK_SIZE)][(int)(p_SquareCells.bottomRight.x)] || map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y) / BLOCK_SIZE) + 2][(int)(p_SquareCells.middleBot.x)] != map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y) / BLOCK_SIZE) + 2][(int)(p_SquareCells.bottomRight.x)])
		{
			if (map.Tiles[(int)(p_SquareCells.bottomLeft.y)][(int)((mapObjects[nPlayerID].p_Pos.x) / BLOCK_SIZE)] != NONE || map.Tiles[(int)(p_SquareCells.bottomRight.y)][(int)((mapObjects[nPlayerID].p_Pos.x + P_BLOCK_SIZEX) / BLOCK_SIZE)] != NONE /*koko*/ || map.Tiles[(int)(p_SquareCells.middleBot.y)][(int)((mapObjects[nPlayerID].p_Pos.x + (P_BLOCK_SIZEX / 2)) / BLOCK_SIZE)] != NONE)
			{
				mapObjects[nPlayerID].p_Vel.y = 0;
				//Novice::ScreenPrintf(50, 50, "BUMPED 41");
				mapObjects[nPlayerID].p_OnGround = true;
			}
			else
			{
				mapObjects[nPlayerID].p_Pos.y = p_newPosY;
			}
		}
		else if (map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y) / BLOCK_SIZE) + 2][(int)(p_SquareCells.middleBot.x)] == map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y) / BLOCK_SIZE) + 2][(int)(p_SquareCells.bottomLeft.x)] || map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y) / BLOCK_SIZE) + 2][(int)(p_SquareCells.middleBot.x)] == map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y) / BLOCK_SIZE) + 2][(int)(p_SquareCells.bottomRight.x)])
		{
			if (map.Tiles[(int)(p_SquareCells.bottomLeft.y)][(int)((mapObjects[nPlayerID].p_Pos.x) / BLOCK_SIZE)] != NONE || map.Tiles[(int)(p_SquareCells.bottomRight.y)][(int)((mapObjects[nPlayerID].p_Pos.x + P_BLOCK_SIZEX) / BLOCK_SIZE) - 1] != NONE || map.Tiles[(int)(p_SquareCells.middleBot.y)][(int)((mapObjects[nPlayerID].p_Pos.x + (P_BLOCK_SIZEX / 2)) / BLOCK_SIZE)] != NONE)
			{
				mapObjects[nPlayerID].p_Vel.y = 0;
				//mapObjects[nPlayerID].p_Vel.x = 0;
				//Novice::ScreenPrintf(50, 50, "BUMPED 42");
				mapObjects[nPlayerID].p_OnGround = true;
			}
			else
			{
				mapObjects[nPlayerID].p_Pos.y = p_newPosY;
			}
		}


	}

	//Dash
	if (p_Easing.time <= p_Easing.duration)
	{
		p_Easing.time += 0.01;
	}
	else
	{
		p_canDash[LEFT] = false;
		p_canDash[RIGHT] = false;

	}

	if (p_canDash[LEFT])
	{
		mapObjects[nPlayerID].p_Vel.x = -200.0f;

	}
	else if (p_canDash[RIGHT])
	{
		mapObjects[nPlayerID].p_Vel.x = -200.0f;
	}

	else
	{
		p_Easing.time = 0;
		p_Easing.change = 10;
		p_Easing.startPos = 0;
	}

}

void Player::CollisionCheck(float fElapsedTime)
{
	for (auto& object1 : mapObjects)
	{
		for (auto& object2 : mapObjects)
		{
			Square hitBox1_ = MakeSquare(object1.second.p_Pos, { P_BLOCK_SIZEX, P_BLOCK_SIZE });
			Square hitBox2_ = MakeSquare(object2.second.p_Pos, { P_BLOCK_SIZEX, P_BLOCK_SIZE });

			if (object1.second.isSquat)
			{
				Square hitBox1_ = MakeSquare({ object1.second.p_Pos.x, object1.second.p_Pos.y + 32}, { P_BLOCK_SIZEX, P_BLOCK_SIZE - 32 });
			}
			if (object2.second.isSquat)
			{
				Square hitBox2_ = MakeSquare({ object2.second.p_Pos.x, object2.second.p_Pos.y + 32 }, { P_BLOCK_SIZEX, P_BLOCK_SIZE - 32 });
			}

			if (object1.first != object2.first && object1.first != 0 && object2.first != 0)
			{
				if (object2.second.p_Pos.x <= object1.second.p_Pos.x + P_BLOCK_SIZEX && object2.second.p_Pos.x + P_BLOCK_SIZEX >= object1.second.p_Pos.x && object2.second.p_Pos.y <= object1.second.p_Pos.y + P_BLOCK_SIZE && object2.second.p_Pos.y + P_BLOCK_SIZE >= object1.second.p_Pos.y)
				{
					object1.second.color = RED;
					object2.second.color = RED;
				}
				else
				{
					object1.second.color = WHITE;
					object2.second.color = WHITE;
				}
				if (s_s_CollisionCheck(object1.second.melee.hitBox_, hitBox2_))
				{
					object2.second.color = RED;
					object2.second.p_Hp.receivedDamage = 1.0f;
					object2.second.isHitted = true;
				//	Novice::ScreenPrintf(10, 300, "HITTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT");
				}

				for (int i = 0; i < 5; i++)
				{
					if(object1.second.bullet[i].isShooting[0] || object1.second.bullet[i].isShooting[1])
					if (object2.second.p_Pos.x <= object1.second.bullet[i].w_Pos.x + 5 && object2.second.p_Pos.x + P_BLOCK_SIZEX >= object1.second.bullet[i].w_Pos.x && object2.second.p_Pos.y <= object1.second.bullet[i].w_Pos.y + 5 && object2.second.p_Pos.y + P_BLOCK_SIZE >= object1.second.bullet[i].w_Pos.y)
					{
						object2.second.p_Hp.receivedDamage = 1.0f;
						object2.second.color = RED;
						object2.second.isHitted = true;
						//Novice::ScreenPrintf(10, 300, "Bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbullettttttttttttttttttttttttttttttttttttttt");
					}
				}
				if (object2.second.lose)
				{
					object1.second.win = true;
				}
			}
		}
	}

	//Bullet collision
	
	

	
	////////////////////////////////////////////////////////////
	//border
	if (mapObjects[nPlayerID].p_Pos.x >= 1230)
	{
		mapObjects[nPlayerID].p_Pos.x = 1230;
	}
	else if (mapObjects[nPlayerID].p_Pos.x <= 0)
	{
		mapObjects[nPlayerID].p_Pos.x = 0;
	}
	if (mapObjects[nPlayerID].p_Pos.y >= 720)
	{
		mapObjects[nPlayerID].p_Pos.y = 720;
	}
	else if (mapObjects[nPlayerID].p_Pos.y <= 0)
	{
		mapObjects[nPlayerID].p_Pos.y = 0;
	}
	////////////////////////////////////////////////////////////////
}

void Player::TilesCheck(float posX, float posY)
{
	//Square
	p_Square.topLeft.x = posX;
	p_Square.topLeft.y = posY;
	p_Square.bottomLeft.x = posX;
	p_Square.bottomLeft.y = posY + P_BLOCK_SIZE - 1.0f;
	p_Square.topRight.x = posX + P_BLOCK_SIZEX - 1.0f;
	p_Square.topRight.y = posY;
	p_Square.bottomRight.x = posX + P_BLOCK_SIZEX - 1.0f;
	p_Square.bottomRight.y = posY + P_BLOCK_SIZE - 1.0f;

	p_Square.middleTop.x = posX + (P_BLOCK_SIZEX / 2) - 1.0f;
	p_Square.middleTop.y = posY;

	p_Square.middleBot.x = posX + (P_BLOCK_SIZEX / 2) - 1.0f;
	p_Square.middleBot.y = posY + P_BLOCK_SIZE - 1.0f;

	p_Square.middleLeft.x = posX;
	p_Square.middleLeft.y = posY + (P_BLOCK_SIZE / 2) - 1.0f;

	p_Square.middleRight.x = posX + P_BLOCK_SIZEX - 1.0f;
	p_Square.middleRight.y = posY + (P_BLOCK_SIZE / 2) - 1.0f;

	p_Square.middle.x = posX + P_BLOCK_SIZE - 1.0f;
	p_Square.middle.y = posY + P_BLOCK_SIZE - 1.0f;
	

	//square in cells
	p_SquareCells.topLeft.y = floor(p_Square.topLeft.y / BLOCK_SIZE);
	p_SquareCells.topLeft.x = floor(p_Square.topLeft.x / BLOCK_SIZE);
	p_SquareCells.bottomLeft.y = floor(p_Square.bottomLeft.y / BLOCK_SIZE);
	p_SquareCells.bottomLeft.x = floor(p_Square.bottomLeft.x / BLOCK_SIZE);
	p_SquareCells.topRight.y = floor(p_Square.topRight.y / BLOCK_SIZE);
	p_SquareCells.topRight.x = floor(p_Square.topRight.x / BLOCK_SIZE);
	p_SquareCells.bottomRight.y = floor(p_Square.bottomRight.y / BLOCK_SIZE);
	p_SquareCells.bottomRight.x = floor(p_Square.bottomRight.x / BLOCK_SIZE);

	p_SquareCells.middleTop.x = floor(p_Square.middleTop.x / BLOCK_SIZE);
	p_SquareCells.middleTop.y = floor(p_Square.middleTop.y / BLOCK_SIZE);

	p_SquareCells.middleBot.x = floor(p_Square.middleBot.x / BLOCK_SIZE);
	p_SquareCells.middleBot.y = floor(p_Square.middleBot.y / BLOCK_SIZE);

	p_SquareCells.middleLeft.x = floor(p_Square.middleLeft.x / BLOCK_SIZE);
	p_SquareCells.middleLeft.y = floor(p_Square.middleLeft.y / BLOCK_SIZE);

	p_SquareCells.middleRight.x = floor(p_Square.middleRight.x / BLOCK_SIZE);
	p_SquareCells.middleRight.y = floor(p_Square.middleRight.y / BLOCK_SIZE);

	p_SquareCells.middle.x = floor(p_Square.middle.x / BLOCK_SIZE);
	p_SquareCells.middle.x = floor(p_Square.middle.y / BLOCK_SIZE);

}

void Player::Shake(int max, int min)
{
	if (p_Shake.IsShaking == true)
	{
		p_Shake.shakeTime--;
		if (p_Shake.shakeTime >= 0)
		{
			p_Shake.shakePos.x = rand() % max - min;
			p_Shake.shakePos.y = rand() % max - min;
		}
		else
		{
			p_Shake.shakePos = { 0, 0 };
			p_Shake.IsShaking = false;
		}
	}
	else
	{
		p_Shake.shakePos = { 0, 0 };
		p_Shake.shakeTime = maxShakeTime;
	}
}

void Player::Update(char* keys, char* preKeys)
{
	///////////////////////////////////////////////////////////////////////////
	//Timing																///
	//Client thing															///
	m_tp2 = std::chrono::system_clock::now();								///
	std::chrono::duration<float> elapsedTime = m_tp2 - m_tp1;				///
	m_tp1 = m_tp2;															///
																			///
	//Time per frame coefficient											///
	fElapsedTime = elapsedTime.count();										///
																			///
	//Count frame															///
	fFrameTimer += fElapsedTime;											///
	nFrameCount++;															///
	if (fFrameTimer >= 1.0f)												///
	{																		///
		nLastFPS = nFrameCount;												///
		nFrameCount = 0;													///
		fFrameTimer = 0.0f;													///
	}																		///
																			///
	/// <summary>															///
	/// 																	///
	/// </summary>															///
	/// <param name="keys"></param>											///
	/// <param name="preKeys"></param>										///
	ClientInterface::OnUserUpdate();										///
	ClientInterface::PingServer();											///
																			///
	/////////////////////////////////////////////////////////////////////////////
	//
	if (mapObjects[nPlayerID].facing == face::RIGHT)
	{
		mapObjects[nPlayerID].graph = graph1_;
	}
	else if (mapObjects[nPlayerID].facing == face::LEFT)
	{
		mapObjects[nPlayerID].graph = graph2_;
	}
	if (mapObjects[nPlayerID].win)
	{
		p_win = true;
	}

	mapObjects[nPlayerID].win = false;
	mapObjects[nPlayerID].lose = false;


	//If player it hit
	mapObjects[nPlayerID].p_Hp.cooldown--;
	if (mapObjects[nPlayerID].isHitted)
	{
		if (mapObjects[nPlayerID].p_Hp.cooldown <= 0)
		{
			p_Shake.IsShaking = true;
			p_Shake.shakeTime = 60;
			mapObjects[nPlayerID].color = RED;
			mapObjects[nPlayerID].p_Hp.currentHp -= mapObjects[nPlayerID].p_Hp.receivedDamage;
			mapObjects[nPlayerID].p_Hp.receivedDamage = 0;
			mapObjects[nPlayerID].p_Hp.cooldown = PlayerCoolDown;

		}
		mapObjects[nPlayerID].isHitted = false;
	}
	else 
	{
		mapObjects[nPlayerID].color = WHITE;
	}
	
	if (mapObjects[nPlayerID].p_Hp.currentHp < 0)
	{
		Respawn();
		p_lose = true;

		mapObjects[nPlayerID].lose = true;
		
	}
	
	
	Shake(10, 5);
	
	//Get the final position
	GetScreenPos();

	//Attack
	p_range->OnAttack(fElapsedTime, keys, preKeys, mapObjects[nPlayerID].bullet, mapObjects[nPlayerID].p_Pos, mapObjects[nPlayerID].isSquat);

	p_melee->OnAttack(mapObjects[nPlayerID].melee.hitBox_, mapObjects[nPlayerID].p_Pos, BLOCK_SIZE, mapObjects[nPlayerID].facing, keys, preKeys);
	
	//Skill
	Skill(keys, preKeys);
	//Move(keys, preKeys, fElapsedTime);
	Move2(keys, preKeys, fElapsedTime);
	CollisionCheck(fElapsedTime);
	
	p_animation->RunAnimation(mapObjects[nPlayerID].animObj, mapObjects[nPlayerID].p_Pos, P_BLOCK_SIZE);


	AnimationController(keys, preKeys);
}

void Player::AnimationController(char* keys, char* preKeys)
{

	
	if (Novice::IsTriggerMouse(0) && keys[DIK_S])
	{
		mapObjects[nPlayerID].animObj.currentFrame = 24;
		p_isTackle = true;

	}
	else if (Novice::IsTriggerMouse(1) && !keys[DIK_S])
	{
		p_isShooting = true;
		mapObjects[nPlayerID].animObj.currentFrame = 10;
	}
	else if (Novice::IsTriggerMouse(1) && keys[DIK_S])
	{
		p_isShooting = true;
		
	}
	else if (Novice::IsTriggerMouse(0) && !keys[DIK_S])
	{
		p_isMelee = true;
		mapObjects[nPlayerID].animObj.currentFrame = 17;
	}
	else
	{
		mapObjects[nPlayerID].melee.hitBox_ = { 0,0,0,0 };
	}


	//Idle animation
	mapObjects[nPlayerID].animObj.maxFrame = 2;
	mapObjects[nPlayerID].animObj.resetFrame = 0;
	mapObjects[nPlayerID].animObj.frameTime = 30;

	//Shooting animation
	if (p_isShooting)
	{
		if (mapObjects[nPlayerID].isSquat)
		{
			mapObjects[nPlayerID].animObj.currentFrame = 26;
		}
		else
		{
			mapObjects[nPlayerID].animObj.maxFrame = 14;
			mapObjects[nPlayerID].animObj.resetFrame = 10;
			mapObjects[nPlayerID].animObj.frameTime = 15;

		}

		if (!Novice::IsPressMouse(1))
		{
			p_isShooting = false;
		}
	}

	if (p_isMelee)
	{

		mapObjects[nPlayerID].animObj.maxFrame = 19;
		mapObjects[nPlayerID].animObj.resetFrame = 17;
		mapObjects[nPlayerID].animObj.frameTime = 45;

		if (!Novice::IsPressMouse(0))
		{
			p_isMelee = false;
		}
	}
	if (mapObjects[nPlayerID].isSquat && !p_isTackle && !p_isShooting)
	{
		mapObjects[nPlayerID].animObj.currentFrame = 25;
	}
	if (p_isTackle)
	{
		attackCounter++;
		mapObjects[nPlayerID].animObj.maxFrame = 24;
		mapObjects[nPlayerID].animObj.resetFrame = 24;
		mapObjects[nPlayerID].animObj.frameTime = 45;

		if (attackCounter >= 30)
		{
			attackCounter = 0;
			p_isTackle = false;
		}
	}

}

void Player::Respawn()
{
	mapObjects[nPlayerID].p_Pos = mapObjects[nPlayerID].p_respawnPos;
	mapObjects[nPlayerID].p_Hp.currentHp = mapObjects[nPlayerID].p_Hp.maxHp;
	mapObjects[nPlayerID].p_Hp.saveHp = mapObjects[nPlayerID].p_Hp.currentHp;
	mapObjects[nPlayerID].p_Vel.y = 0.0f;
	mapObjects[nPlayerID].p_Vel.x = 0.0f;
	
	mapObjects[nPlayerID].color = WHITE;
}

Vector2 Player::GetScreenPos()
{
	mapObjects[nPlayerID].p_Vel.x += mapObjects[nPlayerID].p_Acc.x;;
	mapObjects[nPlayerID].p_Vel.y += mapObjects[nPlayerID].p_Acc.y;;

	//mapObjects[nPlayerID].p_Pos.x += mapObjects[nPlayerID].p_Vel.x * fElapsedTime;
	//mapObjects[nPlayerID].p_Pos.y += mapObjects[nPlayerID].p_Vel.y * fElapsedTime;

	mapObjects[nPlayerID].p_s_Pos.x = mapObjects[nPlayerID].p_Pos.x + p_Shake.shakePos.x;
	mapObjects[nPlayerID].p_s_Pos.y = mapObjects[nPlayerID].p_Pos.y + p_Shake.shakePos.y;
	return mapObjects[nPlayerID].p_s_Pos;
}

void Player::Draw()
{

	if (ClientInterface::IsConnected())
	{
		////Draw box
		//Novice::DrawBox(p_SquareCells.topLeft.x * BLOCK_SIZE, p_SquareCells.topLeft.y * BLOCK_SIZE , BLOCK_SIZE, BLOCK_SIZE, 0, GREEN, kFillModeSolid);
		//Novice::DrawBox(p_SquareCells.topRight.x * BLOCK_SIZE, p_SquareCells.topRight.y * BLOCK_SIZE , BLOCK_SIZE, BLOCK_SIZE, 0, GREEN, kFillModeSolid);
		//Novice::DrawBox(p_SquareCells.bottomLeft.x * BLOCK_SIZE, p_SquareCells.bottomLeft.y * BLOCK_SIZE , BLOCK_SIZE, BLOCK_SIZE, 0, GREEN, kFillModeSolid);
		//Novice::DrawBox(p_SquareCells.bottomRight.x * BLOCK_SIZE, p_SquareCells.bottomRight.y * BLOCK_SIZE , BLOCK_SIZE, BLOCK_SIZE, 0, GREEN, kFillModeSolid);
		//Novice::DrawBox(p_SquareCells.middleTop.x * BLOCK_SIZE, p_SquareCells.middleTop.y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, 0, GREEN, kFillModeSolid);
		//Novice::DrawBox(p_SquareCells.middleBot.x * BLOCK_SIZE, p_SquareCells.middleBot.y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, 0, GREEN, kFillModeSolid);
		//Novice::DrawBox(p_SquareCells.middleLeft.x * BLOCK_SIZE, p_SquareCells.middleLeft.y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, 0, GREEN, kFillModeSolid);
		//Novice::DrawBox(p_SquareCells.middleRight.x * BLOCK_SIZE, p_SquareCells.middleRight.y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, 0, GREEN, kFillModeSolid);

		//Print information
		Novice::ScreenPrintf(800, 10, "FPS: %d",nLastFPS);

		Novice::ScreenPrintf(1000, 10, "Ping : %lf ms", PingCount);
		/*Novice::ScreenPrintf(600, 30, "fElapsedTime : %f ms", fElapsedTime);
		Novice::ScreenPrintf(600, 80, "IsGrounded : %d ", mapObjects[nPlayerID].p_OnGround);
		Novice::ScreenPrintf(600, 110, "CanJump : %d ", mapObjects[nPlayerID].canJump);

		Novice::ScreenPrintf(600, 150, "TopLeft : [%d][%d] ", int(p_SquareCells.topLeft.x), int(p_SquareCells.topLeft.y));
		Novice::ScreenPrintf(600, 180, "TopRight : [%d][%d] ", int(p_SquareCells.topRight.x), int(p_SquareCells.topRight.y));
		Novice::ScreenPrintf(600, 210, "BotLeft : [%d][%d] ", int(p_SquareCells.bottomLeft.x), int(p_SquareCells.bottomLeft.y));
		Novice::ScreenPrintf(600, 240, "BotRight : [%d][%d] ", int(p_SquareCells.bottomRight.x), int(p_SquareCells.bottomRight.y));

		Novice::ScreenPrintf(600, 270, "shakex : %f", p_Shake.shakePos.x);
		Novice::ScreenPrintf(600, 300, "shakey : %f", p_Shake.shakePos.y);
		Novice::ScreenPrintf(600, 330, "PlayerHP : %f", mapObjects[nPlayerID].p_Hp.currentHp);
		Novice::ScreenPrintf(600, 360, "PlayerReceiveDamage : %f", mapObjects[nPlayerID].p_Hp.receivedDamage);*/

		for (auto& object : mapObjects)
		{
			if (object.first != 0)
			{
				//Draw bullet
				for (int i = 0; i < 5; i++)
				{
					if (object.second.bullet[i].isShooting[0] || object.second.bullet[i].isShooting[1])
					{
						Novice::DrawEllipse(object.second.bullet[i].w_Pos.x, object.second.bullet[i].w_Pos.y, 5, 5, 0, WHITE, kFillModeSolid);
					}
				}

				Novice::DrawQuad(object.second.p_s_Pos.x, object.second.p_s_Pos.y, object.second.p_s_Pos.x + P_BLOCK_SIZE, object.second.p_s_Pos.y, object.second.p_s_Pos.x, object.second.p_s_Pos.y + P_BLOCK_SIZE, object.second.p_s_Pos.x + P_BLOCK_SIZE, object.second.p_s_Pos.y + P_BLOCK_SIZE, object.second.animObj.currentFrame * P_BLOCK_SIZE, 0, P_BLOCK_SIZE, P_BLOCK_SIZE, object.second.graph, object.second.color);
				
			/*	Novice::ScreenPrintf(10, 10, "Vel x : %f  Vel y : %f", object.second.p_Vel.x, object.second.p_Vel.y);
				Novice::ScreenPrintf(10, 30, "Pos x : %f  Pos y : %f", object.second.p_Pos.x, object.second.p_Pos.y);*/
				Novice::ScreenPrintf(object.second.p_Pos.x, object.second.p_Pos.y + 70, "%s", std::to_string(object.first));
				//Novice::ScreenPrintf(10, 60, "%s", std::to_string(object.second.bullet[0].w_Speed));
				
				if (object.second.isSquat)
				{
					//Novice::DrawBox(object.second.p_Pos.x, object.second.p_Pos.y + 32, P_BLOCK_SIZEX, P_BLOCK_SIZE -32, 0, object.second.color, kFillModeWireFrame);
				}
				else
				{
					//Novice::DrawBox(object.second.p_Pos.x, object.second.p_Pos.y, P_BLOCK_SIZEX, P_BLOCK_SIZE, 0, object.second.color, kFillModeWireFrame);
				}
				//Draw HP Bar
				DrawHpBar(object.second.p_Hp.pos, 200, 30, object.second.p_Hp);
			}

			
			
			
		}
		
	}
	
}

void Player::Skill(char* keys, char* preKeys)
{
	
}
