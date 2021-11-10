#pragma once

#include "./Game/GameObject.h"

class Demo1KeyboardBehaviour;
class Demo1SeekBehaviour;
class Demo1FleeBehaviour;
class Demo1WanderBehaviour;
class Demo1FollowPathBehaviour;

class Demo1Player : public GameObject
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
	Demo1FollowPathBehaviour* m_followPathBehaviour;

private:
};