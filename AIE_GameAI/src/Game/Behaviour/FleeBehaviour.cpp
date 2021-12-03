#include "./Game/Behaviour/FleeBehaviour.h"
#include "./Game/GameObject.h"
#include "./Game/Graph2D.h"
#include "./Game/BuildWord.h"

FleeBehaviour::FleeBehaviour(BuildWorld* world) : Behaviour()
{
	m_world = world;
}

FleeBehaviour::~FleeBehaviour()
{

}

void FleeBehaviour::Update(GameObject* obj, float deltaTime)
{
	float distToTarget = Vector2Distance(obj->GetPosition(), m_target);
	if (distToTarget > m_targetRadius)
		if (m_onExitedFn)
			m_onExitedFn();
	
	obj->SetPreviousBehaviour(this);
	
	Vector2 heading = Vector2Add(obj->GetPosition(), obj->GetVelocity());
	
	Vector2 desiredDirToTarget = Vector2Normalize(Vector2Subtract(obj->GetPosition(), m_target));
	Vector2 desiredVelocity = Vector2Scale(desiredDirToTarget, obj->GetMaxSpeed());
	Vector2 targetForcePos = Vector2Add(desiredVelocity, obj->GetPosition());

	/*float distToWp = Vector2Length(Vector2Subtract(m_wanderPoint, obj->GetPosition()));

	if (distToWp < 10 ||
		Vector2Length(obj->GetVelocity()) == 0 ||
		IsKeyPressed(KEY_Q) ||
		obj->GetPreviousBehaviour() != this ||
		(obj->GetVelocity().x < 5 && obj->GetVelocity().x > -5 ||
			obj->GetVelocity().y < 5 && obj->GetVelocity().y > -5))
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

		m_wanderPoint = wanderPoint;

		auto closestWPNode = m_world->m_graph->GetClosestNode(wanderPoint, 128);

		auto func = [=](auto node) {return node == closestWPNode; };

		if (closestWPNode != nullptr)
		{
			auto nodes = m_world->m_graph->FindPath(IGraph::SearchType::DIJKSTRA, obj->GetStartNode(), func);

			obj->SetNodes(nodes);
			obj->DoFollowPath(true);
		}
		else
			return;
	}*/

	auto closestWPNode = m_world->m_graph->GetClosestNode(targetForcePos, 128);

	auto func = [=](auto node) {return node == closestWPNode; };

	if (closestWPNode != nullptr)
	{
		auto nodes = m_world->m_graph->FindPath(IGraph::SearchType::DIJKSTRA, obj->GetStartNode(), func);

		obj->SetNodes(nodes);
		obj->DoFollowPath(true);
	}
	else
		return;
	
	// if (targetForcePos.x <= 0 ||
	// 	targetForcePos.x >= m_windowSize)
	// {
	// 	targetForcePos.x -= targetForcePos.x;
	// 	targetForcePos.y -= 20;
	// }
	// 
	// if (targetForcePos.y <= 0 ||
	// 	targetForcePos.y >= m_windowSize)
	// {
	// 	targetForcePos.x -= 20;
	// 	targetForcePos.y -= targetForcePos.y;
	// }
	// 
	// if (targetForcePos.x <= 1 && targetForcePos.y <= 1)
	// {
	// 	targetForcePos = Vector2{ 20, 20 };
	// }
	
	// Vector2 forceDir = Vector2Scale(Vector2Normalize(Vector2Subtract(targetForcePos, heading)), obj->GetMaxForce());

	// obj->ApplyForce(forceDir);
}

void FleeBehaviour::Draw(GameObject* obj)
{
	DrawCircleV(m_target, m_targetRadius, { 255, 0, 0, 128 });
	DrawCircleV(m_target, 5, { 0, 0, 0, 128 });
}

const Vector2& FleeBehaviour::GetTarget() const
{
	return m_target;
}

void FleeBehaviour::SetTarget(const Vector2& target)
{
	m_target = target;
}

const float& FleeBehaviour::GetTargetRadius() const
{
	return m_targetRadius;
}

void FleeBehaviour::SetTargetRadius(const float& radius)
{
	m_targetRadius = radius;
}

void FleeBehaviour::OnExit(std::function<void()> callback)
{
	m_onExitedFn = callback;
}