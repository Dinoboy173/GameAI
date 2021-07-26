#pragma once

class IGameState
{
public:

	IGameState() { }
	virtual ~IGameState() { }

	virtual void Load() { }
	virtual void Unload() { }

	virtual void Update(float dt) { }
	virtual void Draw() { }

protected:
private:
};