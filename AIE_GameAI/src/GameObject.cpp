#include "GameObject.h"

GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}

void GameObject::Update(float deltaTime)
{
	// m_velocity += m_acceleration * deltaTime;
	// m_position += m_velocity * deltaTime;
	// m_acceleration = {0, 0};

	// upto vid 3 18:59
}

void GameObject::Draw()
{
	DrawCircle(m_position.x, m_position.y, 8, GRAY);
}

void GameObject::ApplyForce(const Vector2& force)
{
	// m_acceleration += force;
	m_acceleration = Vector2Add(m_acceleration, force);
}

// Getters
const Vector2& GameObject::GetPosition() const
{
	return m_position;
}
const Vector2& GameObject::GetVelocity() const
{
	return m_velocity;
}
const Vector2& GameObject::GetAccelertion() const
{
	return m_acceleration;
}
const float& GameObject::GetFriction() const
{
	return m_friction;
}

// Setters
void GameObject::SetPosition(const Vector2& pos)
{
	m_position = pos;
}
void GameObject::SetVelocity(const Vector2& vel)
{
	m_velocity = vel;
}
void GameObject::SetFriction(const float& fric)
{
	m_friction = fric;
}