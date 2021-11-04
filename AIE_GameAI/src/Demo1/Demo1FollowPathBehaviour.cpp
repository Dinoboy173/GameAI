#include "Demo1/Demo1FollowPathBehaviour.h"
#include "./Game/GameObject.h"

Demo1FollowPathBehaviour::Demo1FollowPathBehaviour() : Behaviour()
{
	m_graph = new Graph2D();

	// top row
	auto nodeA = m_graph->AddNode({ 100, 100 });
	auto nodeB = m_graph->AddNode({ 200, 100 });
	auto nodeC = m_graph->AddNode({ 300, 100 });
	auto nodeD = m_graph->AddNode({ 400, 100 });
	auto nodeE = m_graph->AddNode({ 500, 100 });
	auto nodeF = m_graph->AddNode({ 600, 100 });
	auto nodeG = m_graph->AddNode({ 700, 100 });
	auto nodeH = m_graph->AddNode({ 800, 100 });

	// right middle
	auto nodeI = m_graph->AddNode({ 800, 200 });

	// bottom row
	auto nodeJ = m_graph->AddNode({ 800, 300 });
	auto nodeK = m_graph->AddNode({ 700, 300 });
	auto nodeL = m_graph->AddNode({ 600, 300 });
	auto nodeM = m_graph->AddNode({ 500, 300 });
	auto nodeN = m_graph->AddNode({ 400, 300 });
	auto nodeO = m_graph->AddNode({ 300, 300 });
	auto nodeP = m_graph->AddNode({ 200, 300 });
	auto nodeQ = m_graph->AddNode({ 100, 300 });

	// left middle
	auto nodeR = m_graph->AddNode({ 100, 201 });

	// connects nodes
	for (auto node : m_graph->GetNodes())
	{
		std::vector<Graph2D::Node*> nearbyNodes;

		m_graph->GetNearbyNodes(node->data, 101, nearbyNodes);

		for (auto connectedNode : nearbyNodes)
		{
			if (connectedNode == node)
				continue;

			m_graph->AddEdge(node, connectedNode, 1);
			m_graph->AddEdge(connectedNode, node, 1);
		}
	}

	m_target = nodeA->data;
}

Demo1FollowPathBehaviour::~Demo1FollowPathBehaviour()
{
	delete m_graph;
	m_graph = nullptr;
}

void Demo1FollowPathBehaviour::Update(GameObject* obj, float deltaTime)
{
	float distToTarget = Vector2Distance(obj->GetPosition(), m_target);

	if (distToTarget < m_targetRadius)
		if (m_onArrivedFn)
			m_onArrivedFn();

	Vector2 heading = Vector2Add(obj->GetPosition(), obj->GetVelocity());

	Vector2 desiredDirToTarget = Vector2Normalize(Vector2Subtract(m_target, obj->GetPosition()));
	Vector2 desiredVelocity = Vector2Scale(desiredDirToTarget, obj->GetMaxSpeed());
	Vector2 targetForcePos = Vector2Add(desiredVelocity, obj->GetPosition());
	Vector2 forceDir = Vector2Scale(Vector2Normalize(Vector2Subtract(targetForcePos, heading)), obj->GetMaxForce());

	obj->ApplyForce(forceDir);
}

void Demo1FollowPathBehaviour::Draw(GameObject* obj)
{
	DrawText("Demo1", 10, 10, 20, LIGHTGRAY);

	// Draw all connections
	for (auto node : m_graph->GetNodes())
	{
		for (auto connection : node->connections)
		{
			DrawLine(node->data.x, node->data.y, connection.to->data.x, connection.to->data.y, GRAY);
		}
	}

	// Draw all nodes
	for (auto node : m_graph->GetNodes())
	{
		DrawCircle(node->data.x, node->data.y, 8, LIGHTGRAY);
		DrawCircleLines(node->data.x, node->data.y, 8, GRAY);
	}
}

void Demo1FollowPathBehaviour::NextNode()
{
	int size = m_graph->GetNodes().size();

	if (currentNode < size - 1)
		currentNode++;
	else
		currentNode = 0;

	m_target = m_graph->GetNodes().at(currentNode)->data;
}

const Vector2& Demo1FollowPathBehaviour::GetTarget() const
{
	return m_target;
}

void Demo1FollowPathBehaviour::SetTarget(const Vector2& target)
{
	m_target = target;
}

const float& Demo1FollowPathBehaviour::GetTargetRadius() const
{
	return m_targetRadius;
}

void Demo1FollowPathBehaviour::SetTargetRadius(const float& radius)
{
	m_targetRadius = radius;
}

void Demo1FollowPathBehaviour::OnArrive(std::function<void()> callback)
{
	m_onArrivedFn = callback;
}