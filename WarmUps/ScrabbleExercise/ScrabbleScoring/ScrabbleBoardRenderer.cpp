#include "ScrabbleBoardRenderer.h"
#include "ScrabbleBoard.h"

#include "raylib.h"
#include "raygui.h"

#include <string>
#include <cstring>

ScrabbleBoardRenderer::ScrabbleBoardRenderer(ScrabbleBoard* board) :
	m_board(board)
{
	
}

ScrabbleBoardRenderer::~ScrabbleBoardRenderer()
{

}

void ScrabbleBoardRenderer::Update(float dt)
{
	auto mousePos = GetMousePosition();
	m_mxIndex = (mousePos.x - position.x) / (tileSize.x + 1);
	m_myIndex = (mousePos.y - position.y) / (tileSize.y + 1);
	if (m_mxIndex < 0 || m_mxIndex >= m_board->COLS) m_mxIndex = -1;
	if (m_myIndex < 0 || m_myIndex >= m_board->ROWS) m_myIndex = -1;

	if (IsMouseButtonPressed(0) &&
		m_mxIndex >= 0 && m_mxIndex < m_board->COLS &&
		m_myIndex >= 0 && m_myIndex < m_board->ROWS && 
		m_board->CanPlaceText(m_mxIndex, m_myIndex, previewText, (ScrabbleBoard::EDirection)direction))
	{
		m_board->PlaceText(m_mxIndex, m_myIndex, previewText, (ScrabbleBoard::EDirection)direction);
	}
}

void ScrabbleBoardRenderer::Draw()
{
	int width = (tileSize.x + 1) * m_board->COLS - 1;
	int height = (tileSize.y + 1) * m_board->ROWS - 1;
	int borderSize = 3;

	// draw dark black border
	DrawRectangle((int)position.x- borderSize, (int)position.y- borderSize, width + (borderSize*2), height + (borderSize * 2), border_color);

	// draw board background
	DrawRectangle((int)position.x, (int)position.y, width, height, background_color);

	// Draw Board Modifier Tiles
	for (int yi = 0; yi < m_board->ROWS; yi++)
	{
		for (int xi = 0; xi < m_board->COLS; xi++)
		{
			auto mod = m_board->GetBoardModifier(xi, yi);

			// dont need to draw anything
			if (mod == ScrabbleBoard::EScoreMod::NO)
				continue;

			// get the tile color for the modifier
			Color tc = BLACK;
			switch (mod)
			{
			case ScrabbleBoard::EScoreMod::NO: continue;
			case ScrabbleBoard::EScoreMod::DL: tc = dl_bg_color; break;
			case ScrabbleBoard::EScoreMod::TL: tc = tl_bg_color; break;
			case ScrabbleBoard::EScoreMod::DW: tc = dw_bg_color; break;
			case ScrabbleBoard::EScoreMod::TW: tc = tw_bg_color; break;
			}

			int xPos = position.x + xi * (tileSize.x + 1);
			int yPos = position.y + yi * (tileSize.y + 1);

			DrawRectangle(xPos, yPos, tileSize.x, tileSize.y, tc);

			const char* text = "";
			switch (mod)
			{
			case ScrabbleBoard::EScoreMod::NO: break;
			case ScrabbleBoard::EScoreMod::DL: text = "DL"; break;
			case ScrabbleBoard::EScoreMod::TL: text = "TL"; break;
			case ScrabbleBoard::EScoreMod::DW: text = "DW"; break;
			case ScrabbleBoard::EScoreMod::TW: text = "TW"; break;
			}

			if (m_board->GetBoardCharacter(xi, yi) == ' ')
			{
				auto sz = MeasureTextEx(GetFontDefault(), text, fontSize, 0);

				DrawText(text,
					xPos + (tileSize.x / 2.0f) - (sz.x / 2.0f),
					yPos + (tileSize.y / 2.0f) - (sz.y / 2.0f),
					fontSize, WHITE);
			}
			

			
		}
	}

	for (int yi = 0; yi < m_board->ROWS; yi++)
	{
		for (int xi = 0; xi < m_board->COLS; xi++)
		{
			char c = m_board->GetBoardCharacter(xi, yi);
			if (c == ' ') continue;

			int xPos = position.x + xi * (tileSize.x + 1);
			int yPos = position.y + yi * (tileSize.y + 1);

			DrawRectangle(xPos, yPos, tileSize.x, tileSize.y, tile_color);

			std::string s;
			s += c;
			
			auto sz = MeasureTextEx(GetFontDefault(), s.c_str(), fontSize, 0);

			DrawText(s.c_str(),
				xPos + (tileSize.x / 2.0f) - (sz.x / 2.0f),
				yPos + (tileSize.y / 2.0f) - (sz.y / 2.0f),
				fontSize, text_color);

		}
	}

	// draw horizontal grid lines
	for (int yi = 1; yi < m_board->ROWS; yi++)
	{
		int yPos = position.y + yi * (tileSize.y + 1);
		DrawLine(position.x, yPos, position.x + width, yPos, tile_divider_color);
	}

	// draw vertical grid lines
	for (int xi = 1; xi < m_board->COLS; xi++)
	{
		int xPos = position.x + xi * (tileSize.x + 1);
		DrawLine(xPos, position.y, xPos, position.y + height, tile_divider_color);
	}


	// Draw hover
	if (m_mxIndex >= 0 && m_myIndex >= 0)
	{

		int xo = 0, yo = 0;
		switch (direction)
		{
		case (int)ScrabbleBoard::EDirection::RIGHT: xo = 1; break;
		case (int)ScrabbleBoard::EDirection::DOWN: yo =  1; break;
		}

		int startXPos = (position.x + m_mxIndex * (tileSize.x + 1));
		int startYPos = (position.y + m_myIndex * (tileSize.y + 1));

		int len = strlen(previewText);

		bool canPlaceText = m_board->CanPlaceText(m_mxIndex, m_myIndex, previewText, (ScrabbleBoard::EDirection)direction);

		for (int i = 0; i < len; i++)
		{
			std::string s;
			s += previewText[i];

			int xi = m_mxIndex + (i * xo);
			int yi = m_myIndex + (i * yo);

			if (xi < 0 || yi < 0 || xi >= m_board->COLS || yi >= m_board->ROWS)
				continue;

			int xPos = position.x + (xi * (tileSize.x + 1));
			int yPos = position.y + (yi * (tileSize.y + 1));

			Color previewTileColor = { 255, 255, 255, (int)(255 * 0.6) };
			if(!canPlaceText) previewTileColor = { 255, 0, 0, (int)(255 * 0.6) };

			DrawRectangle(xPos, yPos, tileSize.x, tileSize.y, previewTileColor);

			auto sz = MeasureTextEx(GetFontDefault(), s.c_str(), fontSize, 0);

			DrawText(s.c_str(),
				xPos + (tileSize.x / 2.0f) - (sz.x / 2.0f),
				yPos + (tileSize.y / 2.0f) - (sz.y / 2.0f),
				fontSize, text_color);
		}	

		char previewScoreText[32];
		sprintf(previewScoreText, "%i", m_board->CalculateScore(m_mxIndex, m_myIndex, previewText, (ScrabbleBoard::EDirection)direction));
		DrawText(previewScoreText, startXPos, startYPos - 20, 20, WHITE);
	}


	char totalScoreText[32];
	sprintf(totalScoreText, "SCORE: %i", m_board->GetTotalScore());
	DrawText(totalScoreText,
		position.x + width + 30,
		position.y,
		48, WHITE);

	// UI at end of 
	int len = strlen(previewText);
	for (int i = 0; i < len; i++)
	{
		std::string s;
		s += previewText[i];

		auto sz = MeasureTextEx(GetFontDefault(), s.c_str(), fontSize, 0);

		int xPos = position.x + width + 30 + (i * tileSize.x - 2);
		int yPos = position.y + 58;

		DrawRectangle(xPos, yPos, tileSize.x - 2, tileSize.y - 2, { 255, 255, 255, (int)(255 * 0.2) });

		DrawText(s.c_str(),
			xPos + (tileSize.x / 2.0f) - (sz.x / 2.0f),
			yPos + (tileSize.y / 2.0f) - (sz.y / 2.0f),
			fontSize, WHITE);
	}

	GuiTextBox({ position.x + width + 30, position.y + 118, 100, 20 }, previewText, 9, true);

	GuiDropdownBox({ position.x + width + 30 + 110, position.y + 118, 100, 20 }, "RIGHT;DOWN", &direction, true);

}
