#include "./Game/Rabbit.h"
#include "./Game/Behaviour/WanderBehaviour.h"
#include "./Game/Behaviour//FleeBehaviour.h"
#include "./Game/AssetManager.h"

Rabbit::Rabbit()
{
	m_wanderBehaviour = new WanderBehaviour();
	m_wanderBehaviour->SetTargetRadius(100.0f);

	m_fleeBehaviour = new FleeBehaviour();
	m_fleeBehaviour->SetTargetRadius(110);

	SetBehaviour(m_wanderBehaviour);
}

Rabbit::~Rabbit()
{
	SetBehaviour(nullptr);

	delete m_wanderBehaviour;
}

void Rabbit::Update(float dt, BuildWorld* world)
{
	GameObject::Update(dt);

	Vector2 fox = world->IsFoxNearby(this, m_fleeRadius);

	if (fox.x != 0 && fox.y != 0)
	{
		SetBehaviour(m_fleeBehaviour);
		m_fleeBehaviour->SetTarget(fox);
	}

	if (isDead)
	{


		Rabbit::~Rabbit();
	}
}

void Rabbit::Draw()
{
	m_wanderBehaviour->Draw();
	GameObject::Draw(ASSETS->imgRabbit, ASSETS->rabbit, m_position.x, m_position.y);
}