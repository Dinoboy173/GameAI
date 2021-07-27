#include "./Demo2/Demo2GameObject.h"
#include "./Demo2/Demo2Behaviour.h"

Demo2GameObject::Demo2GameObject()
{

}

Demo2GameObject::~Demo2GameObject()
{
	
}

void Demo2GameObject::Update(float deltaTime)
{
	if (m_behaviour != nullptr)
		m_behaviour->Update(this, deltaTime);

	ApplyForce(Vector2Scale(Vector2Negate(m_velocity), m_friction));

	m_velocity = Vector2Add(m_velocity, Vector2Scale(m_acceleration, deltaTime));
	m_position = Vector2Add(m_position, Vector2Scale(m_velocity, deltaTime));
	m_acceleration = { 0, 0 };
}

void Demo2GameObject::Draw()
{
	if (m_behaviour != nullptr)
		m_behaviour->Draw(this);

	Vector2 heading = Vector2Add(m_position, m_velocity);

	DrawCircle(m_position.x, m_position.y, 8, GRAY);
	DrawLine(m_position.x, m_position.y, heading.x, heading.y, BLACK);
}

void Demo2GameObject::ApplyForce(const Vector2& force)
{
	m_acceleration = Vector2Add(m_acceleration, force);
}

// Getters
const Vector2& Demo2GameObject::GetPosition() const
{
	return m_position;
}
const Vector2& Demo2GameObject::GetVelocity() const
{
	return m_velocity;
}
const Vector2& Demo2GameObject::GetAccelertion() const
{
	return m_acceleration;
}
const float& Demo2GameObject::GetFriction() const
{
	return m_friction;
}
const float& Demo2GameObject::GetMaxSpeed() const
{
	return m_maxSpeed;
}
const float& Demo2GameObject::GetMaxForce() const
{
	return m_maxForce;
}
Demo2Behaviour* Demo2GameObject::GetBehaviour()
{
	return m_behaviour;
}

// Setters
void Demo2GameObject::SetPosition(const Vector2& pos)
{
	m_position = pos;
}
void Demo2GameObject::SetVelocity(const Vector2& vel)
{
	m_velocity = vel;
}
void Demo2GameObject::SetFriction(const float& fric)
{
	m_friction = fric;
}
void Demo2GameObject::SetMaxSpeed(const float& speed)
{
	m_maxSpeed = speed;
}
void Demo2GameObject::SetMaxForce(const float& force)
{
	m_maxForce = force;
}
void Demo2GameObject::SetBehaviour(Demo2Behaviour* behaviour)
{
	m_behaviour = behaviour;
}