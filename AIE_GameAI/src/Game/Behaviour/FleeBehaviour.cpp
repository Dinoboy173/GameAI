#include "./Game/Behaviour/FleeBehaviour.h"
#include "./Game/GameObject.h"

FleeBehaviour::FleeBehaviour() : Behaviour()
{

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
	Vector2 forceDir = Vector2Scale(Vector2Normalize(Vector2Subtract(targetForcePos, heading)), obj->GetMaxForce());

	obj->ApplyForce(forceDir);
}

void FleeBehaviour::Draw(GameObject* obj)
{
	DrawCircle(m_target.x, m_target.y, m_targetRadius, LIGHTGRAY);
	DrawCircle(m_target.x, m_target.y, 4, GRAY);
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