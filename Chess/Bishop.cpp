#include "stdafx.h"
#include "Bishop.h"

vector<string> Bishop::GetAllPossibleMoves(Square * currentSqr, Move move, Board * pBoard)
{
	vector<string> vec;
	SquareDesc origDesc;
	origDesc.m_Column = currentSqr->GetColumn();
	origDesc.m_Row = currentSqr->GetRow();

	//forward side
	MultipleMove(1, 1, vec, origDesc, pBoard);

	//forward other side
	MultipleMove(1, -1, vec, origDesc, pBoard);

	//back side
	MultipleMove(-1, -1, vec, origDesc, pBoard);

	//back other side
	MultipleMove(-1, 1, vec, origDesc, pBoard);

	return vec;
}
