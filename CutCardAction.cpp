#include "CutCardAction.h"
#include"Output.h"
#include"Input.h"
#include"Grid.h"





CutCardAction::CutCardAction(ApplicationManager* pApp) :Action(pApp)    //constructor
{

}

void CutCardAction::ReadActionParameters()
{
	//Reading action parameters
}

void CutCardAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();   //get a pointer Grid from App Manager

	Input* pIn = pGrid->GetInput();     //get a pointer Input from App Manager

	Output* pOut = pGrid->GetOutput();   //get a pointer Output from App Manager

	pOut->PrintMessage("Click on the source cell");

	CellPosition CellClick = pIn->GetCellClicked(); //the user will choose the cell 

	Card* CutCard = pGrid->CurrentCellCard(CellClick);

	if (CutCard != NULL)
	{
		pGrid->SetClipboard(CutCard);            //cuts a card with all its data to the clipboard
		pGrid->RemoveObjectFromCell(CellClick); //Removing the card from the source cell

	}
	else

		pGrid->PrintErrorMessage("The cell doesn't contain a card");   //The operation is cancelled


	pOut->ClearStatusBar();
}
CutCardAction::~CutCardAction()         //Destructor
{

}









