#include "./Game/Rabbit.h"
#include "./Game/Behaviour/WanderBehaviour.h"
#include "./Game/AssetManager.h"

Rabbit::Rabbit()
{
	// need list of rabbits
	// spawn rabbits using BuildWorld maybe

	m_wanderBehaviour = new WanderBehaviour();
	m_wanderBehaviour->SetTargetRadius(30.0f);
}

Rabbit::~Rabbit()
{
	SetBehaviour(nullptr);

	delete m_wanderBehaviour;
}

void Rabbit::Update(float dt)
{
	SetBehaviour(m_wanderBehaviour);

	GameObject::Update(dt);
}

void Rabbit::Draw()
{
	GameObject::Draw(ASSETS->imgRabbit, ASSETS->rabbit, m_position.x, m_position.y);
}