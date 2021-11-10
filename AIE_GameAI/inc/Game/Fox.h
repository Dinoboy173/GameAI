#pragma once

#include "./Game/GameObject.h"

class WanderBehaviour;
class SeekBehaviour;
class Rabbit;
class BuildWorld;

class Fox : public GameObject
{
public:

	Fox();
	virtual ~Fox();

	virtual void Update(float dt);
	virtual void Draw();

protected:

	Rabbit* m_rabbit;
	BuildWorld* m_world;

	WanderBehaviour* m_wanderBehaviour;
	SeekBehaviour* m_seekBehaviour;

private:

	float seekRadius = 100.0f;

};