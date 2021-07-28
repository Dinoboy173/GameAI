#include "./Game/AssetManager.h"

// Singleton Method
// ----------------------------------------------------------------
AssetManager* AssetManager::ms_singleton = nullptr;

AssetManager* AssetManager::GetInstance()
{
	return ms_singleton;
}
void AssetManager::CreateSingleton()
{
	ms_singleton = new AssetManager();
}
void AssetManager::DestroySingleton()
{
	delete ms_singleton;
	ms_singleton = nullptr;
}
// ----------------------------------------------------------------

AssetManager::AssetManager()
{

}

AssetManager::~AssetManager()
{

}

void AssetManager::LoadAssets()
{
	imgGrass = LoadTexture("./assets/grass.png");
	imgWater = LoadTexture("./assets/water.png");
	imgTree = LoadTexture("./assets/tree.png");
	imgHole = LoadTexture("./assets/hole.png");
	imgBush = LoadTexture("./assets/bush.png");
	imgFox = LoadTexture("./assets/fox.png");
	imgRabbit = LoadTexture("./assets/rabbit.png");
	imgGameMapInfo = LoadTexture("./assets/colourMap.png");

	imgGameMapInfoRaw = LoadImage("./assets/colourMap.png");
}

void AssetManager::UnloadAssets()
{
	UnloadTexture(imgGrass);
	UnloadTexture(imgWater);
	UnloadTexture(imgTree);
	UnloadTexture(imgHole);
	UnloadTexture(imgBush);
	UnloadTexture(imgFox);
	UnloadTexture(imgRabbit);
	UnloadTexture(imgGameMapInfo);

	UnloadImage(imgGameMapInfoRaw);
}