#pragma once

#include "./Demo1/Demo1Behaviour.h"

class Demo1KeyboardBehaviour : public Demo1Behaviour
{
public:

	Demo1KeyboardBehaviour();
	Demo1KeyboardBehaviour(int upKey, int downKey, int leftKey, int rightKey, float moveForce);
	virtual ~Demo1KeyboardBehaviour();

	virtual void Update(Demo1GameObject* obj, float deltaTime);
	virtual void Draw(Demo1GameObject* obj);

protected:

	int m_upKey;
	int m_downKey;
	int m_leftKey;
	int m_rightKey;

	float m_moveForce = 0;

private:
};