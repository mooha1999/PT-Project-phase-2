#include "Card.h"

Card::Card(const CellPosition& pos) : GameObject(pos) // sets the cell position of the GameObject
{
}

void Card::SetCardNumber(int cnum)
{
	cardNumber = cnum; // needs validation
}

int Card::GetCardNumber()
{
	return cardNumber;
}

void Card::Draw(Output* pOut) const
{
	pOut->DrawCell(position, cardNumber);
}

void Card::ReadCardParameters(Grid* pGrid)
{
	// we should not make it pure virtual because some Cards doesn't have parameters
	// and if we make it pure virtual, that will make those Cards abstract classes
}

void Card::Apply(Grid* pGrid, Player* pPlayer)
{
	// As written below the "Roll Dice" action in the document ==> Check the Project Document
	// "If a player reaches a card of any other type", the following message should be printed then wait mouse click

	pGrid->PrintErrorMessage("You have reached card " + to_string(cardNumber) + ". Click to continue ...");
}

int Card::getinfo1()
{
	return 0;
}

void Card::setinfo1(int x)
{
}
void Card::Save(ofstream& OutFile)
{
	OutFile << "\n" + to_string(cardNumber) + " " + to_string(position.GetCellNum());
}

void Card::Load(ifstream& Infile)
{
	int startCell;
	Infile >> startCell;
	position = CellPosition(startCell);
}

Card::~Card()
{
}