#include "./Game/Behaviour/WanderBehaviour.h"
#include "./Game/GameObject.h"
#include "./Game/Graph2D.h"
#include <stdio.h>
#include <stdlib.h>
#include <random>
#include <time.h>
#include <iostream>

WanderBehaviour::WanderBehaviour(BuildWorld* world) : Behaviour()
{
	m_target = Vector2{ 0, 0 };
	m_world = world;
}
WanderBehaviour::~WanderBehaviour()
{

}

void WanderBehaviour::Update(GameObject* obj, float deltaTime)
{
	float distToWp = Vector2Length(Vector2Subtract(m_wanderPoint, obj->GetPosition()));

	if (distToWp < 10 || Vector2Length(obj->GetVelocity()) == 0 || IsKeyPressed(KEY_Q) || obj->GetPreviousBehaviour() != this)
	{
		obj->SetPreviousBehaviour(this);

		Vector2 wanderCenter;

		if (Vector2Length(obj->GetVelocity()) == 0)
		{
			Vector2 newVel = { 1, 1 };
			obj->SetVelocity(newVel);
		}

		wanderCenter = obj->GetPosition();

		auto angle = (rand() % 360) * PI / 180.0f;

		Vector2 displace = { sin(angle) * m_targetRadius, cos(angle) * m_targetRadius };

		Vector2 wanderPoint = Vector2Add(wanderCenter, displace);

		if (wanderPoint.x <= 0 ||
			wanderPoint.x >= m_windowSize ||
			wanderPoint.y <= 0 ||
			wanderPoint.y >= m_windowSize)
		{
			return;
		}

		// check for null
		auto closestWPNode = m_world->m_graph->GetClosestNode(wanderPoint, 20);

		if (closestWPNode != nullptr)
			wanderPoint = closestWPNode->data;

		SetTarget(wanderPoint);
		m_wanderCenter = wanderCenter;
		m_wanderPoint = wanderPoint;
	}

	Vector2 wanderTotalDistance = Vector2Scale(Vector2Normalize(Vector2Subtract(m_wanderPoint, obj->GetPosition())), obj->GetMaxForce());

	obj->ApplyForce(wanderTotalDistance);
}

void WanderBehaviour::Draw(GameObject* obj)
{
	DrawCircleV(m_wanderCenter, m_targetRadius, { 255, 0, 0, 128 });
	DrawCircleV(m_wanderPoint, 5, { 0, 0, 0, 128 });
}

const Vector2& WanderBehaviour::GetTarget() const
{
	return m_target;
}

void WanderBehaviour::SetTarget(const Vector2& target)
{
	m_target = target;
}

const float& WanderBehaviour::GetTargetRadius() const
{
	return m_targetRadius;
}

void WanderBehaviour::SetTargetRadius(const float& radius)
{
	m_targetRadius = radius;
}