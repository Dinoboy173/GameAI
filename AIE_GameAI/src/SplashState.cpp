#include "SplashState.h"
#include "raylib.h"
#include "Application.h"
#include "GameStateManager.h"
#include <iostream>

SplashState::SplashState(Application *app) : m_app(app)
{

}

SplashState::~SplashState()
{

}

void SplashState::Load()
{
	std::cout << "Loading Splash\n";
}

void SplashState::Unload()
{
	std::cout << "Unloading Splash\n";
}

void SplashState::Update(float dt)
{
	m_timer += dt;
	if (m_timer > 1.0f)
	{
		m_app->GetGameStateManager()->SetState("Splash", nullptr);
		m_app->GetGameStateManager()->PopState();
		m_app->GetGameStateManager()->PushState("Menu");
	}
}

void SplashState::Draw()
{
	DrawText("Splash", 10, 10, 20, LIGHTGRAY);
}