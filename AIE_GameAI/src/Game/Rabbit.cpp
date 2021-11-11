#include "./Game/Rabbit.h"
#include "./Game/Behaviour/WanderBehaviour.h"
#include "./Game/Behaviour//FleeBehaviour.h"
#include "./Game/AssetManager.h"

Rabbit::Rabbit()
{
	m_wanderBehaviour = new WanderBehaviour();
	m_wanderBehaviour->SetTargetRadius(100.0f);

	m_fleeBehaviour = new FleeBehaviour();
	m_fleeBehaviour->SetTargetRadius(150);

	SetBehaviour(m_wanderBehaviour);

	SetMaxSpeed(120);
	SetFriction(1.8f);
}

Rabbit::~Rabbit()
{
	SetBehaviour(nullptr);

	delete m_wanderBehaviour;
	delete m_fleeBehaviour;
}

void Rabbit::Update(float dt, BuildWorld* world)
{
	GameObject::Update(dt);

	Vector2 fox = world->IsFoxNearby(this, m_fleeRadius);
	float distToFox = Vector2Distance(GetPosition(), fox);

	if (fox.x != 0 && fox.y != 0)
	{
		SetBehaviour(m_fleeBehaviour);
		m_fleeBehaviour->SetTarget(fox);
		m_fleeBehaviour->OnExit([this]()
			{
				SetBehaviour(m_wanderBehaviour);
			});
	}

	if (distToFox < 32)
	{
		//world->RemoveRabbitFromList(this);
	}
}

void Rabbit::Draw()
{
	GetBehaviour()->Draw(this);
	GameObject::Draw(ASSETS->imgRabbit, ASSETS->rabbit, m_position.x, m_position.y);
}