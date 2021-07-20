#include "PlayState.h"
#include "Application.h"
#include "GameStateManager.h"
#include "Player.h"
#include "KeyboardBehaviour.h"
#include "GameObject.h"
#include "AssetManager.h"
#include "BuildWord.h"
#include <Graph.h>
#include <iostream>

PlayState::PlayState(Application* app) : m_app(app)
{

}

PlayState::~PlayState()
{

}

void PlayState::Load()
{
	std::cout << "Loading Play\n";

	m_world->Load();

	// m_player = new Player();
	// m_player->SetPosition({ 500, 500 });
	// m_player->SetFriction(1.0f);
}

void PlayState::Unload()
{
	std::cout << "Unloading Play\n";

	m_world->Unload();

	// delete m_player;
	// m_player = nullptr;
}

void PlayState::Update(float dt)
{
	// m_player->Update(dt);
	m_world->Update(dt);

	if (IsKeyPressed(KeyboardKey(KEY_P)))
	{
		m_app->GetGameStateManager()->PushState("Pause");
	}
}

void PlayState::Draw()
{
	m_world->Draw();

	// m_player->Draw();
}