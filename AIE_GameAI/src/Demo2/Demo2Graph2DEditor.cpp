#include "./Demo2/Demo2Graph2DEditor.h"
#include "./Game/Graph2D.h"
#include <iostream>

Demo2Graph2DEditor::Demo2Graph2DEditor()
{

}

Demo2Graph2DEditor::~Demo2Graph2DEditor()
{

}

void Demo2Graph2DEditor::Update(float dt)
{
	if (IsMouseButtonPressed(0))
	{
		auto mousePos = GetMousePosition();

		auto newNode = m_graph->AddNode(mousePos);

		std::vector<Graph2D::Node*> nearbyNodes;
		m_graph->GetNearbyNodes(mousePos, m_radius, nearbyNodes);

		for (auto nearbyNode : nearbyNodes)
		{
			float dist = Vector2Distance(newNode->data, nearbyNode->data);

			m_graph->AddEdge(newNode, nearbyNode, dist);
			m_graph->AddEdge(nearbyNode, newNode, dist);
		}
	}
}

void Demo2Graph2DEditor::Draw()
{
	// Draw all connections
	for (auto node : m_graph->GetNodes())
	{
		for (auto connection : node->connections)
		{
			DrawLine(node->data.x, node->data.y, connection.to->data.x, connection.to->data.y, GRAY);
		}
	}

	// Draw all nodes
	for (auto node : m_graph->GetNodes())
	{
		DrawCircle(node->data.x, node->data.y, 8, LIGHTGRAY);
		DrawCircleLines(node->data.x, node->data.y, 8, GRAY);
	}

	auto mousePos = GetMousePosition();
	DrawCircle(mousePos.x, mousePos.y, 6, LIGHTGRAY);

	std::vector<Graph2D::Node*> nearbyNodes;
	m_graph->GetNearbyNodes(mousePos, m_radius, nearbyNodes);

	for (auto nearbyNode : nearbyNodes)
	{
		DrawLine(mousePos.x, mousePos.y, nearbyNode->data.x, nearbyNode->data.y, LIGHTGRAY);
	}
}

Graph2D* Demo2Graph2DEditor::GetGraph()
{
	return m_graph;
}

void Demo2Graph2DEditor::SetGraph(Graph2D* graph)
{
	m_graph = graph;
}