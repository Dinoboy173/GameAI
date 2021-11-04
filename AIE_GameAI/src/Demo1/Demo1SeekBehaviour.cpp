#include "./Demo1/Demo1SeekBehaviour.h"
#include "./Game/GameObject.h"

Demo1SeekBehaviour::Demo1SeekBehaviour() : Behaviour()
{
	m_target = {0, 0};
}

Demo1SeekBehaviour::~Demo1SeekBehaviour()
{
	
}

void Demo1SeekBehaviour::Update(GameObject* obj, float deltaTime)
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

void Demo1SeekBehaviour::Draw(GameObject* obj)
{
	DrawCircle(m_target.x, m_target.y, m_targetRadius, LIGHTGRAY);
	DrawCircle(m_target.x, m_target.y, 4, GRAY);
}

const Vector2& Demo1SeekBehaviour::GetTarget() const
{
	return m_target;
}

void Demo1SeekBehaviour::SetTarget(const Vector2& target)
{
	m_target = target;
}

const float& Demo1SeekBehaviour::GetTargetRadius() const
{
	return m_targetRadius;
}

void Demo1SeekBehaviour::SetTargetRadius(const float& radius)
{
	m_targetRadius = radius;
}

void Demo1SeekBehaviour::OnArrive(std::function<void()> callback)
{
	m_onArrivedFn = callback;
}