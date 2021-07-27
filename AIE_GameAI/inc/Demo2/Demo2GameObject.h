#pragma once

#include "raymath.h"

class Demo2Behaviour;

class Demo2GameObject
{
public:
	Demo2GameObject();
	virtual ~Demo2GameObject();

	virtual void Update(float deltaTime);
	virtual void Draw();

	void ApplyForce(const Vector2& force);

	// Getters
	const Vector2& GetPosition() const;
	const Vector2& GetVelocity() const;
	const Vector2& GetAccelertion() const;
	const float& GetFriction() const;

	const float& GetMaxSpeed() const;
	const float& GetMaxForce() const;
	
	Demo2Behaviour* GetBehaviour();

	// Setters
	void SetPosition(const Vector2& pos);
	void SetVelocity(const Vector2& vel);
	void SetFriction(const float& fric);

	void SetMaxSpeed(const float& speed);
	void SetMaxForce(const float& force);

	void SetBehaviour(Demo2Behaviour* behaviour);

protected:

	Vector2 m_position = { 0.0f, 0.0f };
	Vector2 m_velocity = { 0.0f, 0.0f };
	Vector2 m_acceleration = { 0.0f, 0.0f };
	float m_friction = 0.0f;
	float m_maxSpeed = 100.0f;
	float m_maxForce = 100.0f;

	Demo2Behaviour* m_behaviour = nullptr;

private:
};