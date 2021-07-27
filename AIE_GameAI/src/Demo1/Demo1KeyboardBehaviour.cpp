#include "./Demo1/Demo1KeyboardBehaviour.h"
#include "./Demo1/Demo1GameObject.h"
#include "raylib.h"

Demo1KeyboardBehaviour::Demo1KeyboardBehaviour() : Demo1Behaviour()
{
	m_upKey = KEY_W;
	m_downKey = KEY_S;
	m_leftKey = KEY_A;
	m_rightKey = KEY_D;
	m_moveForce = 100;
}

Demo1KeyboardBehaviour::Demo1KeyboardBehaviour(int upKey, int downKey, int leftKey, int rightKey, float moveForce) :
	Demo1Behaviour(),
	m_upKey(upKey),
	m_downKey(downKey),
	m_leftKey(leftKey),
	m_rightKey(rightKey),
	m_moveForce(moveForce)
{
	
}

Demo1KeyboardBehaviour::~Demo1KeyboardBehaviour()
{

}

void Demo1KeyboardBehaviour::Update(Demo1GameObject* obj, float deltaTime)
{
	if (IsKeyDown(m_upKey)) obj->ApplyForce({ 0, -m_moveForce });
	if (IsKeyDown(m_downKey)) obj->ApplyForce({ 0, m_moveForce });
	if (IsKeyDown(m_leftKey)) obj->ApplyForce({ -m_moveForce, 0 });
	if (IsKeyDown(m_rightKey)) obj->ApplyForce({ m_moveForce, 0 });
}

void Demo1KeyboardBehaviour::Draw(Demo1GameObject* obj)
{

}