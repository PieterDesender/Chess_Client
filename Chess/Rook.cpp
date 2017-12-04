#include "stdafx.h"
#include "Rook.h"

vector<string> Rook::GetAllPossibleMoves(Square * currentSqr, Move move, Board * pBoard)
{
	vector<string> vec;
	SquareDesc origDesc;
	origDesc.m_Column = currentSqr->GetColumn();
	origDesc.m_Row = currentSqr->GetRow();

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
