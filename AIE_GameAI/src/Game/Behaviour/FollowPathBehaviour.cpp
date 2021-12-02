#include "./Game/Behaviour/FollowPathBehaviour.h"
#include "./Game/GameObject.h"
#include "./Game/BuildWord.h"
#include "./Game/Graph2D.h"
#include <functional>

FollowPathBehaviour::FollowPathBehaviour() : Behaviour()
{
	m_target = Vector2{ 0, 0 };
}

FollowPathBehaviour::~FollowPathBehaviour()
{
	delete m_graph;
	m_graph = nullptr;
}

void FollowPathBehaviour::Update(GameObject* obj, float deltaTime)
{
	float distToTarget = Vector2Distance(obj->GetPosition(), m_target);

	if (distToTarget < m_targetRadius)
		if (m_onArrivedFn)
			m_onArrivedFn();

	Vector2 heading = Vector2Add(obj->GetPosition(), obj->GetVelocity());

	Vector2 desiredDirToTarget = Vector2Normalize(Vector2Subtract(m_target, obj->GetPosition()));
	Vector2 desiredVelocity = Vector2Scale(desiredDirToTarget, obj->GetMaxSpeed());
	Vector2 targetForcePos = Vector2Add(desiredVelocity, obj->GetPosition());
	Vector2 forceDir = Vector2Scale(Vector2Normalize(Vector2Subtract(targetForcePos, heading)), obj->GetMaxForce());

	obj->ApplyForce(forceDir);
}

void FollowPathBehaviour::Draw(GameObject* obj)
{
	// // Draw all connections
	// for (auto node : m_graph->GetNodes())
	// {
	// 	for (auto connection : node->connections)
	// 	{
	// 		DrawLine(node->data.x, node->data.y, connection.to->data.x, connection.to->data.y, GRAY);
	// 	}
	// }
	// 
	// // Draw all nodes
	// for (auto node : m_graph->GetNodes())
	// {
	// 	DrawCircle(node->data.x, node->data.y, 8, LIGHTGRAY);
	// 	DrawCircleLines(node->data.x, node->data.y, 8, GRAY);
	// }
}

void FollowPathBehaviour::NextNode()
{
	int size = m_nodes.size();
	
	if (m_currentNode < size - 1)
		m_currentNode++;
	else
		m_currentNode = 0;
	
	m_target = m_nodes[m_currentNode]->data;
}

const Vector2& FollowPathBehaviour::GetTarget() const
{
	return m_target;
}

void FollowPathBehaviour::SetTarget(const Vector2& target)
{
	m_target = target;
}

const float& FollowPathBehaviour::GetTargetRadius() const
{
	return m_targetRadius;
}

void FollowPathBehaviour::SetTargetRadius(const float& radius)
{
	m_targetRadius = radius;
}

void FollowPathBehaviour::OnArrive(std::function<void()> callback)
{
	m_onArrivedFn = callback;
}

void FollowPathBehaviour::SetGraph(Graph2D* graph)
{
	m_graph = graph;
}

Graph2D* FollowPathBehaviour::GetGraph()
{
	return m_graph;
}

void FollowPathBehaviour::SetPath(std::vector<Graph<Vector2, float>::Node*> nodes)
{
	m_nodes = nodes;
}