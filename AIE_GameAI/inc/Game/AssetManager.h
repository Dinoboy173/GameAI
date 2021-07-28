#pragma once

#include "raylib.h"

#define ASSETS AssetManager::GetInstance()

class AssetManager
{
public:
	static AssetManager* GetInstance();
	static void CreateSingleton();
	static void DestroySingleton();

	void LoadAssets();
	void UnloadAssets();

	// Images
	Texture2D imgGrass;
	Texture2D imgWater;
	Texture2D imgTree;
	Texture2D imgHole;
	Texture2D imgBush;
	Texture2D imgFox;
	Texture2D imgRabbit;
	Texture2D imgGameMapInfo;

	Image imgGameMapInfoRaw;

	Rectangle bushEmpty = { 0.0f, 0.0f, 32.0f, 32.0f };
	Rectangle bushFull = { 32.0f, 0.0f, 32.0f, 32.0f };
	Rectangle bush = { 32.0f, 0.0f, 32.0f, 32.0f };
	
	Rectangle foxSide = { 0.0f, 0.0f, 32.0f, 32.0f };
	Rectangle foxFront = { 32.0f, 0.0f, 32.0f, 32.0f };
	Rectangle foxBack = { 64.0f, 0.0f, 32.0f, 32.0f };
	Rectangle fox = { 0.0f, 0.0f, 32.0f, 32.0f };

	Rectangle rabbitSide = { 0.0f, 0.0f, 32.0f, 32.0f };
	Rectangle rabbitFront = { 32.0f, 0.0f, 32.0f, 32.0f };
	Rectangle rabbitBack = { 64.0f, 0.0f, 32.0f, 32.0f };
	Rectangle rabbit = { 0.0f, 0.0f, 32.0f, 32.0f };

protected:
private:

	static AssetManager* ms_singleton;

	AssetManager();
	~AssetManager();

};