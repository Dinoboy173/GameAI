#include "./Game/Behaviour/FleeBehaviour.h"
#include "./Game/GameObject.h"
#include "./Game/Graph2D.h"

FleeBehaviour::FleeBehaviour(BuildWorld* world) : Behaviour()
{
	m_world = world;
}

FleeBehaviour::~FleeBehaviour()
{

}

void FleeBehaviour::Update(GameObject* obj, float deltaTime)
{
	float distToTarget = Vector2Distance(obj->GetPosition(), m_target);
	if (distToTarget > m_targetRadius)
		if (m_onExitedFn)
			m_onExitedFn();
	
	Vector2 heading = Vector2Add(obj->GetPosition(), obj->GetVelocity());

	Vector2 desiredDirToTarget = Vector2Normalize(Vector2Subtract(obj->GetPosition(), m_target));
	Vector2 desiredVelocity = Vector2Scale(desiredDirToTarget, obj->GetMaxSpeed());
	Vector2 targetForcePos = Vector2Add(desiredVelocity, obj->GetPosition());
	
	if (targetForcePos.x <= 0 ||
		targetForcePos.x >= m_windowSize)
	{
		targetForcePos.x -= targetForcePos.x;
		targetForcePos.y -= 20;
	}
	
	if (targetForcePos.y <= 0 ||
		targetForcePos.y >= m_windowSize)
	{
		targetForcePos.x -= 20;
		targetForcePos.y -= targetForcePos.y;
	}
	
	if (targetForcePos.x <= 1 && targetForcePos.y <= 1)
	{
		targetForcePos = Vector2{ 20, 20 };
	}

	auto closestWPNode = m_world->m_graph->GetClosestNode(targetForcePos, 20);

	if (closestWPNode != nullptr)
		targetForcePos = closestWPNode->data;

	Vector2 forceDir = Vector2Scale(Vector2Normalize(Vector2Subtract(targetForcePos, heading)), obj->GetMaxForce());

	obj->ApplyForce(forceDir);
}

void FleeBehaviour::Draw(GameObject* obj)
{
	DrawCircleV(m_target, m_targetRadius, { 255, 0, 0, 128 });
	DrawCircleV(m_target, 5, { 0, 0, 0, 128 });
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