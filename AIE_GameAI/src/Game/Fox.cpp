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
	m_seekBehaviour = new SeekBehaviour();
	m_seekBehaviour->SetTargetRadius(m_seekRadius);

	// TODO 1: create followPathBehaviour
	// follow path
	m_followPathBehaviour = new FollowPathBehaviour();
	m_followPathBehaviour->SetTargetRadius(10.0f);

	// TODO 2: set a hardcoded path

	// get node at closest position to

	// get fox and rabbit to follow path then merge dikstra with follow path

	// auto path = m_world->m_graph->FindPath(IGraph::SearchType::DIJKSTRA, m_world->m_graph->GetNodes().front(), [](auto node) {
	// 	return node->data == Vector2{ 64, 64 };
	// 	});
	
	SetBehaviour(m_wanderBehaviour);

	SetMaxSpeed(95);
}

Fox::~Fox()
{
	SetBehaviour(nullptr);

	delete m_wanderBehaviour;
}

void Fox::Update(float dt)
{
	// auto m_world->IsRabbitNearby();

	Vector2 rabbit = m_world->IsRabbitNearby(this, m_seekRadius);

	if (rabbit.x != 0 && rabbit.y != 0)
	{
		SetBehaviour(m_seekBehaviour);
		m_seekBehaviour->SetTarget(rabbit);
		m_seekBehaviour->OnArrive([this]()
			{
				SetBehaviour(m_wanderBehaviour);
			});
	}

	// SetBehaviour(m_followPathBehaviour);
	// m_followPathBehaviour->SetGraph(world->m_graph);
	// m_followPathBehaviour->OnArrive([this]()
	// 	{
	// 		m_followPathBehaviour->NextNode();
	// 	});

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