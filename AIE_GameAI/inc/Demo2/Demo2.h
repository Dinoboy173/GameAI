#pragma once

#include "./Menu/IGameState.h"

class Application;

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

};