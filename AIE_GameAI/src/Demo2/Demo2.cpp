#include "./Demo2/Demo2.h"
#include "./Menu/Application.h"
#include "./Menu/GameStateManager.h"
#include "./Demo2/Demo2Player.h"
#include "./Demo2/Demo2KeyboardBehaviour.h"
#include "./Demo2/Demo2GameObject.h"
#include "raylib.h"

#include <iostream>

Demo2::Demo2(Application* app) : m_app(app)
{

}

Demo2::~Demo2()
{

}

void Demo2::Load()
{
	std::cout << "Loading Demo2\n";
}

void Demo2::Unload()
{
	std::cout << "Unloading Demo2\n";
}

void Demo2::Update(float dt)
{
	
}

void Demo2::Draw()
{
	DrawText("Demo2", 10, 10, 20, LIGHTGRAY);

	
}