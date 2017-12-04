#pragma once
#include "stdafx.h"
#include "Enumerations.h"
#include "Structs.h"
#include "Board.h"
#include "Square.h"
class GameObject
{
public:
	GameObject(Color color, string objectName, PeiceType type) : m_Color(color),m_Name(objectName), m_Type(type) {};
	virtual ~GameObject() {};

	Color GetColor() { return m_Color; }
	string GetName() { return m_Name; }
	PeiceType GetPeiceType() { return m_Type; }

	virtual vector<string> GetAllPossibleMoves(Square* currentSqr, Move move, Board* pBoard) = 0;
protected:
	Color m_Color;
	string m_Name;
	PeiceType m_Type;

	struct validMultipleMove {
		bool validMove = false;
		bool lastMove = false;
	};

	bool IsValidMove(SquareDesc targetDesc, Board* pBoard) {
		if (!pBoard->CheckSquareDescOutOfBound(targetDesc)) {
			Square* sqrPtr = pBoard->GetSquareByColumnAndRow(targetDesc.m_Row, targetDesc.m_Column);
			if (sqrPtr->GetObjectOnSquare() == nullptr) {
				return true;
			}
			else {
				if (sqrPtr->GetObjectOnSquare()->GetColor() != m_Color) {
					return true;
				}
			}
		}
		return false;
	}

	validMultipleMove IsValidMultipleMove(SquareDesc targetDesc, Board* pBoard) {
		validMultipleMove returnVal;
		if (!pBoard->CheckSquareDescOutOfBound(targetDesc)) {
			Square* sqrPtr = pBoard->GetSquareByColumnAndRow(targetDesc.m_Row, targetDesc.m_Column);
			if (sqrPtr->GetObjectOnSquare() == nullptr) {
				returnVal.validMove = true;
				return returnVal;
			}
			else {
				if (sqrPtr->GetObjectOnSquare()->GetColor() != m_Color) {
					returnVal.validMove = true;
					returnVal.lastMove = true;
					return returnVal;
				}
			}
		}
		return returnVal;
	}

	void SingleMove(int rowModifier, int colModifier, vector<string> &vec, SquareDesc origDesc, Board * pBoard) {
		SquareDesc targetDesc;
		targetDesc.m_Column = origDesc.m_Column;
		targetDesc.m_Row = origDesc.m_Row;

		targetDesc.m_Row += rowModifier;
		targetDesc.m_Column += colModifier;

		if (IsValidMove(targetDesc, pBoard)) {
			vec.push_back(targetDesc.GetName());
		}
	}

	void MultipleMove(int rowModifier, int colModifier, vector<string> &vec, SquareDesc origDesc, Board * pBoard) {
		SquareDesc targetDesc;
		targetDesc.m_Column = origDesc.m_Column;
		targetDesc.m_Row = origDesc.m_Row;

		targetDesc.m_Row += rowModifier;
		targetDesc.m_Column += colModifier;

		validMultipleMove validMove = IsValidMultipleMove(targetDesc, pBoard);
		while (validMove.validMove && !validMove.lastMove) {
			vec.push_back(targetDesc.GetName());

			targetDesc.m_Row += rowModifier;
			targetDesc.m_Column += colModifier;

			validMove = IsValidMultipleMove(targetDesc, pBoard);
		}

		if (validMove.validMove && validMove.lastMove) {
			vec.push_back(targetDesc.GetName());
		}
	}
};
