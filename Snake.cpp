#include "snake.h"

snake::snake(const CellPosition& startCellPos, const CellPosition& endCellPos) : GameObject(startCellPos)
{
	if (startCellPos.IsValidCell()) {
		position = startCellPos;
	}

	if (endCellPos.IsValidCell()) {
		this->endCellPos = endCellPos;
	}
}

void snake::Draw(Output* pOut) const
{
	pOut->DrawSnake(position, endCellPos);
}

void snake::Apply(Grid* pGrid, Player* pPlayer)
{
	// 1- Print a message "You have reached a ladder. Click to continue ..." and wait mouse click
	pGrid->PrintErrorMessage("You have reached a snake. Click to continue ...");
	// 2- Apply the snake's effect by moving the player to the endCellPos

	pGrid->UpdatePlayerCell(pPlayer, endCellPos);
}

bool snake::IsOverLapping(GameObject* newObj) const
{
	snake* s = dynamic_cast<snake*>(newObj);
	if (s != nullptr)
	{
		if (endCellPos.GetCellNum() >= s->position.GetCellNum() && position.GetCellNum() <= s->endCellPos.GetCellNum())
		{
			return true;
		}
	}
	return false;
}

CellPosition snake::GetEndPosition() const
{
	return endCellPos;
}
void snake::Save(ofstream& OutFile)
{
	OutFile << "\n" + to_string(position.GetCellNum()) + " " + to_string(endCellPos.GetCellNum());
}

void snake::Load(ifstream& Infile)
{
}

snake::~snake()
{
}