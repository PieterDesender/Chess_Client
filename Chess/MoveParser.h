#pragma once
#include "Singleton.h"
#include "Structs.h"
class MoveParser : public Singleton<MoveParser>
{
public:
	MoveParser() {};
	~MoveParser() {};
	
	Move ParseMove(string unparsedMove, Color playerColor) {
		Move parsedMove;

		if (unparsedMove.find("->") == string::npos && (unparsedMove.size() != 6 || unparsedMove.size() != 5)) {
			parsedMove.validParsed = false;
			return parsedMove;
		}

		size_t i = unparsedMove.find("->");
		parsedMove.objName = unparsedMove.substr(0, i);

		i += 2;
		string str = unparsedMove.substr(i, 1);
		const char* c = str.c_str();
		parsedMove.targetColumn = c[0];

		i++;
		str = unparsedMove.substr(i, 1);
		parsedMove.targetRow = stoi(str);

		parsedMove.unparsedString = unparsedMove;
		parsedMove.objColor = playerColor;

		parsedMove.validParsed = true;
		
		return parsedMove;
	}
};