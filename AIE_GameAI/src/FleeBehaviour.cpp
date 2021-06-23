#include "FleeBehaviour.h"
#include "GameObject.h"

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

	// do rest of flee at home based on seek
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