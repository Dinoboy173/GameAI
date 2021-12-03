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
	if (!m_nodes.empty())
	{
		auto endNode = *--m_nodes.end();
		DrawCircleV(endNode->data, m_targetRadius, { 255, 0, 255, 128 });
	}

	DrawCircleV(m_target, m_targetRadius, { 255, 0, 0, 128 });

	for (auto node : m_nodes)
		DrawCircleV(node->data, 5, { 255, 255, 0, 255 });
}

void FollowPathBehaviour::NextNode(GameObject* obj)
{
	if (!m_hasStart)
	{
		m_currentNode = m_nodes.begin();
		m_hasStart = true;
	}
	
	if (m_currentNode == m_nodes.end())
		m_currentNode = m_nodes.begin();
	else
		m_currentNode++;

	Graph<Vector2, float>::Node* node = *m_currentNode;

	obj->SetStartNode(node);
	m_target = node->data;
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

void FollowPathBehaviour::SetPath(std::list<Graph<Vector2, float>::Node*> nodes)
{
	m_nodes = nodes;
}