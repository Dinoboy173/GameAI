#include "./Demo2/Demo2SeekBehaviour.h"
#include "./Demo2/Demo2GameObject.h"

Demo2SeekBehaviour::Demo2SeekBehaviour() : Demo2Behaviour()
{

}

Demo2SeekBehaviour::~Demo2SeekBehaviour()
{
	
}

void Demo2SeekBehaviour::Update(Demo2GameObject* obj, float deltaTime)
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

void Demo2SeekBehaviour::Draw(Demo2GameObject* obj)
{
	DrawCircle(m_target.x, m_target.y, m_targetRadius, LIGHTGRAY);
	DrawCircle(m_target.x, m_target.y, 4, GRAY);
}

const Vector2& Demo2SeekBehaviour::GetTarget() const
{
	return m_target;
}

void Demo2SeekBehaviour::SetTarget(const Vector2& target)
{
	m_target = target;
}

const float& Demo2SeekBehaviour::GetTargetRadius() const
{
	return m_targetRadius;
}

void Demo2SeekBehaviour::SetTargetRadius(const float& radius)
{
	m_targetRadius = radius;
}

void Demo2SeekBehaviour::OnArrive(std::function<void()> callback)
{
	m_onArrivedFn = callback;
}