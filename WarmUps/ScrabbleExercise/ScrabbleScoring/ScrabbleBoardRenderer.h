#pragma once

#include "raylib.h"

class ScrabbleBoard;

class ScrabbleBoardRenderer
{
public:

	Color border_color;
	Color background_color;
	Color tile_divider_color;
	Color tile_color;
	Color text_color;
	Color dw_bg_color;
	Color tw_bg_color;
	Color dl_bg_color;
	Color tl_bg_color;

	Vector2 position;
	Vector2 tileSize;

	int fontSize;

public:

	ScrabbleBoardRenderer(ScrabbleBoard *board);
	~ScrabbleBoardRenderer();

	void Update(float dt);
	void Draw();

protected:

protected:

	ScrabbleBoard* m_board = nullptr;
	int m_mxIndex = -1;
	int m_myIndex = -1;

	char previewText[10] = "hello";
	int direction = 0;
};

