#pragma once
#include "raylib.h"

//Predeclare classes
class GameObject;
class GameStateManager;

class Application
{
public:
	Application(int windowWidth, int windowHeight, const char *windowTitle);
	~Application();

	void Run();

	void Load();
	void Unload();
	void Update(float deltaTime);
	void Draw();

	GameStateManager* GetGameStateManager();

protected:
private:

	int m_windowWidth;
	int m_windowHeight;
	const char* m_windowTitle;

	GameObject* m_player = nullptr;

	GameStateManager* m_gameStateManager = nullptr;
};