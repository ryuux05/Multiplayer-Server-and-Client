#pragma once
#include"Player.h"
#include"Novice.h"

class GameTitle : public ClientInterface
{
private:
	int graph;
public:
	GameTitle();
	void Init();
	void Draw();
};

