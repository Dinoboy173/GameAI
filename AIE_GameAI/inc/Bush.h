#pragma once

#include "GameObject.h"

class Bush : public GameObject
{
public:

	Bush();
	virtual ~Bush();

	virtual void Update(float deltaTime);
	virtual void Draw();

protected:
private:
};