#include "./Demo1/Demo1.h"
#include "./Menu/Application.h"
#include "./Menu/GameStateManager.h"
#include "./Demo1/Demo1Player.h"
#include "./Demo1/Demo1KeyboardBehaviour.h"
#include "./Game/GameObject.h"
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

	m_player = new Player();
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
	m_player->Update(dt);
}

void Demo1::Draw()
{
	DrawText("Demo1", 10, 10, 20, LIGHTGRAY);

	m_player->Draw();
}