#include "./Game/Behaviour/SeekBehaviour.h"
#include "./Game/GameObject.h"
#include "./Game/BuildWord.h"
#include "./Game/Graph2D.h"

SeekBehaviour::SeekBehaviour(BuildWorld* world) : Behaviour()
{
	m_target = {0, 0};
	m_world = world;
}

SeekBehaviour::~SeekBehaviour()
{
	
}

void SeekBehaviour::Update(GameObject* obj)
{
	float distToSp = Vector2Length(Vector2Subtract(m_seekPoint, obj->GetPosition()));
	float targetDist = Vector2Length(Vector2Subtract(m_target, obj->GetPosition()));

	obj->SetPreviousBehaviour(this);

	if (distToSp < 10)
		if (m_onArrivedFn)
			m_onArrivedFn();

	obj->SetPreviousBehaviour(this);

	auto closestWPNode = m_world->m_graph->GetClosestNode(m_target, 128);
	auto func = [=](auto node) {return node == closestWPNode; };

	if (closestWPNode != nullptr)
	{
		auto nodes = m_world->m_graph->FindPath(IGraph::SearchType::DIJKSTRA, obj->GetStartNode(), func);

		obj->SetNodes(nodes);
		obj->DoFollowPath(true);
	}
	else
		return;
}

void SeekBehaviour::Draw(GameObject* obj)
{
	DrawCircleV(m_target, m_targetRadius, { 255, 0, 0, 128 });
	DrawCircleV(m_seekPoint, 5, { 0, 0, 0, 128 });
}

const Vector2& SeekBehaviour::GetTarget() const
{
	return m_target;
}

void SeekBehaviour::SetTarget(const Vector2& target)
{
	m_target = target;
}

const float& SeekBehaviour::GetTargetRadius() const
{
	return m_targetRadius;
}

void SeekBehaviour::SetTargetRadius(const float& radius)
{
	m_targetRadius = radius;
}

void SeekBehaviour::OnArrive(std::function<void()> callback)
{
	m_onArrivedFn = callback;
}