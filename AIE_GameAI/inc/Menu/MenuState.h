#pragma once

#include "IGameState.h"

class Application;

class MenuState : public IGameState
{
public:

	MenuState(Application *app);
	virtual ~MenuState();

	virtual void Load();
	virtual void Unload();

	virtual void Update(float dt);
	virtual void Draw();

protected:
private:

	Application *m_app;

};