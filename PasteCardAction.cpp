#include "PasteCardAction.h"
#include "Grid.h"
#include "Input.h"
#include "Output.h"
#include "Card.h"
#include "Grid.h"
#include "CardOne.h"
#include "CardTwo.h"
#include "CardThree.h"
#include "CardFour.h"
#include "CardFive.h"
#include "CardSix.h"
#include "CardSeven.h"

PasteCardAction::PasteCardAction(ApplicationManager* pApp) :Action(pApp)
{
}

void PasteCardAction::ReadActionParameters()
{
}

void PasteCardAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();           //a pointer grid from app manager

	Input* pIn = pGrid->GetInput();               //a pointer input from grid

	Output* pOut = pGrid->GetOutput();            //a poiter output from grid

	pOut->PrintMessage("Click on the destination cell");

	Card* pCard = pGrid->GetClipboard(); //a pointer card from grid that gets the clipboard

	if (pCard)
	{
		//gets the card number from the user

		int cardNumber = pCard->GetCardNumber();

		//Dynmaic allocation where position points to the cell position and gets the cell clicked by the user
		Position = new CellPosition(pIn->GetCellClicked());

		//Switch case on cardNumber data member and create the appropriate card object type
		switch (cardNumber)
		{
		case 1:
			pCard = new CardOne(*Position);
			pCard->ReadCardParameters(pGrid);
			break;

			// A- Add the remaining cases

		case 2:
			pCard = new CardTwo(*Position);
			break;

		case 3:
			pCard = new CardThree(*Position);
			break;

		case 4:
			pCard = new CardFour(*Position);
			break;

		case 5:
			pCard = new CardFive(*Position);
			break;

		case 6:
			pCard = new CardSix(*Position);
			pCard->ReadCardParameters(pGrid);
			break;

		case 7:
			pCard = new CardSeven(*Position);
			break;
		}
	}
	else
	{
		pGrid->PrintErrorMessage("Clipboard has no card to paste.");
		return;
	}
	//check if this position is valid or not
	if (Position->IsValidCell())
	{
		//pcard that points to the cards
		if (pCard)
		{
			//if added then cellposition is valid and can add an object to it
			bool added = (pGrid->AddObjectToCell(pCard));
			if (added)
				pCard->Draw(pOut);
			pOut->ClearStatusBar();
		}
		else
		{
			pOut->ClearStatusBar();
			return;
		}
	}
}

PasteCardAction::~PasteCardAction()
{
}