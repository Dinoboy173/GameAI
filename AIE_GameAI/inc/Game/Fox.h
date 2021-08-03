#pragma once

#include "./Game/GameObject.h"

class WanderBehaviour;

class Fox : public GameObject
{
public:

	Fox();
	virtual ~Fox();

	virtual void Update(float dt);
	virtual void Draw();

protected:

	WanderBehaviour* m_wanderBehaviour;

private:
};