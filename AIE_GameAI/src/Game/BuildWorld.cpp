#include "./Game/BuildWord.h"
#include "./Game/AssetManager.h"
#include "./Game/Rabbit.h"
#include "./Game/Fox.h"
#include <iostream>
#include "./Game/Graph2D.h"

// clean up headers and #includes

BuildWorld::BuildWorld()
{

}

BuildWorld::~BuildWorld()
{

}

void BuildWorld::Load()
{
	m_numRows = ASSETS->imgGameMapInfo.height;
	m_numCols = ASSETS->imgGameMapInfo.width;

	std::cout << "Loading World\n";

	LoadGraph();

	for (int y = 0; y < m_numRows; y++)
	{
		for (int x = 0; x < m_numCols; x++)
		{
			auto color = GetImagePixel(ASSETS->imgGameMapInfoRaw, x, y);

			if (color == C_YELLOW)
			{
				Rabbit* rabbit = new Rabbit(this);
				rabbit->SetPosition({ x * (float)m_tileSize + 16, y * (float)m_tileSize + 16});
				m_rabbitList.push_back(rabbit);

				auto startNode = m_graph->GetClosestNode(rabbit->GetPosition(), 10);
				rabbit->SetStartNode(startNode);
			}
			else if (color == C_RED)
			{
				Fox* fox = new Fox(this);
				fox->SetPosition({ x * (float)m_tileSize + 16, y * (float)m_tileSize + 16 });
				m_foxList.push_back(fox);

				auto startNode = m_graph->GetClosestNode(fox->GetPosition(), 10);
				fox->SetStartNode(startNode);
			}
		}
	}
}

void BuildWorld::Unload()
{
	std::cout << "Unloading World\n";

	delete m_graph;
	m_graph = nullptr;
}

void BuildWorld::LoadGraph()
{
	m_graph = new Graph2D();

	m_numRows = ASSETS->imgGameMapInfo.height;
	m_numCols = ASSETS->imgGameMapInfo.width;
	float xOffset = float(m_tileSize / 2);
	float yOffset = float(m_tileSize / 2);

	for (int y = 0; y < m_numRows; y++)
	{
		for (int x = 0; x < m_numCols; x++)
		{
			float xPos = (x * m_tileSize) + xOffset;
			float yPos = (y * m_tileSize) + xOffset;

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
	for (auto i : m_rabbitList)
	{
		i->Update(dt);
	}

	for (auto i : m_foxList)
	{
		i->Update(dt);
	}
}

void BuildWorld::Draw()
{
	DrawWorld();

	for (auto i : m_rabbitList)
	{
		if (!editingList)
			i->Draw();
	}
	
	for (auto i : m_foxList)
	{
		i->Draw();
	}

	DrawGraph();
}

void BuildWorld::DrawWorld()
{
	for (int y = 0; y < m_numRows; y++)
	{
		for (int x = 0; x < m_numCols; x++)
		{
			auto color = GetImagePixel(ASSETS->imgGameMapInfoRaw, x, y);

			Rectangle bushDest = { x * m_tileSize, y * m_tileSize, m_tileSize, m_tileSize };

			DrawTexture(ASSETS->imgGrass, x * m_tileSize, y * m_tileSize, WHITE); // Draws Grass

			if (color == C_BLUE) // Draws Water
				DrawTexture(ASSETS->imgWater, x * m_tileSize, y * m_tileSize, WHITE);

			else if (color == C_GREEN) // Draws Trees
				DrawTexture(ASSETS->imgTree, x * m_tileSize, y * m_tileSize, WHITE);

			else if (color == C_MAGENTA) // Draws Holes
				DrawTexture(ASSETS->imgHole, x * m_tileSize, y * m_tileSize, WHITE);

			else if (color == C_CYAN) // Draws Bushes
				DrawTexturePro(ASSETS->imgBush, ASSETS->bush, bushDest, { 0, 0 }, 0.0f, WHITE);
		}
	}
}

void BuildWorld::DrawGraph()
{
	if (IsKeyDown(KeyboardKey(KEY_TAB)))
		DrawTexturePro(ASSETS->imgGameMapInfo, { 0.0f, 0.0f, 32.0f, 32.0f }, { 0.0f, 0.0f, 1024.0f, 1024.0f }, { 0, 0 }, 0.0f, WHITE);

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

Vector2 BuildWorld::IsRabbitNearby(GameObject* obj, float radius)
{
	if (this != NULL)
	{
		for (int i = 0; i < m_rabbitList.size(); i++)
		{
			if (m_rabbitList[i] != obj)
			{
				float distToRabbit = Vector2Distance(obj->GetPosition(), m_rabbitList[i]->GetPosition());

				if (distToRabbit < radius)
					return m_rabbitList[i]->GetPosition();
			}
		}
	}
	
	return { 0, 0 };
}

Vector2 BuildWorld::IsFoxNearby(Rabbit* rabbit, float radius)
{
	if (this != NULL)
	{
		for (int i = 0; i < m_foxList.size(); i++)
		{
			float distToFox = Vector2Distance(rabbit->GetPosition(), m_foxList[i]->GetPosition());

			if (distToFox < radius)
				return m_foxList[i]->GetPosition();
		}
	}

	return { 0, 0 };
}

// void BuildWorld::AddRabbit(Vector2 pos)
// {
// 	Rabbit* rabbit = new Rabbit();
// 	rabbit->SetPosition({ pos.x * (float)m_tileSize + 16, pos.y * (float)m_tileSize + 16 });
// 	m_rabbitList.push_back(rabbit);
// }

void BuildWorld::RemoveRabbitFromList(Rabbit* removeRabbit)
{
	std::vector<Rabbit*> tempList;

	for (auto rabbit : m_rabbitList)
	{
		if (rabbit != removeRabbit)
			tempList.push_back(rabbit);
	}

	m_rabbitList.clear();

	delete removeRabbit;

	for (auto rabbit : tempList)
		m_rabbitList.push_back(rabbit);
}