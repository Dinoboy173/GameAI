#include "./Game/Fox.h"
#include "./Game/Behaviour/WanderBehaviour.h"
#include "./Game/Behaviour/SeekBehaviour.h"
#include "./Game/AssetManager.h"
#include "./Game/Rabbit.h"

Fox::Fox()
{
	// wander
	m_wanderBehaviour = new WanderBehaviour();
	m_wanderBehaviour->SetTargetRadius(50.0f);

	SetBehaviour(m_wanderBehaviour);

	// seek
	m_seekBehaviour = new SeekBehaviour();
	m_seekBehaviour->SetTargetRadius(50.0f);
	m_seekBehaviour->OnArrive([this]()
	{
		SetBehaviour(m_wanderBehaviour);
	});
}

Fox::~Fox()
{
	SetBehaviour(nullptr);

	delete m_wanderBehaviour;
}

void Fox::Update(float dt)
{


	GameObject::Update(dt);
}

void Fox::Draw()
{
	GameObject::Draw(ASSETS->imgFox, ASSETS->fox, m_position.x, m_position.y);
}