#pragma once

#include "raylib.h"
#include "AssetManager.h"
enum COLOR
{
	// a b g r

	C_BLACK = 0xFF000000,
	C_BLUE = 0xFFFF0000,
	C_GREEN = 0xFF00FF00,
	C_RED = 0xFF0000FF,
	C_CYAN = 0xFFFFFF00,
	C_MAGENTA = 0xFFFF00FF,
	C_YELLOW = 0xFF00FFFF
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
};