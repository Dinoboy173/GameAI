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

	auto nodeA = m_graph->AddNode({ 100, 100 });
	auto nodeB = m_graph->AddNode({ 200, 100 });
	auto nodeC = m_graph->AddNode({ 200, 200 });

	m_graph->AddEdge(nodeA, nodeB, 100);
	m_graph->AddEdge(nodeB, nodeA, 100);
	m_graph->AddEdge(nodeB, nodeC, 100);
	m_graph->AddEdge(nodeC, nodeB, 100);

	//m_graphEditor = new Demo2Graph2DEditor();
	//m_graphEditor->SetGraph(m_graph);
}

void Demo2::Unload()
{
	std::cout << "Unloading Demo2\n";

	//delete m_graphEditor;
	//m_graphEditor = nullptr;

	delete m_graph;
	m_graph = nullptr;
}

void Demo2::Update(float dt)
{
	//m_graphEditor->Update(dt);

	if (IsKeyPressed(KeyboardKey(KEY_BACKSPACE)))
	{
		m_app->GetGameStateManager()->PopState();
		m_app->GetGameStateManager()->PushState("Menu");
	}
}

void Demo2::Draw()
{
	DrawText("Demo2", 10, 10, 20, LIGHTGRAY);

	//m_graphEditor->Draw();
}