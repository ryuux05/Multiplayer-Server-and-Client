#pragma once
#include <cstdint>
#include"Networking.h"
#include"Struct.h"
#include<math.h>
#define BLOCK_SIZE 32

enum MapInfo
{
	NONE,
	BLOCK,
};

enum GameStatus
{
	Game_Title,
	Game_Search,
	Game_Start,
	Game_MakeRoom,
	Game_Over,
};

enum PlayerNum
{
	PLAYER1,
	PLAYER2,
};

enum class GameMsg : uint32_t
{
	Server_GetStatus,
	Server_GetPing,

	Client_Accepted,
	Client_AssignID,
	Client_AssignAvatar,
	Client_RegisterWithServer,
	Client_UnregisterWithServer,

	Game_AddPlayer,
	Game_RemovePlayer,
	Game_UpdatePlayer,
};

struct PlayerInfo
{
	uint32_t nUniqueID = 0;
	uint32_t nAvatarID = 0;
	Hp p_Hp;
	Vector2 p_Pos;
	Vector2 p_Old_Pos;
	Vector2 p_respawnPos;
	Vector2 p_Vel;
	Vector2 p_Acc;
	Vector2 p_s_Pos;
	Vector2 p_Scale;
	Bullet bullet[5];
	Melee melee;
	int graph;

	AnimationObject animObj;

	int facing = RIGHT;
	int color = 0xFFFFFFFF;
	bool isHitted;
	bool canHit;
	bool p_OnGround;
	bool canJump;
	bool isSquat;
	bool win;
	bool lose;
};