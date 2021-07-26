#pragma once

#include "GameObject.h"



class Rabbit : public GameObject
{
public:

	Rabbit();
	virtual ~Rabbit();

	virtual void Update(float dt);
	virtual void Draw();

protected:

	

private:
};