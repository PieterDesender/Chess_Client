#pragma once
#include "GameObject.h"
#include "Structs.h"
class King : public GameObject
{
public:
	King(Color color, string objectName) : GameObject(color, objectName, PeiceType::KING) {};
	~King() {};

	vector<string> GetAllPossibleMoves(Square* currentSqr, Move move, Board* pBoard) override;
};

