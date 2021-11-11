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

protected:

	WanderBehaviour* m_wanderBehaviour;
	FleeBehaviour* m_fleeBehaviour;
	BuildWorld* m_world;

private:

	float m_fleeRadius = 60.0f;

};