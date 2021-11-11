#include "./Game/Behaviour/FollowPathBehaviour.h"
#include "./Game/GameObject.h"
#include "./Game/BuildWord.h"

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
	DrawText("Demo1", 10, 10, 20, LIGHTGRAY);

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
}

void FollowPathBehaviour::NextNode()
{
	int size = m_graph->GetNodes().size();

	if (currentNode < size - 1)
		currentNode++;
	else
		currentNode = 0;

	m_target = m_graph->GetNodes().at(currentNode)->data;
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