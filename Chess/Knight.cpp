#include "stdafx.h"
#include "Knight.h"

vector<string> Knight::GetAllPossibleMoves(Square * currentSqr, Move move, Board * pBoard)
{
	vector<string> vec;
	SquareDesc origDesc;
	origDesc.m_Column = currentSqr->GetColumn();
	origDesc.m_Row = currentSqr->GetRow();

	SingleMove(2, 1, vec, origDesc, pBoard);

	SingleMove(2, -1, vec, origDesc, pBoard);

	SingleMove(-2, 1, vec, origDesc, pBoard);

	SingleMove(-2, -1, vec, origDesc, pBoard);

	SingleMove(1, 2, vec, origDesc, pBoard);
	
	SingleMove(-1, 2, vec, origDesc, pBoard);

	SingleMove(1, -2, vec, origDesc, pBoard);

	SingleMove(-1, -2, vec, origDesc, pBoard);

	return vec;
}
