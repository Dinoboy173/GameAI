#pragma once

class Demo1GameObject;

class Demo1Behaviour
{
public:

	Demo1Behaviour() {}
	virtual ~Demo1Behaviour() {}

	virtual void Update(Demo1GameObject* obj, float deltaTime) {}
	virtual void Draw(Demo1GameObject* obj) {}

protected:
private:
};