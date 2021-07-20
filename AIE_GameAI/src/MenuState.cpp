#include "MenuState.h"
#include "Application.h"
#include "GameStateManager.h"
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
	if (IsKeyPressed(KeyboardKey(KEY_SPACE)))
	{
		m_app->GetGameStateManager()->SetState("Menu", nullptr);
		m_app->GetGameStateManager()->PopState();
		m_app->GetGameStateManager()->PushState("Play");
	}
}

void MenuState::Draw()
{
	DrawText("Menu", 10, 10, 20, LIGHTGRAY);
}