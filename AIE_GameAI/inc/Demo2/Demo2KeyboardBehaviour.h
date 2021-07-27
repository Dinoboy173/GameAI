#pragma once

#include "./Demo2/Demo2Behaviour.h"

class Demo2KeyboardBehaviour : public Demo2Behaviour
{
public:

	Demo2KeyboardBehaviour();
	Demo2KeyboardBehaviour(int upKey, int downKey, int leftKey, int rightKey, float moveForce);
	virtual ~Demo2KeyboardBehaviour();

	virtual void Update(Demo2GameObject* obj, float deltaTime);
	virtual void Draw(Demo2GameObject* obj);

protected:

	int m_upKey;
	int m_downKey;
	int m_leftKey;
	int m_rightKey;

	float m_moveForce = 0;

private:
};