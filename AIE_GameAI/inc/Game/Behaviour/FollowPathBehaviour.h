#pragma once

#include "./Game/Behaviour/Behaviour.h"
#include <functional>
#include <raymath.h>
#include "./Game/Graph2D.h"
#include "./Game/Graph.h"

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

protected:

	Vector2 m_target;
	float m_targetRadius = 1.0f;
	int currentNode = 0;

	// list of nodes
	std::list<Graph<Vector2, float>::Node*> nodes;

private:

	std::function<void()> m_onArrivedFn;

	Graph2D* m_graph = nullptr;
	BuildWorld* m_world;
};