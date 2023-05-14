#include "CardSeven.h"
#include <iostream>
#include <fstream>

CardSeven::CardSeven(const CellPosition& pos) :Card(pos)
{
	cardNumber = 7;
}


void CardSeven::Apply(Grid* pGrid, Player* pPlayer)
{

	CellPosition Firstcell(8, 0);
	Card::Apply(pGrid, pPlayer);
	Cell* currentplayercell = pPlayer->GetCell();
	CellPosition currentplayercellpos = currentplayercell->GetCellPosition();
	Player* nextplayer = pGrid->GetNextPlayer(currentplayercellpos);
	if (nextplayer != NULL)
	{
		pGrid->UpdatePlayerCell(nextplayer, Firstcell);
		pGrid->PrintErrorMessage("The openent next to you is sent to start cell (click to continue ...)");
	}
	else {
		pGrid->PrintErrorMessage("There is no player in the lead!");
		return;
	}

}



CardSeven::~CardSeven()
{
}
