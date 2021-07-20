#pragma once

#include "IGameState.h"
#include "raylib.h"
#include <Graph.h>

class Application;
class GameObject;
class BuildWorld;

class PlayState : public IGameState
{
public:

	PlayState(Application* app);
	virtual ~PlayState();

	virtual void Load();
	virtual void Unload();

	virtual void Update(float dt);
	virtual void Draw();

protected:
private:

	Application* m_app;
	BuildWorld* m_world;

	GameObject* m_player = nullptr;

};