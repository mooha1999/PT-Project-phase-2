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
	int newCellPostion = pPlayer->GetCell()->GetCellPosition().GetCellNum() - lastroll;
	pGrid->UpdatePlayerCell(pPlayer, CellPosition(newCellPostion));
	//Check for other game objects
	if (pPlayer->GetCell()->GetGameObject())
	{
		pPlayer->GetCell()->GetGameObject()->Apply(pGrid, pPlayer);
	}
}
CardFive::~CardFive() {
}
void CardFive::Load(ifstream& Infile) {
	Card::Load(Infile);
}