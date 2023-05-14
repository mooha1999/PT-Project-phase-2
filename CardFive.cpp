#include "CardFive.h"


CardFive::CardFive(const CellPosition& pos) : Card(pos)
{
	cardNumber = 5;

}
void CardFive::ReadCardParameters(Grid* pGrid) {

}
void CardFive::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	int lastroll = pPlayer->getjustrolleddicenumber();
	pPlayer->Move(pGrid, -lastroll);
}
CardFive::~CardFive() {

}
void CardFive::load(ifstream& Infile) {

	{
		Infile >> cardNumber;

	}

}


