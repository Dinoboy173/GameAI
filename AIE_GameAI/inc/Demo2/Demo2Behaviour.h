#pragma once

class Demo2GameObject;

class Demo2Behaviour
{
public:

	Demo2Behaviour() {}
	virtual ~Demo2Behaviour() {}

	virtual void Update(Demo2GameObject* obj, float deltaTime) {}
	virtual void Draw(Demo2GameObject* obj) {}

protected:
private:
};