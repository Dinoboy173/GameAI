#include "./Demo2/Demo2.h"
#include "./Menu/Application.h"
#include "./Menu/GameStateManager.h"
#include "./Demo2/Demo2Player.h"
#include "./Demo2/Demo2KeyboardBehaviour.h"
#include "./Demo2/Demo2GameObject.h"
#include "./Game/Graph2D.h"
#include "./Demo2/Demo2Graph2DEditor.h"
#include "raylib.h"

#include <iostream>

Demo2::Demo2(Application* app) : m_app(app)
{
	
}

Demo2::~Demo2()
{

}

void Demo2::Load()
{
	std::cout << "Loading Demo2\n";

	m_graph = new Graph2D();

	int numRows = 8;
	int numCols = 8;
	float xOffset = 100;
	float yOffset = 100;
	float spacing = 50;

	for (int y = 0; y < numRows; y++)
	{
		for (int x = 0; x < numCols; x++)
		{
			m_graph->AddNode({
				x * spacing + xOffset,
				y * spacing + yOffset
				});
		}
	}

	for (auto node : m_graph->GetNodes())
	{
		std::vector<Graph2D::Node*> nearbyNodes;

		m_graph->GetNearbyNodes(node->data, 60, nearbyNodes);

		for (auto connectedNode : nearbyNodes)
		{
			if (connectedNode == node)
				continue;

			float dist = Vector2Distance(node->data, connectedNode->data);
			m_graph->AddEdge(node, connectedNode, dist);
			m_graph->AddEdge(connectedNode, node, dist);
		}
	}

	m_graphEditor = new Demo2Graph2DEditor();
	m_graphEditor->SetGraph(m_graph);
}

void Demo2::Unload()
{
	std::cout << "Unloading Demo2\n";

	delete m_graphEditor;
	m_graphEditor = nullptr;

	delete m_graph;
	m_graph = nullptr;
}

void Demo2::Update(float dt)
{
	m_graphEditor->Update(dt);

	if (IsKeyPressed(KeyboardKey(KEY_BACKSPACE)))
	{
		m_app->GetGameStateManager()->PopState();
		m_app->GetGameStateManager()->PushState("Menu");
	}
}

void Demo2::Draw()
{
	DrawText("Demo2", 10, 10, 20, LIGHTGRAY);

	m_graphEditor->Draw();
}