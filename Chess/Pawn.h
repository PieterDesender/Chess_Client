#pragma once
#include "GameObject.h"
#include "Structs.h"
#include "Board.h"

class Pawn : public GameObject
{
public:
	Pawn(Color color, string objectName) : GameObject(color,objectName, PeiceType::PAWN) {};
	~Pawn() {};

	vector<string> GetAllPossibleMoves(Square* currentSqr, Move move, Board* pBoard) override;
};

