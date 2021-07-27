
#include "Application.h"
#include "ScrabbleBoard.h"
#include "ScrabbleBoardRenderer.h"

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raygui.h"



Application::Application()
{

}
Application::~Application()
{

}

void Application::Run()
{
	InitWindow(m_windowWidth, m_windowHeight, "Scrabble");

	SetTargetFPS(60);
	Load();

	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		float dt = GetFrameTime();
		Update(dt);
		Draw();
	}

	Unload();
	CloseWindow();

}

void Application::Load()
{
	m_board = new ScrabbleBoard(15, 15);

	unsigned int NO = (int)ScrabbleBoard::EScoreMod::NO;
	unsigned int DL = (int)ScrabbleBoard::EScoreMod::DL;
	unsigned int TL = (int)ScrabbleBoard::EScoreMod::TL;
	unsigned int DW = (int)ScrabbleBoard::EScoreMod::DW;
	unsigned int TW = (int)ScrabbleBoard::EScoreMod::TW;

	unsigned int modifiers[15*15] = {
		TW, NO, NO, DL, NO, NO, NO, TW, NO, NO, NO, NO, DL, NO, TW,
		NO, DW, NO, NO, NO, TL, NO, NO, NO, TL, NO, NO, NO, DW, NO,
		NO, NO, DW, NO, NO, NO, DL, NO, DL, NO, NO, NO, DW, NO, NO,
		DL, NO, NO, DW, NO, NO, NO, DL, NO, NO, NO, DW, NO, NO, DL,
		NO, NO, NO, NO, DW, NO, NO, NO, NO, NO, DW, NO, NO, NO, NO,
		NO, TL, NO, NO, NO, TL, NO, NO, NO, TL, NO, NO, NO, TL, NO,
		NO, NO, DL, NO, NO, NO, DL, NO, DL, NO, NO, NO, DL, NO, NO,
		TW, NO, NO, DL, NO, NO, NO, NO, NO, NO, NO, DL, NO, NO, TW,
		NO, NO, DL, NO, NO, NO, DL, NO, DL, NO, NO, NO, DL, NO, NO,
		NO, TL, NO, NO, NO, TL, NO, NO, NO, TL, NO, NO, NO, TL, NO,
		NO, NO, NO, NO, DW, NO, NO, NO, NO, NO, DW, NO, NO, NO, NO,
		DL, NO, NO, DW, NO, NO, NO, DL, NO, NO, NO, DW, NO, NO, DL,
		NO, NO, DW, NO, NO, NO, DL, NO, DL, NO, NO, NO, DW, NO, NO,
		NO, DW, NO, NO, NO, TL, NO, NO, NO, TL, NO, NO, NO, DW, NO,
		TW, NO, NO, DL, NO, NO, NO, NO, NO, NO, NO, DL, NO, NO, TW
	};

	m_board->SetBoardScoreModifiers(modifiers);
	m_scrabbleBoardRenderer = new ScrabbleBoardRenderer(m_board);

	m_scrabbleBoardRenderer->border_color		= { 34, 34, 34, 255 };
	m_scrabbleBoardRenderer->background_color	= { 12, 131, 101, 255 };
	m_scrabbleBoardRenderer->tile_divider_color = { 10, 105, 81, 255 };
	m_scrabbleBoardRenderer->tile_color			= { 255, 255, 255, (int)(255 * 0.7) };
	m_scrabbleBoardRenderer->text_color			= { 0, 0, 0, 255 };
	m_scrabbleBoardRenderer->dw_bg_color		= { 248, 160, 156, 255 };
	m_scrabbleBoardRenderer->tw_bg_color		= { 232, 60, 84, 255 };
	m_scrabbleBoardRenderer->dl_bg_color		= { 142, 190, 213, 255 };
	m_scrabbleBoardRenderer->tl_bg_color		= { 16, 126, 201, 255 };

	m_scrabbleBoardRenderer->position			= { 15.0f, 15.0f };
	m_scrabbleBoardRenderer->tileSize			= { 50.0f, 50.0f };
	m_scrabbleBoardRenderer->fontSize			= 18;

}
void Application::Unload()
{
	delete m_scrabbleBoardRenderer;
	m_scrabbleBoardRenderer = nullptr;
}
void Application::Update(float dt)
{
	m_scrabbleBoardRenderer->Update(dt);
}
void Application::Draw()
{
	BeginDrawing();

	ClearBackground({ 45, 52, 60, 255 });
	
	m_scrabbleBoardRenderer->Draw();

	EndDrawing();
}
