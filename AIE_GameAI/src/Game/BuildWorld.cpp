#include "./Game/BuildWord.h"
#include "./Game/AssetManager.h"
#include "raylib.h"
#include <iostream>
#include "./Game/Graph.h"

BuildWorld::BuildWorld()
{
	
}

BuildWorld::~BuildWorld()
{

}

void BuildWorld::Load()
{
	std::cout << "Loading World\n";

	LoadGraph();
}

void BuildWorld::Unload()
{
	std::cout << "Unloading World\n";

	delete m_graph;
	m_graph = nullptr;
}

void BuildWorld::LoadGraph()
{
	m_graph = new Graph2D;

	int numRows = ASSETS->imgGameMapInfo.height;
	int numCols = ASSETS->imgGameMapInfo.width;
	float xOffset = 16;
	float yOffset = 16;
	float spacing = 32;

	for (int y = 0; y < numRows; y++)
	{
		for (int x = 0; x < numCols; x++)
		{
			float xPos = (x * spacing) + xOffset;
			float yPos = (y * spacing) + xOffset;

			auto color = GetImagePixel(ASSETS->imgGameMapInfoRaw, x, y);

			if (color != COLOR::C_GREEN)
				if (color != COLOR::C_BLUE)
					m_graph->AddNode({ xPos, yPos });
		}
	}

	for (auto node : m_graph->GetNodes())
	{
		float radius = 50.0f;

		std::vector<Graph2D::Node*> nearbyNodes;
		m_graph->GetNearbyNodes(node->data, radius, nearbyNodes);

		for (auto connectedNode : nearbyNodes)
		{
			if (connectedNode == node)
				continue;

			float dist = Vector2Distance(node->data, connectedNode->data);
			m_graph->AddEdge(node, connectedNode, dist);
			m_graph->AddEdge(connectedNode, node, dist);
		}
	}
}

void BuildWorld::Update(float dt)
{
	
}

void BuildWorld::Draw()
{
	DrawWorld();
	DrawGraph();
}

void BuildWorld::DrawWorld()
{
	int numRows = ASSETS->imgGameMapInfo.height;
	int numCols = ASSETS->imgGameMapInfo.width;

	int tileSize = 32;

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

	if (IsKeyDown(KeyboardKey(KEY_TAB)))
	{
		DrawTexturePro(ASSETS->imgGameMapInfo, { 0.0f, 0.0f, 32.0f, 32.0f }, {0.0f, 0.0f, 1024.0f, 1024.0f}, { 0, 0 }, 0.0f, WHITE);
	}
}

void BuildWorld::DrawGraph()
{
	if (IsKeyDown(KeyboardKey(KEY_F2)))
	{
		for (auto& node : m_graph->GetNodes())
		{
			for (auto& edge : node->connections)
			{
				DrawLine(node->data.x, node->data.y, edge.to->data.x, edge.to->data.y, YELLOW);
			}
		}
	}

	if (IsKeyDown(KeyboardKey(KEY_F1)))
	{
		for (auto& node : m_graph->GetNodes())
		{
			DrawCircle(node->data.x, node->data.y, 4, PINK);
		}
	}
}

unsigned int BuildWorld::GetImagePixel(Image img, int xPos, int yPos)
{
	unsigned int* data = (unsigned int *)img.data;
	unsigned int color = data[yPos * img.width + xPos];

	return color;
}