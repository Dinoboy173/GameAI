#include "./Game/Graph2D.h"
#include "raymath.h"

Graph2D::Graph2D()
{

}

Graph2D::~Graph2D()
{

}

void Graph2D::GetNearbyNodes(Vector2 position, float radius, std::vector<Graph2D::Node*>& out_nodes)
{
	for (auto node : m_nodes)
	{
		float dist = Vector2Distance(position, node->data);
		if (dist < radius)
		{
			out_nodes.push_back(node);
		}
	}
}

Graph2D::Node* Graph2D::GetClosestNode(Vector2 position, float withinRadius)
{
	std::vector<Graph2D::Node*> nodes;
	GetNearbyNodes(position, withinRadius, nodes);

	if (nodes.empty())
		return nullptr;
	
	Graph2D::Node* closestNode = nullptr;
	float closestNodeDist = NULL;

	for (auto node : nodes)
	{
		auto dist = Vector2Distance(node->data, position);

		if (dist < closestNodeDist || closestNodeDist == NULL)
		{
			closestNodeDist = dist;
			closestNode = node;
		}
	}

	return closestNode;
}
