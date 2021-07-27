#pragma once

#include "./Menu/IGameState.h"
#include "raylib.h"
#include <./Demo2/Demo2Graph.h>

class Application;
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

};