#include "./Game/Rabbit.h"
#include "./Game/Behaviour/WanderBehaviour.h"
#include "./Game/Behaviour/FleeBehaviour.h"
#include "./Game/AssetManager.h"

Rabbit::Rabbit()
{
	m_wanderBehaviour = new WanderBehaviour();
	m_wanderBehaviour->SetTargetRadius(100.0f);

	m_fleeBehaviour = new FleeBehaviour();
	m_fleeBehaviour->SetTargetRadius(m_fleeRadius);

	SetBehaviour(m_wanderBehaviour);

	SetMaxSpeed(110);
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

	//auto desiredBehaviour = CalculateDesiredBehaviour(world);

	Vector2 fox = world->IsFoxNearby(this, m_fleeRadius);
	Vector2 rabbit = world->IsRabbitNearby(this, m_mateRadius);

	float distToFox = Vector2Distance(GetPosition(), fox);
	float distToRabbit = Vector2Distance(GetPosition(), rabbit);

	if (fox.x != 0 && fox.y != 0)
	{
		SetBehaviour(m_fleeBehaviour);
		m_fleeBehaviour->SetTarget(fox);
		m_fleeBehaviour->OnExit([this]()
			{
				SetBehaviour(m_wanderBehaviour);
			});
	}

	if (distToFox < 16)
		world->RemoveRabbitFromList(this);

	//if (distToRabbit < m_mateRadius)
	//	world->AddRabbit(GetPosition());
}

void Rabbit::Draw()
{
	bool behaviourDebug = false;

	if (IsKeyDown(KeyboardKey(KEY_F3)))
		GetBehaviour()->Draw(this);

	GameObject::Draw(ASSETS->imgRabbit, ASSETS->rabbit, m_position.x, m_position.y);
}