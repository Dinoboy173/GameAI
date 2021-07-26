#pragma once

#include "./Menu/IGameState.h"

class Application;
class GameObject;

class Demo1 : public IGameState
{
public:

	Demo1(Application* app);
	virtual ~Demo1();

	virtual void Load();
	virtual void Unload();

	virtual void Update(float dt);
	virtual void Draw();

protected:
private:

	Application* m_app;

	GameObject* m_player = nullptr;

};