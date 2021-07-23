#include "BuildWord.h"
#include "AssetManager.h"
#include "Bush.h"
#include "GameObject.h"
#include "raylib.h"
#include <iostream>
#include <Graph.h>

BuildWorld::BuildWorld()
{

}

BuildWorld::~BuildWorld()
{

}

void BuildWorld::Load()
{
	std::cout << "Loading World\n";
}

void BuildWorld::Unload()
{
	std::cout << "Unloading World\n";
}

void BuildWorld::Update(float dt)
{
	
}

void BuildWorld::Draw()
{
	int numRows = ASSETS->imgGameMapInfo.height;
	int numCols = ASSETS->imgGameMapInfo.width;

	int tileSize = 32;

	// Raylib color is backwards (a,b,g,r)

	for (int y = 0; y < numRows; y++)
	{
		for (int x = 0; x < numCols; x++)
		{
			auto color = GetImagePixel(ASSETS->imgGameMapInfoRaw, x, y);

			DrawTexture(ASSETS->imgGrass, x * tileSize, y * tileSize, WHITE);

			if (color == 0xFFFF0000)
				DrawTexture(ASSETS->imgWater, x * tileSize, y * tileSize, WHITE);

			else if (color == 0xFF00FF00)
				DrawTexture(ASSETS->imgTree, x * tileSize, y * tileSize, WHITE);

			else if (color == 0xFFFF00FF)
				DrawTexture(ASSETS->imgHole, x * tileSize, y * tileSize, WHITE);

			if (color == 0xFF00FFFF)
				DrawTexture(ASSETS->imgBush, x * tileSize, y * tileSize, WHITE); // make own object
		}
	}
}

unsigned int BuildWorld::GetImagePixel(Image img, int xPos, int yPos)
{
	unsigned int* data = (unsigned int *)img.data;
	unsigned int color = data[yPos * img.width + xPos];

	return color;
}