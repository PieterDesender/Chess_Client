#include "stdafx.h"
#include "ChessGame.h"
#include "MoveParser.h"
#include "Enumerations.h"

void mainMethod();
void test();

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(157);

	mainMethod();
	cout << "\nDone";

	cin.get();
	_CrtDumpMemoryLeaks();
	return 0;
}

void mainMethod()
{
	//Setting window sizes
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT rect = { 0,0, 100, 60 };
	SetConsoleWindowInfo(hConsole, true, &rect);

	ChessGame* pChessGame = new ChessGame();

	pChessGame->GameLoop();

	delete pChessGame;
	pChessGame = nullptr;
}

//Move format
//R1->A2