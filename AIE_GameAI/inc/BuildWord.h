#pragma once

#include "raylib.h"
#include "AssetManager.h"
#include "Bush.h"
#include <vector>
#include <map>

struct Pos
{
	float x;
	float y;
};

class BuildWorld
{
public:

	BuildWorld();
	~BuildWorld();

	void Load();
	void Unload();

	void Update(float dt);
	void Draw();

	unsigned int GetImagePixel(Image img, int xPos, int yPos);

protected:
private:

	

	Bush m_bush;

};