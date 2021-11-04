#include "./Demo1/Demo1.h"
#include "./Menu/Application.h"
#include "./Menu/GameStateManager.h"
#include "./Demo1/Demo1Player.h"
#include "./Demo1/Demo1KeyboardBehaviour.h"
#include "./Game/GameObject.h"
#include "./Game/Graph.h"
#include "raylib.h"

#include <iostream>

Demo1::Demo1(Application* app) : m_app(app)
{

}

Demo1::~Demo1()
{

}

void Demo1::Load()
{
	std::cout << "Loading Demo1\n";

	m_player = new Demo1Player();
	m_player->SetPosition({ 500, 500 });
	m_player->SetFriction(1.0f);
}

void Demo1::Unload()
{
	std::cout << "Unloading Demo1\n";

	delete m_player;
	m_player = nullptr;
}

void Demo1::Update(float dt)
{
	if (IsKeyPressed(KeyboardKey(KEY_BACKSPACE)))
	{
		m_app->GetGameStateManager()->PopState();
		m_app->GetGameStateManager()->PushState("Menu");
	}

	m_player->Update(dt);
}

void Demo1::Draw()
{
	m_player->Draw();
}