#pragma once
#include "Enumerations.h"
#include "Structs.h"

class Board;

class Player
{
public:
	Player(Color playerColor);
	~Player();

	Color GetPlayerColor() { return m_PlayerColor; }

	bool IsMovePossibleAndMove(Move move, Board* pBoard);
	void MovePiece(Move move, Board* pBoard);

private:
	Color m_PlayerColor;
};
