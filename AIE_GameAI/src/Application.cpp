#include "Application.h"
#include "GameObject.h"
#include "Player.h"
#include "KeyboardBehaviour.h"

Application::Application(int windowWidth, int windowHeight, const char* windowTitle) :
	m_windowWidth(windowWidth),
	m_windowHeight(windowHeight),
	m_windowTitle(windowTitle)
{

}

Application::~Application()
{

}

void Application::Run()
{
	InitWindow(m_windowWidth, m_windowHeight, m_windowTitle);
	SetTargetFPS(60);

	Load();

	while (!WindowShouldClose())
	{
		float deltaTime = GetFrameTime();
		Update(deltaTime);

		Draw();
	}

	Unload();

	CloseWindow();
}

void Application::Load()
{
	m_player = new Player();
	m_player->SetPosition({ m_windowWidth / 2.0f, m_windowHeight / 2.0f });
	m_player->SetFriction(1.0f);
}

void Application::Unload()
{
	delete m_player;
	m_player = nullptr;
}

void Application::Update(float deltaTime)
{
	m_player->Update(deltaTime);
}

void Application::Draw()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);

	m_player->Draw();

	EndDrawing();
}