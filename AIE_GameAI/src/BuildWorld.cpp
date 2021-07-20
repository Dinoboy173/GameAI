#include "BuildWord.h"
#include "AssetManager.h"
#include "raylib.h"
#include <iostream>
#include <map>
#include <list>

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
	//bushes.push_back({ 32.0f, 32.0f });
}

void BuildWorld::Draw()
{
	int numRows = ASSETS->imgGameMapInfo.height;
	int numCols = ASSETS->imgGameMapInfo.width;

	for (int y = 0; y < numRows; y++)
	{
		for (int x = 0; x < numCols; x++)
		{
			auto color = GetImagePixel(ASSETS->imgGameMapInfoRaw, x, y);

			DrawTexture(ASSETS->imgGrass, x * 32, y * 32, WHITE);

			if (color == 0xFFFF0000)
				DrawTexture(ASSETS->imgWater, x * 32, y * 32, WHITE);

			else if (color == 0xFF00FF00)
				DrawTexture(ASSETS->imgTree, x * 32, y * 32, WHITE);

			else if (color == 0xFFFF00FF)
				DrawTexture(ASSETS->imgHole, x * 32, y * 32, WHITE);
		}
	}

	std::vector<std::pair<float, float>> m_bushes = { std::make_pair(32.0f, 32.0f) };

	for (int i = 0; i < m_bushes.size(); i++)
	{
		DrawTexturePro(
			ASSETS->imgBush,
			ASSETS->bush,
			{ m_bushes[i].first, m_bushes[i].second, ASSETS->imgBush.width / 2.0f,  ASSETS->imgBush.height * 1.0f },
			{ 0.0f, 0.0f },
			0.0f, WHITE);
	}
}

unsigned int BuildWorld::GetImagePixel(Image img, int xPos, int yPos)
{
	unsigned int* data = (unsigned int *)img.data;
	unsigned int color = data[yPos * img.width + xPos];

	return color;
}