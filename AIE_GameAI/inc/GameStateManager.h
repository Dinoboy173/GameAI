#pragma once

#include <map>
#include <list>
#include <functional>

class IGameState;

class GameStateManager
{
public:

	GameStateManager();
	~GameStateManager();

	void Update(float dt);
	void Draw();

	void SetState(const char* name, IGameState* state);
	void PushState(const char* name);
	void PopState();

protected:

	std::map<const char*, IGameState*> m_states;
	std::list<IGameState*> m_stack;
	std::list < std::function<void()> > m_commands;

private:
};