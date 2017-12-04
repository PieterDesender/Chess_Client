#pragma once
#include "GameObject.h"
#include "Structs.h"

class Bishop : public GameObject 
{
public:
	Bishop(Color color, string objectName) : GameObject(color, objectName, PeiceType::BISHOP) {};
	~Bishop() {};

	vector<string> GetAllPossibleMoves(Square* currentSqr, Move move, Board* pBoard) override;
};

