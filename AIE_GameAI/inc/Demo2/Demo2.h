#pragma once

#include "./Menu/IGameState.h"
#include "./Demo2/Demo2Graph2DEditor.h"

class Application;
class Graph2D;
class Demo2Graph2DEditor;

class Demo2 : public IGameState
{
public:

	Demo2(Application* app);
	virtual ~Demo2();

	virtual void Load();
	virtual void Unload();

	virtual void Update(float dt);
	virtual void Draw();

protected:
private:

	Application* m_app;

	Graph2D* m_graph = nullptr;

};