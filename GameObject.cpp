#include "GameObject.h"


GameObject::GameObject(const CellPosition& pos)
{
	position = pos; // Sets Position
}

CellPosition GameObject::GetPosition() const
{
	return position;
}


bool GameObject::IsOverlapping(GameObject* newObj) //
{
	CellPosition c1 = newObj->position;
	CellPosition c2 = position;
	if (c1.HCell() == c2.HCell())
	{
		if (c1.VCell() == c2.VCell())
			return true;
	}
	else
		return false;
}

GameObject::~GameObject()
{
}