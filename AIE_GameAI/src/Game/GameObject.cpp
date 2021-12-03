#include "./Game/GameObject.h"
#include "./Game/Behaviour/Behaviour.h"
#include "./Game/AssetManager.h"
#include "./Game/Graph.h"
#include <functional>

GameObject::GameObject()
{
	
}

GameObject::~GameObject()
{
	
}

void GameObject::Update(float deltaTime)
{
	if (m_behaviour != nullptr)
		m_behaviour->Update(this, deltaTime);

	ApplyForce(Vector2Scale(Vector2Negate(m_velocity), m_friction));

	m_velocity = Vector2Add(m_velocity, Vector2Scale(m_acceleration, deltaTime));
	m_position = Vector2Add(m_position, Vector2Scale(m_velocity, deltaTime));
	m_acceleration = { 0, 0 };
}

void GameObject::Draw()
{
	if (m_behaviour != nullptr)
		m_behaviour->Draw(this);

	Vector2 heading = Vector2Add(m_position, m_velocity);

	DrawCircle(m_position.x, m_position.y, 8, GRAY);
	DrawLine(m_position.x, m_position.y, heading.x, heading.y, BLACK);
}

void GameObject::Draw(Texture2D& img, Rectangle srcRec, float xPos, float yPos)
{
	Rectangle destRec = { xPos, yPos, 32.0f, 32.0f };
	Vector2 origin = { 16.0f, 16.0f };

	DrawTexturePro(img, srcRec, destRec, origin, 0.0f, WHITE);
}

void GameObject::ApplyForce(const Vector2& force)
{
	m_acceleration = Vector2Add(m_acceleration, force);
}

// Getters
const Vector2& GameObject::GetPosition() const
{
	return m_position;
}
const Vector2& GameObject::GetVelocity() const
{
	return m_velocity;
}
const Vector2& GameObject::GetAccelertion() const
{
	return m_acceleration;
}
const float& GameObject::GetFriction() const
{
	return m_friction;
}
const float& GameObject::GetMaxSpeed() const
{
	return m_maxSpeed;
}
const float& GameObject::GetMaxForce() const
{
	return m_maxForce;
}
Behaviour* GameObject::GetBehaviour()
{
	return m_behaviour;
}
Behaviour* GameObject::GetPreviousBehaviour()
{
	return m_previousBehviour;
}
Graph<Vector2, float>::Node* GameObject::GetStartNode()
{
	return m_startNode;
}
std::list<Graph<Vector2, float>::Node*> GameObject::GetNodes()
{
	return m_nodes;
}
bool GameObject::IsFollowPath()
{
	return m_doFollowPath;
}
bool GameObject::GetIsChangeBehaviour()
{
	return m_isChangingBehaviour;
}

// Setters
void GameObject::SetPosition(const Vector2& pos)
{
	m_position = pos;
}
void GameObject::SetVelocity(const Vector2& vel)
{
	m_velocity = vel;
}
void GameObject::SetFriction(const float& fric)
{
	m_friction = fric;
}
void GameObject::SetMaxSpeed(const float& speed)
{
	m_maxSpeed = speed;
}
void GameObject::SetMaxForce(const float& force)
{
	m_maxForce = force;
}
void GameObject::SetBehaviour(Behaviour* behaviour)
{
	m_previousBehviour = m_behaviour;
	m_behaviour = behaviour;
}
void GameObject::SetPreviousBehaviour(Behaviour* behaviour)
{
	m_previousBehviour = behaviour;
}
void GameObject::SetStartNode(Graph<Vector2, float>::Node* startNode)
{
	m_startNode = startNode;
}
void GameObject::SetNodes(std::list<Graph<Vector2, float>::Node*> nodes)
{
	m_nodes.clear();
	m_nodes = nodes;
}
void GameObject::DoFollowPath(bool doFollowPath)
{
	m_doFollowPath = doFollowPath;
}
void GameObject::SetIsChangeBehaviour(bool isChangingBehaviour)
{
	m_isChangingBehaviour = isChangingBehaviour;
}