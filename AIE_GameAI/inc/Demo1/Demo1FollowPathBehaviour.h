#pragma once

#include "./Game/Behaviour/Behaviour.h"
#include <functional>
#include <raymath.h>
#include "./Game/Graph2D.h"

class Demo1FollowPathBehaviour : public Behaviour
{
public:

	Demo1FollowPathBehaviour();
	virtual ~Demo1FollowPathBehaviour();

	virtual void Update(GameObject* obj, float deltaTime);
	virtual void Draw(GameObject* obj);

	void NextNode();

	const Vector2& GetTarget() const;
	void SetTarget(const Vector2& target);

	const float& GetTargetRadius() const;
	void SetTargetRadius(const float& radius);

	void OnArrive(std::function<void()> callback);

protected:

	Vector2 m_target;
	float m_targetRadius = 1.0f;
	int currentNode = 0;

private:

	std::function<void()> m_onArrivedFn;

	Graph2D* m_graph = nullptr;
};