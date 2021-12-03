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
	m_wanderBehaviour->SetTargetRadius(200.0f);

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
	//auto desiredBehaviour = CalculateDesiredBehaviour(world);

	if (GetPosition().x < 0 || GetPosition().y < 0)
		SetPosition({ 48, 48 });

	if (GetPosition().x > 1024 || GetPosition().y > 1024)
		SetPosition({ 976, 976 });

	Vector2 fox = m_world->IsFoxNearby(this, m_fleeRadius);
	Vector2 rabbit = m_world->IsRabbitNearby(this, m_mateRadius);

	float distToFox = Vector2Distance(GetPosition(), fox);
	float distToRabbit = Vector2Distance(GetPosition(), rabbit);

	// flee behaviour
	if (fox.x != 0 && fox.y != 0)
	{
		SetIsChangeBehaviour(true);
		SetBehaviour(m_fleeBehaviour);
		m_fleeBehaviour->SetTarget(fox);
		m_fleeBehaviour->OnExit([this]()
			{
				SetIsChangeBehaviour(true);
				SetBehaviour(m_wanderBehaviour);
			});
	}
	
	// follow path behaviour
	if (m_doFollowPath)
	{
		SetIsChangeBehaviour(true);
		SetBehaviour(m_followPathBehaviour);
		m_followPathBehaviour->SetPath(m_nodes);
		m_followPathBehaviour->SetTarget(m_nodes.front()->data);
		m_followPathBehaviour->OnArrive([this]()
			{
				if (m_followPathBehaviour->GetTarget().x == m_nodes.back()->data.x &&
					m_followPathBehaviour->GetTarget().y == m_nodes.back()->data.y)
				{
					SetIsChangeBehaviour(true);
					m_followPathBehaviour->m_hasStart = false;
					SetBehaviour(GetPreviousBehaviour());
				}
				else
				{
					m_followPathBehaviour->NextNode(this);
				}

				DoFollowPath(false);
			});

		DoFollowPath(false);
	}

	// have behaviours send info to follow path

	GameObject::Update(dt);

	// if (distToFox < 16)
	// {
	// 	m_followPathBehaviour->m_hasStart = false;
	// 	m_world->RemoveRabbitFromList(this);
	// }
		

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