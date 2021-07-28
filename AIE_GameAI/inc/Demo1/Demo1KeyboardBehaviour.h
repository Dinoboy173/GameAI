#pragma once

#include "./Game/Behaviour/Behaviour.h"

class Demo1KeyboardBehaviour : public Behaviour
{
public:

	Demo1KeyboardBehaviour();
	Demo1KeyboardBehaviour(int upKey, int downKey, int leftKey, int rightKey, float moveForce);
	virtual ~Demo1KeyboardBehaviour();

	virtual void Update(GameObject* obj, float deltaTime);
	virtual void Draw(GameObject* obj);

protected:

	int m_upKey;
	int m_downKey;
	int m_leftKey;
	int m_rightKey;

	float m_moveForce = 0;

private:
};