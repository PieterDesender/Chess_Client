#include "stdafx.h"
#include "Enumerations.h"
#include "Structs.h"
#include "Player.h"
#include "Board.h"
#include "GameObject.h"
#include "Square.h"

Player::Player(Color playerColor) : m_PlayerColor(playerColor)
{
}

Player::~Player()
{
}

bool Player::IsMovePossibleAndMove(Move move, Board* pBoard)
{
	bool isPossible = false;

	Square* objCurrentSquare = pBoard->GetSquarePtrByObjNameColor(move.objName, move.objColor);
	vector<string> possibleMoves = objCurrentSquare->GetObjectOnSquare()->GetAllPossibleMoves(objCurrentSquare, move, pBoard);

	string suggestedMove = to_string(move.targetRow) + move.targetColumn;

	for_each(possibleMoves.begin(), possibleMoves.end(), [suggestedMove, &isPossible](string str)
	{
		if (str == suggestedMove)isPossible = true;
	});
	if (isPossible)MovePiece(move, pBoard);
	return isPossible;
}

void Player::MovePiece(Move move, Board* pBoard)
{
	Square* objCurrentSquare = pBoard->GetSquarePtrByObjNameColor(move.objName, move.objColor);
	GameObject* objPtr = objCurrentSquare->GetObjectOnSquare();
	Square* objTargetSquare = pBoard->GetSquareByColumnAndRow(move.targetRow, move.targetColumn);

	if (objTargetSquare->GetObjectOnSquare() != nullptr) {
		delete objTargetSquare->GetObjectOnSquare();
	}
	objTargetSquare->SetObjectOnSquare(objPtr);
	objCurrentSquare->SetObjectOnSquare(nullptr);
}