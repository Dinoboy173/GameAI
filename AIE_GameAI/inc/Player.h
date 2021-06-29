#pragma once

#include "GameObject.h"

class KeyboardBehaviour;
class SeekBehaviour;
class FleeBehaviour;
class WanderBehaviour;

class Player : public GameObject
{
public:

	Player();
	virtual ~Player();

	virtual void Update(float deltaTime);
	virtual void Draw();

protected:

	KeyboardBehaviour* m_kbBehaviour;
	SeekBehaviour* m_seekBehaviour;
	FleeBehaviour* m_fleeBehaviour;
	WanderBehaviour* m_wanderBehaviour;

private:
};