#include "AddSnakeAction.h"

#include "Input.h"
#include "Output.h"
#include "Snake.h"

AddSnakeAction::AddSnakeAction(ApplicationManager* pApp) : Action(pApp)
{
	flag = 0;
}

AddSnakeAction::~AddSnakeAction()
{

}

void AddSnakeAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("New Snake: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();
	if (startPos.IsValidCell() == false) //operator overloading in cellPosition ?
	{
		pGrid->PrintErrorMessage("Invalid. Check Snake specification");
		flag = 1;
		return;
	}

	pOut->PrintMessage("New Snake: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();
	if (endPos.IsValidCell() == false) //operator overloading in cellPosition ?
	{
		pGrid->PrintErrorMessage("Invalid. Check ladder specification");
		flag = 1;
		return;
	}

	if (endPos.GetCellNum() > startPos.GetCellNum())
	{
		pGrid->PrintErrorMessage("end cell cannot be smaller than start cell");
		flag = 1;
		return;
	}
	else if (startPos.HCell() != endPos.HCell())
	{
		pGrid->PrintErrorMessage("end cell and start cell are not in the same column");
		flag = 1;
		return;
	}
	else if (endPos.VCell() == 0)
	{
		pGrid->PrintErrorMessage("End cell cannot be a start of another ladder or snake");
		flag = 1;
		return;
	}

	/*GameObject* S = new Snake(startPos, endPos);
	if (S->IsOverLapping(S))
	{
		pGrid->PrintErrorMessage("Two Snakes cannot overlap");
		flag = 1;
		return;
	}*/

	pOut->ClearStatusBar();
}



void AddSnakeAction::Execute()
{
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	if (flag != 0)
	{
		pGrid->PrintErrorMessage("Operation Cancelled ");
		return;
	}
	else
	{
		snake* psnake = new snake(startPos, endPos);
		bool added = pGrid->AddObjectToCell(psnake);
		if (!added)
		{
			pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
		}
	}
}
