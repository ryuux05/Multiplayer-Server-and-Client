#pragma once
#include<iostream>
#include<stdio.h>
#include"..\[Server]\Common.h"
#include"Novice.h"
#include"Particle.h"

#define MAP_WIDTH 50
#define MAP_HEIGHT 25

class Map
{
private:
	FILE* fp;
	errno_t err;
	std::string fname = "mapSample2.csv";
	int mapGraph;
	int particleGraph_;
	Vector2 bgPos;
	Particle* spiral = new Particle(maxParticle, 25, 100, 240, 25, 1, 1, 0xDC143C00);
public:
	int Tiles[25][50];

public:
	Map();
	void InitMap();
	void DrawMap();
};

