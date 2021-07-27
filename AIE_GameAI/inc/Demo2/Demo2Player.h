#pragma once

#include "./Demo2/Demo2GameObject.h"

class Demo2KeyboardBehaviour;
class Demo2SeekBehaviour;
class Demo2FleeBehaviour;
class Demo2WanderBehaviour;

class Player : public Demo2GameObject
{
public:

	Player();
	virtual ~Player();

	virtual void Update(float deltaTime);
	virtual void Draw();

protected:

	Demo2KeyboardBehaviour* m_kbBehaviour;
	Demo2SeekBehaviour* m_seekBehaviour;
	Demo2FleeBehaviour* m_fleeBehaviour;
	Demo2WanderBehaviour* m_wanderBehaviour;

private:
};