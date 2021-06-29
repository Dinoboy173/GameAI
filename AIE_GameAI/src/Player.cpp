#include "Player.h"
#include "KeyboardBehaviour.h"
#include "SeekBehaviour.h"
#include "FleeBehaviour.h"
#include "WanderBehaviour.h"

Player::Player()
{
	// Keyboard
	m_kbBehaviour = new KeyboardBehaviour();
	SetBehaviour(m_kbBehaviour);

	// Seek
	m_seekBehaviour = new SeekBehaviour();
	m_seekBehaviour->SetTargetRadius(25.0f);
	m_seekBehaviour->OnArrive([this]()
	{
		SetBehaviour(m_kbBehaviour);
	});

	// Flee
	m_fleeBehaviour = new FleeBehaviour();
	m_fleeBehaviour->SetTargetRadius(75.0f);
	m_fleeBehaviour->OnExit([this]()
	{
		SetBehaviour(m_kbBehaviour);
	});

	// Wander
	m_wanderBehaviour = new WanderBehaviour();
	m_wanderBehaviour->SetTargetRadius(50.0f);
}

Player::~Player()
{
	SetBehaviour(nullptr);

	delete m_wanderBehaviour;
	delete m_fleeBehaviour;
	delete m_seekBehaviour;
	delete m_kbBehaviour;
}

void Player::Update(float deltaTime)
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

	GameObject::Update(deltaTime);
}

void Player::Draw()
{
	GameObject::Draw();
}