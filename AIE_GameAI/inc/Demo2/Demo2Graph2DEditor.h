#pragma once

class Demo2Graph2D;

class Demo2Graph2DEditor
{
public:

	Demo2Graph2DEditor();
	~Demo2Graph2DEditor();

	void Update(float dt);
	void Draw();

	Demo2Graph2D* GetGraph();
	void SetGraph(Demo2Graph2D* graph);

protected:

	Demo2Graph2D* m_graph;

private:
};