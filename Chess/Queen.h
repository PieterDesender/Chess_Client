#pragma once
#include "GameObject.h"
#include "Structs.h"
class Queen : public GameObject
{
public:
	Queen(Color color, string objectName) : GameObject(color, objectName, PeiceType::QUEEN) {};
	~Queen() {};

	vector<string> GetAllPossibleMoves(Square* currentSqr, Move move, Board* pBoard) override;
};