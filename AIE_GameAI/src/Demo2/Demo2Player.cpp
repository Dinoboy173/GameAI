#include "./Demo2/Demo2Player.h"
#include "./Demo2/Demo2KeyboardBehaviour.h"
#include "./Demo2/Demo2SeekBehaviour.h"

Player::Player()
{
	// Keyboard
	m_kbBehaviour = new Demo2KeyboardBehaviour();
	SetBehaviour(m_kbBehaviour);

	// Seek
	m_seekBehaviour = new Demo2SeekBehaviour();
	m_seekBehaviour->SetTargetRadius(25.0f);
	m_seekBehaviour->OnArrive([this]()
	{
		SetBehaviour(m_kbBehaviour);
	});
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
	}

	Demo2GameObject::Update(deltaTime);
}

void Player::Draw()
{
	Demo2GameObject::Draw();
}