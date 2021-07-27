#pragma once

#include "./Demo2/Demo2Behaviour.h"
#include "raymath.h"

#include <functional>

class Demo2SeekBehaviour : public Demo2Behaviour
{
public:

	Demo2SeekBehaviour();
	virtual ~Demo2SeekBehaviour();

	virtual void Update(Demo2GameObject* obj, float deltaTime);
	virtual void Draw(Demo2GameObject* obj);

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