#pragma once

#include "./Game/Behaviour/Behaviour.h"
#include "raymath.h"
#include <functional>

class BuildWorld;

class FleeBehaviour : public Behaviour
{
public:

	FleeBehaviour(BuildWorld* world);
	virtual ~FleeBehaviour();

	virtual void Update(GameObject* obj, float deltaTime);
	virtual void Draw(GameObject* obj);

	const Vector2& GetTarget() const;
	void SetTarget(const Vector2& target);

	const float& GetTargetRadius() const;
	void SetTargetRadius(const float& radius);

	void OnExit(std::function<void()> callback);

protected:

	Vector2 m_fleePoint = { 0.0f, 0.0f };

	Vector2 m_target;
	float m_targetRadius = 1.0f;
	int m_windowSize = 1024;

	std::function<void()> m_onExitedFn;

	BuildWorld* m_world = nullptr;

private:
};