#include "Map.h"

Map::Map()
{
	InitMap();
}

void Map::InitMap()
{
	err = fopen_s(&fp, "./Resources/mapSample2.csv", "r");
	mapGraph = Novice::LoadTexture("./Resources/Block1.png");
	particleGraph_ = Novice::LoadTexture("./Resources/particle.jpg");
	if (err != 0)
	{
		//return err;
	}
	else {
		for (int i = 0; i < 25; i++)
		{
			for (int j = 0; j < 40; j++)
			{
				if (fscanf_s(fp, "%d,", &Tiles[i][j]) != EOF);
			}
		}
	}
}

void Map::DrawMap()
{
	Novice::DrawBox(0, 0, 1280, 800, 0, BLACK, kFillModeSolid);
	spiral->Update(PARTICLESTYLE::spiral);
	spiral->Draw(particleGraph_);
	Novice::SetBlendMode(kBlendModeNormal);
	for (int y = 0; y < 25; y++)
	{
		for (int x = 0; x < 50; x++)
		{
			//Novice::DrawLine(x * BLOCK_SIZE + bgPos.x, 0, x * BLOCK_SIZE + bgPos.x, 800, WHITE);
			if (Tiles[y][x] == MapInfo::BLOCK || Tiles[y][x] == 2)
			{
				
				Novice::DrawSprite(x * BLOCK_SIZE + bgPos.x, y * BLOCK_SIZE, mapGraph, 1, 1, 0, WHITE);
			}
			//if (x == int(squareCells.topLeft.x) && y == int(squareCells.topLeft.y) || x == int(squareCells.bottomLeft.x) && y == int(squareCells.bottomLeft.y) || x == int(squareCells.topRight.x) && y == int(squareCells.topRight.y) || x == int(squareCells.bottomRight.x) && y == int(squareCells.bottomRight.y))
			//{
			//	//Novice::DrawBox(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, 0, WHITE, kFillModeSolid);
			//}

		}
		//Novice::DrawLine(0, y * BLOCK_SIZE, 1280, y * BLOCK_SIZE, WHITE);
	}
}
