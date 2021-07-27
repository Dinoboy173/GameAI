#pragma once

#include "./Demo1/Demo1Behaviour.h"
#include "raymath.h"

#include <functional>

class Demo1SeekBehaviour : public Demo1Behaviour
{
public:

	Demo1SeekBehaviour();
	virtual ~Demo1SeekBehaviour();

	virtual void Update(Demo1GameObject* obj, float deltaTime);
	virtual void Draw(Demo1GameObject* obj);

	const Vector2& GetTarget() const;
	void SetTarget(const Vector2& target);

	const float& GetTargetRadius() const;
	void SetTargetRadius(const float& radius);

	void OnArrive(std::function<void()> callback);

protected:

	Vector2 m_target;
	float m_targetRadius = 1.0f;

	std::function<void()> m_onArrivedFn;

private:
};