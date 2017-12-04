#include "stdafx.h"
#include "King.h"

vector<string> King::GetAllPossibleMoves(Square * currentSqr, Move move, Board * pBoard)
{
	vector<string> vec;
	SquareDesc origDesc;
	origDesc.m_Column = currentSqr->GetColumn();
	origDesc.m_Row = currentSqr->GetRow();

	//1 forward
	SingleMove(1, 0, vec, origDesc, pBoard);

	//1 back
	SingleMove(-1, 0, vec, origDesc, pBoard);

	//1 side
	SingleMove(0, 1, vec, origDesc, pBoard);

	//1 other side
	SingleMove(0, -1, vec, origDesc, pBoard);

	//1 forward side
	SingleMove(1, 1, vec, origDesc, pBoard);

	//1 forward other side
	SingleMove(1, -1, vec, origDesc, pBoard);

	//1 back side
	SingleMove(-1, -1, vec, origDesc, pBoard);

	//1 back other side
	SingleMove(-1, 1, vec, origDesc, pBoard);

	return vec;
}
