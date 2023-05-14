#include "Ladder.h"
#include "Player.h"
#include <fstream>

#include <iostream>
using namespace std;
Ladder::Ladder(const CellPosition& startCellPos, const CellPosition& endCellPos) : GameObject(startCellPos)
{
	if (startCellPos.IsValidCell()) {
		position = startCellPos;
	}

	if (endCellPos.IsValidCell()) {
		this->endCellPos = endCellPos;
	}
}

void Ladder::Draw(Output* pOut) const
{
	pOut->DrawLadder(position, endCellPos);
}

void Ladder::Apply(Grid* pGrid, Player* pPlayer)
{
	// 1- Print a message "You have reached a ladder. Click to continue ..." and wait mouse click
	pGrid->PrintErrorMessage("You have reached a ladder. Click to continue ...");
	// 2- Apply the ladder's effect by moving the player to the endCellPos

	pGrid->UpdatePlayerCell(pPlayer, endCellPos);
}

bool Ladder::IsOverLapping(GameObject* newObj) const
{
	Ladder* l = dynamic_cast<Ladder*>(newObj);
	if (l != nullptr)
	{
		if (endCellPos.GetCellNum() >= l->position.GetCellNum() && position.GetCellNum() <= l->endCellPos.GetCellNum())
		{
			return true;
		}
	}
	return false;
}

CellPosition Ladder::GetEndPosition() const
{
	return endCellPos;
}
void Ladder::Save(ofstream& OutFile)
{
	OutFile << "\n" + to_string(position.GetCellNum()) + " " + to_string(endCellPos.GetCellNum());
}

void Ladder::Load(ifstream& Infile)
{
}

Ladder::~Ladder()
{
}