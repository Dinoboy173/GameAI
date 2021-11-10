#include "raylib.h"
#include "AssetManager.h"
#include "./Game/Rabbit.h"
#include "./Game/Fox.h"
#include "./Game/Graph2D.h"

class Graph2D;
class Rabbit;
class Fox;

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

	void LoadGraph();

	void Update(float dt);
	void Draw();

	void DrawWorld();
	void DrawGraph();

	unsigned int GetImagePixel(Image img, int xPos, int yPos);

protected:

	Graph2D* m_graph = nullptr;

private:

	int m_numRows = ASSETS->imgGameMapInfo.height;
	int m_numCols = ASSETS->imgGameMapInfo.width;

	int m_tileSize = 32;
	
	Rabbit* m_rabbit;
	Fox* m_fox;

	std::vector<Rabbit*> m_rabbitList;
	std::vector<Fox*> m_foxList;

};