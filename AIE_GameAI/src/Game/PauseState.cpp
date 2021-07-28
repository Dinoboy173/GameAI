#include "./Game/PauseState.h"
#include "./Menu/Application.h"
#include "./Menu/GameStateManager.h"
#include "raylib.h"

#include <iostream>

PauseState::PauseState(Application* app) : m_app(app)
{

}

PauseState::~PauseState()
{

}

void PauseState::Load()
{
	std::cout << "Loading Pause\n";
}

void PauseState::Unload()
{
	std::cout << "Unloading Pause\n";
}

void PauseState::Update(float dt)
{
	if (IsKeyPressed(KeyboardKey(KEY_P)))
	{
		m_app->GetGameStateManager()->PopState();
	}
	else if (IsKeyPressed(KeyboardKey(KEY_BACKSPACE)))
	{
		m_app->GetGameStateManager()->PopState();
		m_app->GetGameStateManager()->PopState();
		m_app->GetGameStateManager()->PushState("Menu");
	}
}

void PauseState::Draw()
{
	DrawText("Pause", 10, 10, 50, LIGHTGRAY);
}