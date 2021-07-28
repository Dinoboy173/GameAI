#include "./Menu/Application.h"
#include "./Menu/GameStateManager.h"
#include "./Menu/SplashState.h"
#include "./Menu/MenuState.h"
#include "./Game/PlayState.h"
#include "./Game/PauseState.h"
#include "./Demo1/Demo1.h"
#include "./Demo2/Demo2.h"
#include "./Game/AssetManager.h"

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
	AssetManager::CreateSingleton();
	AssetManager::GetInstance()->LoadAssets();

	m_gameStateManager = new GameStateManager();
	m_gameStateManager->SetState("Splash", new SplashState(this));
	m_gameStateManager->SetState("Menu", new MenuState(this));
	m_gameStateManager->SetState("Play", new PlayState(this));
	m_gameStateManager->SetState("Pause", new PauseState(this));
	m_gameStateManager->SetState("Demo1", new Demo1(this));
	m_gameStateManager->SetState("Demo2", new Demo2(this));

	m_gameStateManager->PushState("Splash");
}

void Application::Unload()
{
	AssetManager::GetInstance()->UnloadAssets();
	AssetManager::DestroySingleton();

	delete m_gameStateManager;
}

void Application::Update(float deltaTime)
{
	m_gameStateManager->Update(deltaTime);
}

void Application::Draw()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);

	m_gameStateManager->Draw();

	EndDrawing();
}

GameStateManager* Application::GetGameStateManager()
{
	return m_gameStateManager;
}