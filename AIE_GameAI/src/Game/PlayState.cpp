#include "./Game/PlayState.h"
#include "./Menu/Application.h"
#include "./Menu/GameStateManager.h"
#include "./Game/AssetManager.h"
#include "./Game/BuildWord.h"
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

	m_world = new BuildWorld();
	
	m_world->Load();
}

void PlayState::Unload()
{
	std::cout << "Unloading Play\n";

	m_world->Unload();

	delete m_world;
	m_world = nullptr;
}

void PlayState::Update(float dt)
{
	m_world->Update(dt);

	if (IsKeyPressed(KeyboardKey(KEY_P)))
	{
		m_app->GetGameStateManager()->PushState("Pause");
	}
}

void PlayState::Draw()
{
	m_world->Draw();
}