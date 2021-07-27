#pragma once

class ScrabbleBoard;
class ScrabbleBoardRenderer;

class Application
{
public:

	Application();
	~Application();

	void Run();

	void Load();
	void Unload();
	void Update(float dt);
	void Draw();

protected:
private:

	int m_windowWidth = 1200;
	int m_windowHeight = 800;

	ScrabbleBoard* m_board = nullptr;
	ScrabbleBoardRenderer* m_scrabbleBoardRenderer = nullptr;
};