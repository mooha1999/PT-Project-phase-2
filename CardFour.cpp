#include "CardFour.h"

CardFour::CardFour(const CellPosition& pos) : Card(pos)
{
	cardNumber = 4;
}

void CardFour::ReadCardParameters(Grid* pGrid)
{
	// Card Four has no parameters to read
}

void CardFour::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);

	// Set the next turn prevention flag of the player
	pPlayer->setcard4affect(true);

	// Print a message to the status bar
	pGrid->PrintErrorMessage("You are prevented from rolling next turn. Click to continue ...");
}

void CardFour::Load(ifstream& Infile)
{
	Card::Load(Infile);
}

CardFour::~CardFour()
{
	// The destructor of the base class Card will be called automatically
}