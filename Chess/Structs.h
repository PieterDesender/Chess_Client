#pragma once
#include "stdafx.h"
#include "Enumerations.h"

struct SquareDesc
{
	int m_Row;
	char m_Column;
	string GetName() {
		return to_string(m_Row) + m_Column;
	}
};

struct Move
{
	bool validParsed = false;
	bool validMove = false;
	string unparsedString;
	string objName;
	Color objColor;
	int targetRow;
	char targetColumn;
};