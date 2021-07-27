#pragma once



class ScrabbleBoard
{
public:

	enum class EScoreMod
	{
		NO, DL, TL, DW, TW
	};

	enum class EDirection
	{
		RIGHT, DOWN
	};

	const int ROWS = 15;
	const int COLS = 15;

	ScrabbleBoard(int rows, int cols);
	~ScrabbleBoard();

	void SetBoardScoreModifiers(unsigned int* board);

	EScoreMod GetBoardModifier(int xIndex, int yIndex);
	char GetBoardCharacter(int xIndex, int yIndex);

	void SetBoardCharacter(int xIndex, int yIndex, char c);
	void PlaceText(int xIndex, int yIndex, const char* text, EDirection dir);

	unsigned int GetTotalScore();

	bool CanPlaceText(int xIndex, int yIndex, const char *text, EDirection dir);

	unsigned int CalculateScore(int xIndex, int yIndex, const char* text, EDirection dir);

protected:

	unsigned int m_totalScore = 0;
	unsigned int* m_boardModifiers = nullptr;
	char* m_boardCharacters = nullptr;


private:
};
