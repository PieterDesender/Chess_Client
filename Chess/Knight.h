#pragma once
#include "GameObject.h"
#include "Structs.h"

class Knight : public GameObject
{
public:
	Knight(Color color, string objectName) : GameObject(color, objectName, PeiceType::KNIGHT) {};	
	~Knight() {};

	vector<string> GetAllPossibleMoves(Square* currentSqr, Move move, Board* pBoard) override;
};

