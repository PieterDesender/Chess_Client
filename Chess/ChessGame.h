#pragma once
#include "Enumerations.h"

class Board;
class Player;

class ChessGame
{
public:
	ChessGame();
	~ChessGame();

	void GameLoop();

private:
	/**************************** MEMBER FUNTIONS *********************/
	void GameRunning();
	void GameHelp();
	bool GameInitialise();
	void GameEnd();

	string WaitForPlayerInput();

	void Paint();
	void OutputHelpScreen();

	void PlayerMove();
	void OtherplayerMove();

	bool CheckQuit();
	bool CheckHelp();
	/**************************** MEMBER VARIABLES ********************/
	GameState m_GameState = GameState::INITIALISE;

	string m_PlayerInput;
	string m_IPAddres;

	int m_Port;

	Board* m_pBoard = nullptr;
	Player* m_pPlayer = nullptr;
	Player* m_pOtherPlayer = nullptr;
};
