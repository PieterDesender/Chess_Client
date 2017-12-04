#include "stdafx.h"
#include "Square.h"
#include "Enumerations.h"
#include "GameObject.h"
#include "Pawn.h"
#include "Rook.h"
#include "bishop.h"
#include "King.h"
#include "Queen.h"
#include "Knight.h"
#include "Board.h"

Board::Board(Color playerColor)
{
	//Creating Board
	m_BoardArr.resize(m_BoardSize);
	for_each(m_BoardArr.begin(), m_BoardArr.end(), [boardSize = m_BoardSize](vector<Square*> &vec) { vec.resize(boardSize); });
	switch (playerColor)
	{
	case Color::BLACK:
		for (int i = 0; i < 8; i++) {
			for (int z = 'A'; z <= 'H'; z++) {
				m_BoardArr[i][z - 'A'] = new Square(i+1, (char)('H' - (z - 'A')));
			}
		}
		break;
	case Color::WHITE:
		for (int i = 0; i < 8; i++) {
			for (int z = 'A'; z <= 'H'; z++) {
				m_BoardArr[7 - i][z - 'A'] = new Square(i+1, (char)z);
			}
		}
		break;
	}
}

Board::~Board()
{
	for_each(m_BoardArr.begin(), m_BoardArr.end(), [](vector<Square *> vec) {
		for_each(vec.begin(), vec.end(), [](Square * sqrPtr) {
			delete sqrPtr;
		});
		vec.clear();
	});
	m_BoardArr.clear();
}

void Board::Paint(Color playerColor)
{
	cout << "+--+--+--+--+--+--+--+--+--+--+\n";
	if (playerColor == Color::WHITE)	cout << "|..|.A|.B|.C|.D|.E|.F|.G|.H|..|\n";
	else cout << "|..|.H|.G|.F|.E|.D|.C|.B|.A|..|\n";
	cout << "+--+--+--+--+--+--+--+--+--+--+\n";
	for (unsigned int i = 0; i < m_BoardArr.size(); i++)
	{
		if (playerColor == Color::WHITE) cout << "|." << m_BoardArr.size() - i << "|";
		else cout << "|." << i + 1 << "|";
		for (unsigned int z = 0; z < m_BoardArr.size(); z++)
		{
			cout << GetColorOfObjectOnSquare(m_BoardArr[i][z]);
			cout << "|";
			if (z == m_BoardArr.size() - 1) {
				if (playerColor == Color::WHITE) cout << "." << m_BoardArr.size() - i << "|\n";
				else cout << "." << i + 1 << "|\n";
			}
		}
		cout << "|..|";
		for (unsigned int z = 0; z < m_BoardArr.size(); z++)
		{
			cout << GetNameOfObjectOnSquare(m_BoardArr[i][z]);
			cout << "|";
			if (z == m_BoardArr.size() - 1)cout << "..|\n";
		}
		cout << "+--+--+--+--+--+--+--+--+--+--+\n";
	}
	if (playerColor == Color::WHITE) cout << "|..|.A|.B|.C|.D|.E|.F|.G|.H|..|\n";
	else cout << "|..|.H|.G|.F|.E|.D|.C|.B|.A|..|\n";
	cout << "+--+--+--+--+--+--+--+--+--+--+\n";
}

void Board::PopulateBoard()
{
	//all white object
	PopulateSpacials(1, Color::WHITE);
	PopulatatePawns(2, Color::WHITE);

	//all black object
	PopulateSpacials(8, Color::BLACK);
	PopulatatePawns(7, Color::BLACK);


	//GetSquareByColumnAndRow(5, 'E')->SetObjectOnSquare(new Knight(Color::BLACK, "K1"));
	//GetSquareByColumnAndRow(2, 'B')->SetObjectOnSquare(new Bishop(Color::WHITE, "B1"));
}

Square * Board::GetSquarePtrByObjNameColor(string objName, Color objColor)
{
	/*
	for_each(m_BoardArr.begin(), m_BoardArr.end(), [objName, objColor](vector<Square *> vec) {
		for_each(vec.begin(), vec.end(), [objName, objColor](Square * sqrPtr) {
			GameObject* objPtr = sqrPtr->GetObjectOnSquare();
			if (objPtr != nullptr && objPtr->GetName() == objName && objPtr->GetColor() == objColor) {
				return objPtr;
			}
		});
	});
	*/
	for each (vector<Square *> vec in m_BoardArr)
	{
		for each (Square* sqrPtr in vec)
		{
			GameObject* objPtr = sqrPtr->GetObjectOnSquare();
			if (objPtr != nullptr && objPtr->GetName() == objName && objPtr->GetColor() == objColor) {
				return sqrPtr;
			}
		}
	}
	return nullptr;
}

Square * Board::GetSquareByColumnAndRow(int row, char column)
{
	for each (vector<Square*> vec in m_BoardArr)
	{
		for each (Square* ptr in vec) {
			if (ptr->GetColumn() == column && ptr->GetRow() == row)return ptr;
		}
	}
	return nullptr;
}

void Board::PopulatatePawns(int row, Color color)
{
	for (int i = 0; i < 8; i++)
	{
		GetSquareByColumnAndRow(row, 'A'+i)->SetObjectOnSquare(new Pawn(color, "P" + to_string(i + 1)));
	}
}

void Board::PopulateSpacials(int row, Color color)
{
	GetSquareByColumnAndRow(row, 'A')->SetObjectOnSquare(new Rook(color, "R1"));
	GetSquareByColumnAndRow(row, 'B')->SetObjectOnSquare(new Knight(color, "K1"));
	GetSquareByColumnAndRow(row, 'C')->SetObjectOnSquare(new Bishop(color, "B1"));
	GetSquareByColumnAndRow(row, 'D')->SetObjectOnSquare(new King(color, "K"));
	GetSquareByColumnAndRow(row, 'E')->SetObjectOnSquare(new Queen(color, "Q"));
	GetSquareByColumnAndRow(row, 'F')->SetObjectOnSquare(new Bishop(color, "B2"));
	GetSquareByColumnAndRow(row, 'G')->SetObjectOnSquare(new Knight(color, "K2"));
	GetSquareByColumnAndRow(row, 'H')->SetObjectOnSquare(new Rook(color, "R2"));
}

string Board::GetColorOfObjectOnSquare(Square * square)
{

	if (square->GetObjectOnSquare() == nullptr)return "..";
	switch (square->GetObjectOnSquare()->GetColor())
	{
	case Color::BLACK:
		return ".B";
		break;
	case Color::WHITE:
		return ".W";
		break;
	}
	return "";
	//return square->GetColumn() + to_string(square->GetRow());
}

string Board::GetNameOfObjectOnSquare(Square * square)
{
	if (square->GetObjectOnSquare() == nullptr)return "..";
	string name = square->GetObjectOnSquare()->GetName();
	if (name.size() == 1)return "." + name;
	return name;
}

bool Board::CheckIfAnyObjectOnSquareByDesc(SquareDesc desc)
{
	if(GetSquareByColumnAndRow(desc.m_Row, desc.m_Column)->GetObjectOnSquare() == nullptr)
		return false;
	return true;
}


bool Board::CheckSquareDescOutOfBound(SquareDesc desc)
{
	if (desc.m_Row <= m_BoardSize && desc.m_Row >= 1 && desc.m_Column - 'A' < m_BoardSize && desc.m_Column - 'A' >= 0)
		return false;
	return true;
}