#pragma once

#include "./Game/GameObject.h"

class WanderBehaviour;

class Rabbit : public GameObject
{
public:

	Rabbit();
	virtual ~Rabbit();

	virtual void Update(float dt);
	virtual void Draw();

protected:

	WanderBehaviour* m_wanderBehaviour;

private:
};