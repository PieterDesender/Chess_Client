#pragma once
#include "Enumerations.h"
#include "Structs.h"
class Square;

class Board
{
public:
	Board(Color playerColor);
	~Board();

	void Paint(Color playerColor);

	void PopulateBoard();

	Square* GetSquarePtrByObjNameColor(string objName, Color objColor);
	Square* GetSquareByColumnAndRow(int row, char column);

	bool CheckIfAnyObjectOnSquareByDesc(SquareDesc desc);
	bool CheckSquareDescOutOfBound(SquareDesc desc);

private:
	int m_BoardSize = 8;
	vector<vector<Square*>>m_BoardArr;

	string GetColorOfObjectOnSquare(Square* square);
	string GetNameOfObjectOnSquare(Square* square);

	void PopulatatePawns(int row, Color color);
	void PopulateSpacials(int row, Color color);
};