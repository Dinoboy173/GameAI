#pragma once

#include "raymath.h"

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Update(float deltaTime);
	virtual void Draw();

	void ApplyForce(const Vector2& force);

	// Getters
	const Vector2& GetPosition() const;
	const Vector2& GetVelocity() const;
	const Vector2& GetAccelertion() const;
	const float& GetFriction() const;

	// Setters
	void SetPosition(const Vector2& pos);
	void SetVelocity(const Vector2& vel);
	void SetFriction(const float& fric);

protected:

	Vector2 m_position;
	Vector2 m_velocity;
	Vector2 m_acceleration;
	float m_friction;

private:
};