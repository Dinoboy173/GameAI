#include "./Game/BuildWord.h"
#include "./Game/AssetManager.h"
#include "./Game/GameObject.h"
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

			Rectangle bushDest = { x * (float)tileSize, y * (float)tileSize, 32.0f, 32.0f };

			DrawTexture(ASSETS->imgGrass, x * tileSize, y * tileSize, WHITE); // Draws Grass

			if (color == COLOR::C_BLUE) // Draws Water
				DrawTexture(ASSETS->imgWater, x * tileSize, y * tileSize, WHITE);

			else if (color == COLOR::C_GREEN) // Draws Trees
				DrawTexture(ASSETS->imgTree, x * tileSize, y * tileSize, WHITE);

			else if (color == COLOR::C_MAGENTA) // Draws Holes
				DrawTexture(ASSETS->imgHole, x * tileSize, y * tileSize, WHITE);

			if (color == COLOR::C_CYAN) // Draws Bushes
				DrawTexturePro(ASSETS->imgBush, ASSETS->bush, bushDest, { 0, 0 }, 0.0f, WHITE); // make own object
		}
	}
}

unsigned int BuildWorld::GetImagePixel(Image img, int xPos, int yPos)
{
	unsigned int* data = (unsigned int *)img.data;
	unsigned int color = data[yPos * img.width + xPos];

	return color;
}