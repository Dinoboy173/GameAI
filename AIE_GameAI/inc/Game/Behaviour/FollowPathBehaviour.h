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

	void NextNode(GameObject* obj);

	const Vector2& GetTarget() const;
	void SetTarget(const Vector2& target);

	const float& GetTargetRadius() const;
	void SetTargetRadius(const float& radius);

	void OnArrive(std::function<void()> callback);

	void SetGraph(Graph2D* graph);
	Graph2D* GetGraph();

	void SetPath(std::list<Graph<Vector2, float>::Node*> nodes);

	bool m_hasStart = false;

protected:

	Vector2 m_target;
	float m_targetRadius = 1.0f;

	std::list<Graph<Vector2, float>::Node*>::iterator m_currentNode;

	// list of nodes
	std::list<Graph<Vector2, float>::Node*> m_nodes;

private:

	std::function<void()> m_onArrivedFn;

	Graph2D* m_graph = nullptr;
	BuildWorld* m_world;
};