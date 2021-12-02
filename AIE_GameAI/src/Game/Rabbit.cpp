#include "./Game/Rabbit.h"
#include "./Game/Behaviour/WanderBehaviour.h"
#include "./Game/Behaviour/FleeBehaviour.h"
#include "./Game/Behaviour/FollowPathBehaviour.h"
#include "./Game/AssetManager.h"
#include "./Game/BuildWord.h"

Rabbit::Rabbit(BuildWorld* world)
{
	m_world = world;

	// wander
	m_wanderBehaviour = new WanderBehaviour(world);
	m_wanderBehaviour->SetTargetRadius(100.0f);

	// flee
	m_fleeBehaviour = new FleeBehaviour(world);
	m_fleeBehaviour->SetTargetRadius(m_fleeRadius);

	// follow path
	m_followPathBehaviour = new FollowPathBehaviour();
	m_followPathBehaviour->SetTargetRadius(10.0f);

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

void Rabbit::Update(float dt)
{
	GameObject::Update(dt);

	//auto desiredBehaviour = CalculateDesiredBehaviour(world);

	Vector2 fox = m_world->IsFoxNearby(this, m_fleeRadius);
	Vector2 rabbit = m_world->IsRabbitNearby(this, m_mateRadius);

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

	if (m_doFollowPath) // do same for fox
	{
		SetBehaviour(m_followPathBehaviour);
		m_followPathBehaviour->SetPath(m_nodes);
		m_followPathBehaviour->SetTarget(m_nodes[0]->data);
		m_followPathBehaviour->OnArrive([this]()
			{
				if (m_followPathBehaviour->GetTarget().x != m_nodes.back()->data.x &&
					m_followPathBehaviour->GetTarget().y != m_nodes.back()->data.y)
				{
					m_followPathBehaviour->NextNode();
				}
				else
				{
					SetBehaviour(m_wanderBehaviour);
				}
			});

		DoFollowPath(false);
	}

	// have behaviours send info to follow path

	if (distToFox < 16)
		m_world->RemoveRabbitFromList(this);

	//if (distToRabbit < m_mateRadius)
	//	world->AddRabbit(GetPosition());
}

void Rabbit::Draw()
{
	bool behaviourDebug = false;

	// draw velocity line

	if (IsKeyDown(KeyboardKey(KEY_F3)))
		GetBehaviour()->Draw(this);

	GameObject::Draw(ASSETS->imgRabbit, ASSETS->rabbit, m_position.x, m_position.y);
}

void Rabbit::SetBehaviourFollow()
{
	
}