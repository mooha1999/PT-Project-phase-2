#include "AddLadderAction.h"

#include "Input.h"
#include "Output.h"
#include "Ladder.h"

AddLadderAction::AddLadderAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
	flag = 0;
}

AddLadderAction::~AddLadderAction()
{
}

void AddLadderAction::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("New Ladder: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();
	endPos = pIn->GetCellClicked();
	if (!startPos.IsValidCell())
	{
		pGrid->PrintErrorMessage("Invalid start cell. Please click on a valid cell.");
		flag = 1;
		return;
	}


	pOut->PrintMessage("New Ladder: Click on its End Cell ...");

	if (!endPos.IsValidCell())
	{
		pGrid->PrintErrorMessage("Invalid end cell. Please choose a valid cell.");
		flag = 1;
		return;
	}
	if (startPos.HCell() == 0 && startPos.VCell() == 8)
	{

		pGrid->PrintErrorMessage("start cell cannot be the first cell, Click to continue ...");
		flag = 1;
		return;
	}
	if (endPos.HCell() == 10 && endPos.VCell() == 0)
	{
		startPos.SetHCell(-1);
		startPos.SetVCell(-1);
		pGrid->PrintErrorMessage("end cell cannot be the last cell, CLick to continue ...");
		return;
	}


	if (startPos.GetCellNum() == endPos.GetCellNum())
	{
		pGrid->PrintErrorMessage("start and end cells are the same");
		flag = 1;
		return;
	}
	if (endPos.GetCellNum() < startPos.GetCellNum())
	{
		pGrid->PrintErrorMessage("Invalid ladder specification: the end cell must be strictly greater than the start cell");
		flag = 1;
		return;
	}

	if (startPos.HCell() != endPos.HCell())
	{
		pGrid->PrintErrorMessage("end cell and start cell are not in the same column");
		flag = 1;
		return;
	}

	GameObject* Lad = new Ladder(startPos, endPos);
	if (Lad->IsOverlapping(Lad))
	{
		pGrid->PrintErrorMessage("Two ladders cannot overlap");
		flag = 1;
		return;
	}


	// Clear messages
	pOut->ClearStatusBar();
}


// Execute the action
void AddLadderAction::Execute()
{

	ReadActionParameters();

	// Create a Ladder object with the parameters read from the user
	Ladder* pLadder = new Ladder(startPos, endPos);

	Grid* pGrid = pManager->GetGrid();
	if (flag) {
		pGrid->PrintErrorMessage("can't add ladder ...");
		return;
	}
	else
	{
		Ladder* pLadder = new Ladder(startPos, endPos);
		bool added = pGrid->AddObjectToCell(pLadder);
		if (!added)
		{
			pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
		}
	}
}




