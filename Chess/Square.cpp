#include "stdafx.h"
#include "Square.h"
#include "GameObject.h"

Square::~Square()
{
	if (m_GameObject != nullptr) {
		delete m_GameObject;
		m_GameObject = nullptr;
	}
}

GameObject * Square::GetObjectOnSquare()
{
	return m_GameObject;
}

void Square::SetObjectOnSquare(GameObject * obj)
{
	m_GameObject = obj;
}
