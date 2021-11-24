#pragma once

#include "./Game/GameObject.h"

class WanderBehaviour;
class FleeBehaviour;
class BuildWorld;

class Rabbit : public GameObject
{
public:

	Rabbit();
	virtual ~Rabbit();

	virtual void Update(float dt, BuildWorld* world);
	virtual void Draw();

	Behaviour* CalculateDesiredBehaviour(BuildWorld* world, Vector2 foxPos);

protected:

	WanderBehaviour* m_wanderBehaviour;
	FleeBehaviour* m_fleeBehaviour;
	BuildWorld* m_world;

private:

	float m_fleeRadius = 100.0f;
	float m_mateRadius = 25.0f;

};