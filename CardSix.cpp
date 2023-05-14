#include "CardSix.h"

#include "Ladder.h"
#include "Snake.h"
CardSix::CardSix(const CellPosition& pos) : Card(pos)
{
	cardNumber = 6;

}

void CardSix::ReadCardParameters(Grid* pGrid)
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("click on the cell to go to a specific cell");
	SpecificCell = pIn->GetCellClicked();
	pOut->ClearStatusBar();

}
void CardSix::load(ifstream& Infile)
{

	{
		Infile >> cardNumber;

	}

}
void CardSix::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	pGrid->UpdatePlayerCell(pPlayer, SpecificCell);

	if (pPlayer->GetCell()->GetGameObject())
	{
		pPlayer->GetCell()->GetGameObject()->Apply(pGrid, pPlayer);
	}

}



void CardSix::Save(ofstream& OutFile)
{

	Card::Save(OutFile);

	OutFile << endl;
}

CardSix::~CardSix()
{

}