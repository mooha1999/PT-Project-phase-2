#include "CardOne.h"

CardOne::CardOne(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 1; // set the inherited cardNumber data member with the card number (1 here)
}

CardOne::~CardOne(void)
{
}

void CardOne::ReadCardParameters(Grid* pGrid)
{
	// Get the output interface to print messages and the input interface to get data from user
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Ask the user for the wallet amount of card one
	pOut->PrintMessage("Enter the wallet amount for Card One: ");
	walletAmount = pIn->GetInteger(pOut);

	// Clear the status bar after getting input
	pOut->ClearStatusBar();
}


void CardOne::Apply(Grid* pGrid, Player* pPlayer)
{
	// Call Apply() of the base class Card to print the message that you reached this card number
	Card::Apply(pGrid, pPlayer);

	// Decrement the wallet of pPlayer by the walletAmount data member of CardOne
	int newWallet = pPlayer->GetWallet() - walletAmount;
	pPlayer->SetWallet(newWallet);

}
