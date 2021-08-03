#include "./Game/Fox.h"
#include "./Game/Behaviour/WanderBehaviour.h"
#include "./Game/AssetManager.h"

Fox::Fox()
{
	// need list of foxs
	// spawn foxs using BuildWorld maybe

	m_wanderBehaviour = new WanderBehaviour();
	m_wanderBehaviour->SetTargetRadius(50.0f);
}

Fox::~Fox()
{
	SetBehaviour(nullptr);

	delete m_wanderBehaviour;
}

void Fox::Update(float dt)
{
	SetBehaviour(m_wanderBehaviour);

	GameObject::Update(dt);
}

void Fox::Draw()
{
	GameObject::Draw(ASSETS->imgFox, ASSETS->fox, m_position.x, m_position.y);
}