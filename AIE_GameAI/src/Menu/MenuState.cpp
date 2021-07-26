#include "./Menu/MenuState.h"
#include "./Menu/Application.h"
#include "./Menu/GameStateManager.h"
#include "raylib.h"

#include <iostream>

MenuState::MenuState(Application *app) : m_app(app)
{

}

MenuState::~MenuState()
{

}

void MenuState::Load()
{
	std::cout << "Loading Menu\n";
}

void MenuState::Unload()
{
	std::cout << "Unloading Menu\n";
}

void MenuState::Update(float dt)
{
	if (IsKeyPressed(KeyboardKey(KEY_ONE)))
	{
		m_app->GetGameStateManager()->SetState("Menu", nullptr);
		m_app->GetGameStateManager()->PopState();
		m_app->GetGameStateManager()->PushState("Demo1");
	}
	else if (IsKeyPressed(KeyboardKey(KEY_THREE)))
	{
		m_app->GetGameStateManager()->SetState("Menu", nullptr);
		m_app->GetGameStateManager()->PopState();
		m_app->GetGameStateManager()->PushState("Play");
	}
}

void MenuState::Draw()
{
	DrawText("Menu", 10, 10, 20, LIGHTGRAY);
	DrawText("1. Demo1", 10, 40, 40, LIGHTGRAY);
	DrawText("2. Demo2", 10, 90, 40, LIGHTGRAY);
	DrawText("3. Play", 10, 140, 40, LIGHTGRAY);
}