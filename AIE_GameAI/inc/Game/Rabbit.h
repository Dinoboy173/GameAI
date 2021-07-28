#pragma once

#include "./Game/GameObject.h"
#include "./Game/BuildWord.h"

class WanderBehaviour;

class Rabbit : public GameObject, public BuildWorld
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