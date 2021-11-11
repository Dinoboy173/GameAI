#pragma once

#include "./Game/Behaviour/Behaviour.h"
#include "raymath.h"
#include <functional>
#include "./Game/Graph.h"
#include "./Game/BuildWord.h"
#include "./Menu/Application.h"

class BuildWorld;
class Application;

class WanderBehaviour : public Behaviour
{
public:

	WanderBehaviour();
	virtual ~WanderBehaviour();

	virtual void Update(GameObject* obj, float deltaTime);
	virtual void Draw();

	const Vector2& GetTarget() const;
	void SetTarget(const Vector2& target);

	const float& GetTargetRadius() const;
	void SetTargetRadius(const float& radius);

protected:

	Vector2 m_target;
	float m_targetRadius = 1.0f;
	int m_windowSize = 1024;

	Vector2 m_wanderCenter = { 0.0f, 0.0f };
	Vector2 m_wanderPoint = { 0.0f, 0.0f };

	BuildWorld* m_world;

private:
};