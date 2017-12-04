#include "stdafx.h"
#include "Pawn.h"

vector<string> Pawn::GetAllPossibleMoves(Square * currentSqr, Move move, Board * pBoard)
{
	vector<string> vec;

	SquareDesc targetDesc;
	targetDesc.m_Column = currentSqr->GetColumn();
	targetDesc.m_Row = currentSqr->GetRow();

	//1 forward
	if (move.objColor == Color::WHITE) {
		targetDesc.m_Row += 1;
	}
	else {
		targetDesc.m_Row -= 1;
	}
	Square* targetSqr = pBoard->GetSquareByColumnAndRow(targetDesc.m_Row, targetDesc.m_Column);
	if (!pBoard->CheckSquareDescOutOfBound(targetDesc)) {
		if (targetSqr->GetObjectOnSquare() == nullptr)
		{
			vec.push_back(targetDesc.GetName());
		}
	}
	
	//1 side
	targetDesc.m_Column -= 1;

	if (IsValidMove(targetDesc, pBoard)) {
		vec.push_back(targetDesc.GetName());
	}

	//2 other side
	targetDesc.m_Column += 2;

	if (IsValidMove(targetDesc, pBoard))
		vec.push_back(targetDesc.GetName());

	return vec;
}
