#include "CardTwo.h"
#include "Ladder.h"

CardTwo::CardTwo(const CellPosition& pos) : Card(pos)
{
	cardNumber = 2;
}

void CardTwo::Apply(Grid* pGrid, Player* pPlayer)
{
	// Call the base class method to print a message that the card has been reached
	Card::Apply(pGrid, pPlayer);

	// Get the current position of the player
	CellPosition playerPos = pPlayer->GetCell()->GetCellPosition();

	// Get the next ladder ahead of the player's position
	Ladder* nextLadder = pGrid->GetNextLadder(playerPos);

	// If there is a ladder ahead, move the player to its end position and apply it
	if (nextLadder != nullptr)
	{
		pGrid->PrintErrorMessage("You will proceed to the next ladder ahead (click to continue ...)");
		pGrid->UpdatePlayerCell(pPlayer, nextLadder->GetEndPosition());
		nextLadder->Apply(pGrid, pPlayer);
	}
	else // If there is no ladder ahead, display an error message
	{
		pGrid->PrintErrorMessage("No ladder ahead (click to continue ...)");
	}
}

void CardTwo::Load(ifstream& Infile)
{
	Card::Load(Infile);
}

CardTwo::~CardTwo()
{
}