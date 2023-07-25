#include "GameTitle.h"

GameTitle::GameTitle()
{
	graph = Novice::LoadTexture("./Resources/title.png");
}

void GameTitle::Init()
{
}

void GameTitle::Draw()
{		
	Novice::DrawSprite(0, 0, graph, 1, 1, 0, WHITE);
}
