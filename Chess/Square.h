#pragma once
#include "Structs.h"

class GameObject;

class Square
{
public:
	Square(int row, char column) : m_Row(row), m_Column(column) {};
	~Square();

	GameObject* GetObjectOnSquare();
	void SetObjectOnSquare(GameObject* obj);

	int GetRow() { return m_Row; }
	char GetColumn() { return m_Column; }
private:
	char m_Column;
	int m_Row;
	GameObject* m_GameObject;
};
