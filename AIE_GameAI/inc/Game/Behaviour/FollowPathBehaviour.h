#pragma once

#include "./Game/Graph.h"
#include "./Game/Behaviour/Behaviour.h"
#include <raymath.h>
#include <vector>

class BuildWorld;
class Graph2D;

class FollowPathBehaviour : public Behaviour
{
public:

	FollowPathBehaviour();
	virtual ~FollowPathBehaviour();

	virtual void Update(GameObject* obj, float deltaTime);
	virtual void Draw(GameObject* obj);

	void NextNode();

	const Vector2& GetTarget() const;
	void SetTarget(const Vector2& target);

	const float& GetTargetRadius() const;
	void SetTargetRadius(const float& radius);

	void OnArrive(std::function<void()> callback);

	void SetGraph(Graph2D* graph);
	Graph2D* GetGraph();

	void SetPath(std::vector<Graph<Vector2, float>::Node*> nodes);

protected:

	Vector2 m_target;
	float m_targetRadius = 1.0f;
	int m_currentNode = 0;

	// list of nodes
	std::vector<Graph<Vector2, float>::Node*> m_nodes;

private:

	std::function<void()> m_onArrivedFn;

	Graph2D* m_graph = nullptr;
	BuildWorld* m_world;
};