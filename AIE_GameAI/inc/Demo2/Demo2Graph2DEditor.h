#pragma once

class Graph2D;

class Demo2Graph2DEditor
{
public:

	Demo2Graph2DEditor();
	~Demo2Graph2DEditor();

	void Update(float dt);
	void Draw();

	Graph2D* GetGraph();
	void SetGraph(Graph2D* graph);

protected:

	Graph2D* m_graph;

private:

	int m_radius = 60;

};