#include "./Game/Behaviour/SeekBehaviour.h"
#include "./Game/GameObject.h"
#include "./Game/BuildWord.h"
#include "./Game/Graph2D.h"

SeekBehaviour::SeekBehaviour(BuildWorld* world) : Behaviour()
{
	m_target = {0, 0};
	m_world = world;
}

SeekBehaviour::~SeekBehaviour()
{
	
}

void SeekBehaviour::Update(GameObject* obj, float deltaTime)
{
	float distToTarget = Vector2Distance(obj->GetPosition(), m_target);
	if (distToTarget < m_targetRadius)
		if (m_onArrivedFn)
			m_onArrivedFn();

	Vector2 heading = Vector2Add(obj->GetPosition(), obj->GetVelocity());

	Vector2 desiredDirToTarget = Vector2Normalize(Vector2Subtract(m_target, obj->GetPosition()));
	Vector2 desiredVelocity = Vector2Scale(desiredDirToTarget, obj->GetMaxSpeed());
	Vector2 targetForcePos = Vector2Add(desiredVelocity, obj->GetPosition());

	if (targetForcePos.x <= 0 ||
		targetForcePos.x >= m_windowSize ||
		targetForcePos.y <= 0 ||
		targetForcePos.y >= m_windowSize)
	{
		targetForcePos.x -= targetForcePos.x;
		targetForcePos.y -= targetForcePos.y;
	}

	auto closestWPNode = m_world->m_graph->GetClosestNode(m_target, 128);

	auto func = [=](auto node) {return node == closestWPNode; };

	if (closestWPNode != nullptr)
	{
		auto nodes = m_world->m_graph->FindPath(IGraph::SearchType::DIJKSTRA, obj->GetStartNode(), func);

		obj->SetNodes(nodes);
		obj->DoFollowPath(true);
	}
	else
		return;

	Vector2 forceDir = Vector2Scale(Vector2Normalize(Vector2Subtract(targetForcePos, heading)), obj->GetMaxForce());

	obj->ApplyForce(forceDir);
}

void SeekBehaviour::Draw(GameObject* obj)
{
	// DrawCircleV(m_target, m_targetRadius, { 255, 0, 0, 128 });
	// DrawCircleV(m_target, 5, { 0, 0, 0, 128 });

	// DrawCircle(m_target.x, m_target.y, m_targetRadius, LIGHTGRAY);
	// DrawCircle(m_target.x, m_target.y, 4, GRAY);
}

const Vector2& SeekBehaviour::GetTarget() const
{
	return m_target;
}

void SeekBehaviour::SetTarget(const Vector2& target)
{
	m_target = target;
}

const float& SeekBehaviour::GetTargetRadius() const
{
	return m_targetRadius;
}

void SeekBehaviour::SetTargetRadius(const float& radius)
{
	m_targetRadius = radius;
}

void SeekBehaviour::OnArrive(std::function<void()> callback)
{
	m_onArrivedFn = callback;
}