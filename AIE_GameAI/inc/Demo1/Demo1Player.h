#pragma once

#include "./Demo1/Demo1GameObject.h"

class Demo1KeyboardBehaviour;
class Demo1SeekBehaviour;
class Demo1FleeBehaviour;
class Demo1WanderBehaviour;

class Demo1Player : public Demo1GameObject
{
public:

	Demo1Player();
	virtual ~Demo1Player();

	virtual void Update(float deltaTime);
	virtual void Draw();

protected:

	Demo1KeyboardBehaviour* m_kbBehaviour;
	Demo1SeekBehaviour* m_seekBehaviour;
	Demo1FleeBehaviour* m_fleeBehaviour;
	Demo1WanderBehaviour* m_wanderBehaviour;

private:
};