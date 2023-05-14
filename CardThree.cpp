#include "CardThree.h"
#include <iostream>
#include <fstream>

CardThree::CardThree(const CellPosition& pos) :Card(pos)
{
	cardNumber = 3;
}


void CardThree::ReadCardParameters(Grid* pGrid)
{

}


void CardThree::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	// Set the ExtraRollDiceCon parameter of the player to 1
	pPlayer->SetExtraRollDiceCon(1);
	// Print a message to inform the player to roll again
	pGrid->PrintErrorMessage("You got an extra roll, click to continue ...");
}


CardThree::~CardThree()
{
}

