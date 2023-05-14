#include "CopyCardAction.h"
#include"Output.h"
#include"Input.h"
#include"Card.h"





CopyCardAction::CopyCardAction(ApplicationManager* pApp) :Action(pApp)  //constructor
{

}


void CopyCardAction::ReadActionParameters()
{
	//Reading action parameters
}

void CopyCardAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();           //a pointer grid from app manager

	Input* pIn = pGrid->GetInput();              //a pointer input from grid

	Output* pOut = pGrid->GetOutput();           //a pointer output from grid

	pOut->PrintMessage("Click on the source cell ");

	CellPosition CellClicked = pIn->GetCellClicked();  //make the user choose the cell

	Card* CopyCard = pGrid->CurrentCellCard(CellClicked);

	if (CopyCard != NULL)
	{
		pGrid->SetClipboard(CopyCard);      //Copy the card with all it's date to the clipboard
	}
	else
	{
		pGrid->PrintErrorMessage("The cell doesn't contain a card"); //this operation is canceled 
	}
	pOut->ClearStatusBar();                       //cleaning status bar
}


CopyCardAction::~CopyCardAction()            //destructor
{

}