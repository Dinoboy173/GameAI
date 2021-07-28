#include "./Game/Graph.h"
#include "raymath.h"

class Graph2D : public Graph<Vector2, float>
{
public:
	Graph2D();
	virtual ~Graph2D();

	void GetNearbyNodes(Vector2 position, float radius, std::vector<Graph2D::Node*>& out_nodes);

protected:
private:
};