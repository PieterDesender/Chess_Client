#include "stdafx.h"
#include "Queen.h"

vector<string> Queen::GetAllPossibleMoves(Square * currentSqr, Move move, Board * pBoard)
{
	vector<string> vec;
	SquareDesc origDesc, targetDesc;
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

	//forward
	MultipleMove(1, 0, vec, origDesc, pBoard);

	//Back
	MultipleMove(-1, 0, vec, origDesc, pBoard);

	//side 
	MultipleMove(0, 1, vec, origDesc, pBoard);

	//other side 
	MultipleMove(0, -1, vec, origDesc, pBoard);

	return vec;
}
