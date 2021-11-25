#pragma once

#include "./Game/GameObject.h"

class WanderBehaviour;
class FleeBehaviour;
class FollowPathBehaviour;

class BuildWorld;

class Rabbit : public GameObject
{
public:

	Rabbit(BuildWorld* world);
	virtual ~Rabbit();

	virtual void Update(float dt);
	virtual void Draw();

	Behaviour* CalculateDesiredBehaviour(Vector2 foxPos);

protected:

	BuildWorld* m_world = nullptr;

	WanderBehaviour* m_wanderBehaviour;
	FleeBehaviour* m_fleeBehaviour;
	FollowPathBehaviour* m_followPathBehaviour;

private:

	float m_fleeRadius = 100.0f;
	float m_mateRadius = 25.0f;

};