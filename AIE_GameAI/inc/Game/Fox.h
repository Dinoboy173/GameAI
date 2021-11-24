#pragma once

#include "./Game/GameObject.h"

class WanderBehaviour;
class SeekBehaviour;
class FollowPathBehaviour;

class Rabbit;
class BuildWorld;

class Fox : public GameObject
{
public:

	Fox();
	virtual ~Fox();

	virtual void Update(float dt, BuildWorld* world);
	virtual void Draw();

	Behaviour* CalculateDesiredBehaviour(BuildWorld* world);

protected:

	BuildWorld* m_world;

	WanderBehaviour* m_wanderBehaviour;
	SeekBehaviour* m_seekBehaviour;
	FollowPathBehaviour* m_followPathBehaviour;

private:

	float m_seekRadius = 100.0f;

};