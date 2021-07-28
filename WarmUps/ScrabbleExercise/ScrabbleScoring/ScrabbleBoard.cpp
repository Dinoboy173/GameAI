
#include "ScrabbleBoard.h"

#include <cstring>

ScrabbleBoard::ScrabbleBoard(int rows, int cols) :
	ROWS(rows), COLS(cols)
{
	m_boardModifiers = new unsigned int[ROWS * COLS];
	m_boardCharacters = new char[ROWS * COLS];

	// Initialise board values
	for (int i = 0; i < ROWS * COLS; i++)
	{
		m_boardModifiers[i] = (int)EScoreMod::NO;
		m_boardCharacters[i] = ' ';
	}
}

ScrabbleBoard::~ScrabbleBoard()
{
	delete[] m_boardModifiers;
	delete[] m_boardCharacters;
}

ScrabbleBoard::EScoreMod ScrabbleBoard::GetBoardModifier(int xIndex, int yIndex)
{
	int index = yIndex * ROWS + xIndex;
	return (EScoreMod)m_boardModifiers[index];
}

char ScrabbleBoard::GetBoardCharacter(int xIndex, int yIndex)
{
	int index = yIndex * ROWS + xIndex;
	return m_boardCharacters[index];
}

void ScrabbleBoard::SetBoardCharacter(int xIndex, int yIndex, char c)
{
	if (xIndex < 0 || yIndex < 0 || xIndex >= COLS || yIndex >= ROWS)
		return;

	int index = yIndex * ROWS + xIndex;
	m_boardCharacters[index] = c;
}

void ScrabbleBoard::SetBoardScoreModifiers(unsigned int* board)
{
	for (int i = 0; i < ROWS * COLS; i++)
		m_boardModifiers[i] = board[i];
}

void ScrabbleBoard::PlaceText(int xIndex, int yIndex, const char* text, EDirection dir)
{
	int score = CalculateScore(xIndex, yIndex, text, dir);
	m_totalScore += score;

	int xo = 0, yo = 0;
	switch (dir)
	{
	case EDirection::RIGHT: xo = 1; break;
	case EDirection::DOWN:  yo = 1; break;
	}

	int len = strlen(text);
	for (int i = 0; i < len; i++)
	{
		int xi = xIndex + (i * xo);
		int yi = yIndex + (i * yo);

		SetBoardCharacter(xi, yi, text[i]);
	}
}

unsigned int ScrabbleBoard::GetTotalScore()
{
	return m_totalScore;
}

bool ScrabbleBoard::CanPlaceText(int xIndex, int yIndex, const char* text, EDirection dir)
{
	// ========================================================================
	// DAILY WARMUP - TODO
	// ========================================================================
	// write your code here

	// is in bounds

	int len = strlen(text);

	if (dir == EDirection::RIGHT)
	{
		if (xIndex + len > COLS)
			return false;
	}
	else
	{
		if (yIndex + len > ROWS)
			return false;
	}

	// is overlapping
	if (dir == EDirection::RIGHT)
	{
		for (int i = 0; i < len; i++)
		{
			if (GetBoardCharacter(xIndex + i, yIndex) != text[i] && GetBoardCharacter(xIndex + i, yIndex) != ' ')
				return false;
		}
	}
	else
	{
		for (int i = 0; i < len; i++)
		{
			if (GetBoardCharacter(xIndex, yIndex + i) != text[i] && GetBoardCharacter(xIndex, yIndex + i) != ' ')
				return false;
		}
	}

	return true;
}

#include <map>

unsigned int ScrabbleBoard::CalculateScore(int xIndex, int yIndex, const char* text, EDirection dir)
{
	// ========================================================================
	// DAILY WARMUP - TODO
	// ========================================================================
	// write your code here

	int score = 0;

	int len = strlen(text);

	std::map<char, int> scores{ {'a', 1}, {'e', 1}, {'i', 1}, {'o', 1}, {'u', 1}, {'l', 1}, {'n', 1}, {'s', 1}, {'t', 1}, {'r', 1}, {'d', 2}, {'g', 2}, {'b', 3}, {'c', 3}, {'m', 3}, {'p', 3}, {'f', 4}, {'h', 4}, {'v', 4}, {'w', 4}, {'y', 4}, {'k', 5}, {'j', 8}, {'x', 8}, {'q', 10}, {'z',10} };

	for (int i = 0; i < len; i++)
	{
		score += scores[towlower(text[i])];

		if (dir == EDirection::RIGHT)
		{
			if ((int)GetBoardModifier(xIndex + i, yIndex) == 1)
				score += scores[towlower(text[i])];

			else if ((int)GetBoardModifier(xIndex + i, yIndex) == 2)
				score += scores[towlower(text[i])] * 2;

			else if ((int)GetBoardModifier(xIndex + i, yIndex) == 3)
				for (int j = 0; j < len; j++)
					score += scores[towlower(text[i])];

			else if ((int)GetBoardModifier(xIndex + i, yIndex) == 4)
				for (int j = 0; j < len; j++)
					score += scores[towlower(text[i])] * 2;
		}
		else
		{
			if ((int)GetBoardModifier(xIndex, yIndex + i) == 1)
				score += scores[towlower(text[i])];

			else if ((int)GetBoardModifier(xIndex, yIndex + i) == 2)
				score += scores[towlower(text[i])] * 2;

			else if ((int)GetBoardModifier(xIndex, yIndex + i) == 3)
				for (int j = 0; j < len; j++)
					score += scores[towlower(text[i])];

			else if ((int)GetBoardModifier(xIndex, yIndex + i) == 4)
				for (int j = 0; j < len; j++)
					score += scores[towlower(text[i])] * 2;
		}
	}

	return score;
}

#include <iostream>

class Dictionary
{
public:
    Dictionary(const char *filename)
    {
    
    };
    
    ~Dictionary()
    {
    
    }
    
    bool Contains(const char *word)
    {
        return true;
    }
protected:
private:
};

int main(int argc, char **argv)
{
    {
        Dictionary dictionary("dictionary.txt");
        std::cout << std::boolalpha;
        std::cout << dictionary.Contains("hello") << std::endl;
        std::cout << dictionary.Contains("pilgrimaged") << std::endl;
        std::cout << dictionary.Contains("ejector") << std::endl;
        std::cout << dictionary.Contains("thisworddoesntexist") << std::endl;
        std::cout << dictionary.Contains("z") << std::endl;
    }
    return 0;
}