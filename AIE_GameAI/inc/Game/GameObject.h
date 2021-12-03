#pragma once

#include "raymath.h"
#include "./Game/Graph.h"
#include <functional>
#include <list>
#include <vector>

class Behaviour;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Update(float deltaTime);
	virtual void Draw();

	virtual void Draw(Texture2D& img, Rectangle srcRec, float xPos, float yPos);

	void ApplyForce(const Vector2& force);

	// Getters
	const Vector2& GetPosition() const;
	const Vector2& GetVelocity() const;
	const Vector2& GetAccelertion() const;
	const float& GetFriction() const;

	const float& GetMaxSpeed() const;
	const float& GetMaxForce() const;
	
	Behaviour* GetBehaviour();
	Behaviour* GetPreviousBehaviour();

	Graph<Vector2, float>::Node* GetStartNode();

	std::list<Graph<Vector2, float>::Node*> GetNodes();
	bool IsFollowPath();

	// Setters
	void SetPosition(const Vector2& pos);
	void SetVelocity(const Vector2& vel);
	void SetFriction(const float& fric);

	void SetMaxSpeed(const float& speed);
	void SetMaxForce(const float& force);

	void SetBehaviour(Behaviour* behaviour);
	void SetPreviousBehaviour(Behaviour* behaviour);

	void SetStartNode(Graph<Vector2, float>::Node* startNode);

	void SetNodes(std::list<Graph<Vector2, float>::Node*> nodes);
	void DoFollowPath(bool doFollowPath);

protected:

	Vector2 m_position = { 0.0f, 0.0f };
	Vector2 m_velocity = { 0.0f, 0.0f };
	Vector2 m_acceleration = { 0.0f, 0.0f };
	float m_friction = 2.0f;
	float m_maxSpeed = 100.0f;
	float m_maxForce = 200.0f;

	Graph<Vector2, float>::Node* m_startNode;

	std::list<Graph<Vector2, float>::Node*> m_nodes;
	bool m_doFollowPath = false;

	Behaviour* m_behaviour = nullptr;
	Behaviour* m_previousBehviour = nullptr;

private:
};