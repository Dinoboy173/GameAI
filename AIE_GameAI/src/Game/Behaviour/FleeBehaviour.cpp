#include "./Game/Behaviour/FleeBehaviour.h"
#include "./Game/GameObject.h"
#include "./Game/Graph2D.h"
#include "./Game/BuildWord.h"
#include <random>

FleeBehaviour::FleeBehaviour(BuildWorld* world) : Behaviour()
{
	m_world = world;
}

FleeBehaviour::~FleeBehaviour()
{

}

void FleeBehaviour::Update(GameObject* obj, float deltaTime)
{
	float distFromTarget = Vector2Length(Vector2Subtract(m_target, obj->GetPosition()));

	if (distFromTarget > 100)
		if (m_onExitedFn)
		{
			m_onExitedFn();
			return;
		}

	obj->SetPreviousBehaviour(this);

	Vector2 desiredDirToTarget = Vector2Normalize(Vector2Subtract(obj->GetPosition(), m_target));
	Vector2 desiredVelocity = Vector2Scale(desiredDirToTarget, obj->GetMaxSpeed());
	Vector2 targetForcePos = Vector2Add(desiredVelocity, obj->GetPosition());

	auto closestWPNode = m_world->m_graph->GetClosestNode(targetForcePos, 128);

	auto func = [=](auto node) {return node == closestWPNode; };

	if (closestWPNode != nullptr)
	{
		auto nodes = m_world->m_graph->FindPath(IGraph::SearchType::DIJKSTRA, obj->GetStartNode(), func);

		obj->SetNodes(nodes);
		obj->DoFollowPath(true);
	}
	else
		return;
}

void FleeBehaviour::Draw(GameObject* obj)
{
	DrawCircleV(m_target, m_targetRadius, { 255, 0, 0, 128 });
	DrawCircleV(m_fleePoint, 5, { 0, 0, 0, 128 });
}

const Vector2& FleeBehaviour::GetTarget() const
{
	return m_target;
}

void FleeBehaviour::SetTarget(const Vector2& target)
{
	m_target = target;
}

const float& FleeBehaviour::GetTargetRadius() const
{
	return m_targetRadius;
}

void FleeBehaviour::SetTargetRadius(const float& radius)
{
	m_targetRadius = radius;
}

void FleeBehaviour::OnExit(std::function<void()> callback)
{
	m_onExitedFn = callback;
}