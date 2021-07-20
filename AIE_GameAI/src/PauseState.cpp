#include "PauseState.h"
#include "Application.h"
#include "GameStateManager.h"
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
}

void PauseState::Draw()
{
	DrawText("Pause", 10, 10, 50, LIGHTGRAY);
}