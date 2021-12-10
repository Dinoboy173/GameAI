#include "./Game/Fox.h"
#include "./Game/Behaviour/WanderBehaviour.h"
#include "./Game/Behaviour/SeekBehaviour.h"
#include "./Game/Behaviour/FollowPathBehaviour.h"
#include "./Game/AssetManager.h"
#include "./Game/Rabbit.h"
#include "./Game/BuildWord.h"
#include <iostream>

Fox::Fox(BuildWorld* world)
{
	m_world = world;

	// wander
	m_wanderBehaviour = new WanderBehaviour(world);
	m_wanderBehaviour->SetTargetRadius(200.0f);

	// seek
	m_seekBehaviour = new SeekBehaviour(world);
	m_seekBehaviour->SetTargetRadius(m_seekRadius);

	// follow path
	m_followPathBehaviour = new FollowPathBehaviour();
	m_followPathBehaviour->SetTargetRadius(10.0f);
	
	SetBehaviour(m_wanderBehaviour);

	SetMaxSpeed(95);
}

Fox::~Fox()
{
	SetBehaviour(nullptr);

	delete m_wanderBehaviour;
	delete m_seekBehaviour;
	delete m_followPathBehaviour;
}

void Fox::Update(float dt)
{
	if (GetPosition().x < 0 || GetPosition().y < 0)
		SetPosition({ 48, 48 });

	if (GetPosition().x > 1024 || GetPosition().y > 1024)
		SetPosition({ 976, 976 });

	Vector2 rabbit = m_world->IsRabbitNearby(this, m_seekRadius);
	float distToRabbit = Vector2Length(Vector2Subtract(rabbit, GetPosition()));
	
	if (distToRabbit < 16 && !m_killedEntity)
		m_killedEntity = true;

	// seek behaviour
	if ((rabbit.x != 0 && rabbit.y != 0) && GetPreviousBehaviour() != m_seekBehaviour)
	{
		m_killedEntity = false;
		SetIsChangeBehaviour(true);
		SetBehaviour(m_seekBehaviour);
		m_seekBehaviour->SetTarget(rabbit);
		m_seekBehaviour->OnArrive([this]()
			{
				m_doFollowPath = false;
				SetIsChangeBehaviour(true);
				SetBehaviour(m_wanderBehaviour);
			});
	}

	if (m_doFollowPath)
	{
		if (m_nodes.size() != 0)
		{
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
				});

			DoFollowPath(false);
		}
	}
	
	// auto desiredBehaviour = CalculateDesiredBehaviour();
	// if (desiredBehaviour != GetBehaviour())
	// {
	// 	SetBehaviour(desiredBehaviour);
	// }

	GameObject::Update(dt);
}

void Fox::Draw()
{
	bool behaviourDebug = false;

	if (IsKeyDown(KeyboardKey(KEY_F3)))
		GetBehaviour()->Draw(this);

	GameObject::Draw(ASSETS->imgFox, ASSETS->fox, m_position.x, m_position.y);

	GameObject::Draw();
}

Behaviour* Fox::CalculateDesiredBehaviour(BuildWorld* world)
{
	// auto behaviour;

	// TODO 4: define locif for switching between follow pathh and wander
	// if (isHungry)
	// {
		// calculate path to food - use the graph pathfinder to calculate that path.
		// m_followPathBehaviour->SetPath(path that was calculated on above line)
		// return m_followPathBehaviour
	// }

	// TODO 3: return the followPathBehaviour

	return m_wanderBehaviour;
}