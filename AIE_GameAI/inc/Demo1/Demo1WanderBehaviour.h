#pragma once

#include "./Demo1/Demo1Behaviour.h"
#include "raymath.h"
#include <functional>

class Demo1WanderBehaviour : public Demo1Behaviour
{
public:

	Demo1WanderBehaviour();         
	virtual ~Demo1WanderBehaviour();

	virtual void Update(Demo1GameObject* obj, float deltaTime);
	virtual void Draw(Demo1GameObject* obj);

	const Vector2& GetTarget() const;
	void SetTarget(const Vector2& target);

	const float& GetTargetRadius() const;
	void SetTargetRadius(const float& radius);

protected:

	Vector2 m_target;
	float m_targetRadius = 1.0f;

	Vector2 m_wanderCenter = { 0.0f, 0.0f };
	Vector2 m_wanderPoint = { 0.0f, 0.0f };

private:
};