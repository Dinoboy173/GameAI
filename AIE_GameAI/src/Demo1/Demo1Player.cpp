#include "./Demo1/Demo1Player.h"
#include "./Demo1/Demo1KeyboardBehaviour.h"
#include "./Demo1/Demo1SeekBehaviour.h"
#include "./Demo1/Demo1FleeBehaviour.h"
#include "./Demo1/Demo1WanderBehaviour.h"
#include "Demo1/Demo1FollowPathBehaviour.h"

Demo1Player::Demo1Player()
{
	// Keyboard
	m_kbBehaviour = new Demo1KeyboardBehaviour();
	SetBehaviour(m_kbBehaviour);

	// Seek
	m_seekBehaviour = new Demo1SeekBehaviour();
	m_seekBehaviour->SetTargetRadius(25.0f);
	m_seekBehaviour->OnArrive([this]()
	{
		SetBehaviour(m_kbBehaviour);
	});

	// Flee
	m_fleeBehaviour = new Demo1FleeBehaviour();
	m_fleeBehaviour->SetTargetRadius(75.0f);
	m_fleeBehaviour->OnExit([this]()
	{
		SetBehaviour(m_kbBehaviour);
	});

	// Wander
	m_wanderBehaviour = new Demo1WanderBehaviour();
	m_wanderBehaviour->SetTargetRadius(50.0f);

	// Follow Path
	m_followPathBehaviour = new Demo1FollowPathBehaviour();
	m_followPathBehaviour->SetTargetRadius(10.0f);
	m_followPathBehaviour->OnArrive([this]()
		{
			m_followPathBehaviour->NextNode();
		});
}

Demo1Player::~Demo1Player()
{
	SetBehaviour(nullptr);

	delete m_wanderBehaviour;
	delete m_fleeBehaviour;
	delete m_seekBehaviour;
	delete m_kbBehaviour;
	delete m_followPathBehaviour;
}

void Demo1Player::Update(float deltaTime)
{
	if (IsMouseButtonPressed(0))
	{
		m_seekBehaviour->SetTarget(GetMousePosition());
		SetBehaviour(m_seekBehaviour);
	}

	if (IsMouseButtonPressed(1))
	{
		m_fleeBehaviour->SetTarget(GetMousePosition());
		SetBehaviour(m_fleeBehaviour);
	}

	if (IsKeyPressed(KeyboardKey(KEY_ONE)))
	{
		SetBehaviour(m_kbBehaviour);
	}

	if (IsKeyPressed(KeyboardKey(KEY_TWO)))
	{
		SetBehaviour(m_wanderBehaviour);
	}

	if (IsKeyPressed(KeyboardKey(KEY_THREE)))
	{
		SetBehaviour(m_followPathBehaviour);
	}

	GameObject::Update(deltaTime);
}

void Demo1Player::Draw()
{
	GameObject::Draw();
}