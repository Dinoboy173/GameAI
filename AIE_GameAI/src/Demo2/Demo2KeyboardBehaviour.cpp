#include "./Demo2/Demo2KeyboardBehaviour.h"
#include "./Demo2/Demo2GameObject.h"
#include "raylib.h"

Demo2KeyboardBehaviour::Demo2KeyboardBehaviour() : Demo2Behaviour()
{
	m_upKey = KEY_W;
	m_downKey = KEY_S;
	m_leftKey = KEY_A;
	m_rightKey = KEY_D;
	m_moveForce = 100;
}

Demo2KeyboardBehaviour::Demo2KeyboardBehaviour(int upKey, int downKey, int leftKey, int rightKey, float moveForce) :
	Demo2Behaviour(),
	m_upKey(upKey),
	m_downKey(downKey),
	m_leftKey(leftKey),
	m_rightKey(rightKey),
	m_moveForce(moveForce)
{
	
}

Demo2KeyboardBehaviour::~Demo2KeyboardBehaviour()
{

}

void Demo2KeyboardBehaviour::Update(Demo2GameObject* obj, float deltaTime)
{
	if (IsKeyDown(m_upKey)) obj->ApplyForce({ 0, -m_moveForce });
	if (IsKeyDown(m_downKey)) obj->ApplyForce({ 0, m_moveForce });
	if (IsKeyDown(m_leftKey)) obj->ApplyForce({ -m_moveForce, 0 });
	if (IsKeyDown(m_rightKey)) obj->ApplyForce({ m_moveForce, 0 });
}

void Demo2KeyboardBehaviour::Draw(Demo2GameObject* obj)
{

}