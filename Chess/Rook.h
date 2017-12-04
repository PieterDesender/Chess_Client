#pragma once
#include "GameObject.h"
#include "Structs.h"
class Rook : public GameObject
{
public:
	Rook(Color color, string objectName) : GameObject(color, objectName, PeiceType::ROOK) {};
	~Rook() {};

	vector<string> GetAllPossibleMoves(Square* currentSqr, Move move, Board* pBoard) override;
};