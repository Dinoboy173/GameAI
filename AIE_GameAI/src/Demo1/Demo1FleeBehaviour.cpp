#include "./Demo1/Demo1FleeBehaviour.h"
#include "./Demo1/Demo1GameObject.h"

Demo1FleeBehaviour::Demo1FleeBehaviour() : Demo1Behaviour()
{

}

Demo1FleeBehaviour::~Demo1FleeBehaviour()
{

}

void Demo1FleeBehaviour::Update(Demo1GameObject* obj, float deltaTime)
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

void Demo1FleeBehaviour::Draw(Demo1GameObject* obj)
{
	DrawCircle(m_target.x, m_target.y, m_targetRadius, LIGHTGRAY);
	DrawCircle(m_target.x, m_target.y, 4, GRAY);
}

const Vector2& Demo1FleeBehaviour::GetTarget() const
{
	return m_target;
}

void Demo1FleeBehaviour::SetTarget(const Vector2& target)
{
	m_target = target;
}

const float& Demo1FleeBehaviour::GetTargetRadius() const
{
	return m_targetRadius;
}

void Demo1FleeBehaviour::SetTargetRadius(const float& radius)
{
	m_targetRadius = radius;
}

void Demo1FleeBehaviour::OnExit(std::function<void()> callback)
{
	m_onExitedFn = callback;
}