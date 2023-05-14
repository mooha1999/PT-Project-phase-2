#include "DeleteGameObject.h"
#include "Grid.h"	
#include "Output.h"	
#include "Input.h"	

DeleteGameObject::DeleteGameObject(ApplicationManager* pApp) :Action(pApp)
{
}

void DeleteGameObject::ReadActionParameters()
{
}

void DeleteGameObject::Execute()
{
	int x, y;
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	pOut->PrintMessage("Select game object to delete, Click on the desired cell...");
	Input* pIn = pGrid->GetInput();

	CellPosition pCellpos = pIn->GetCellClicked();
	pGrid->RemoveObjectFromCell(pCellpos);
	pGrid->GetOutput()->PrintMessage("Object Deleted. Click to continue");
	pGrid->GetInput()->GetPointClicked(x, y);
	pGrid->GetOutput()->ClearStatusBar();
	pGrid->UpdateInterface();
}

DeleteGameObject::~DeleteGameObject()
{
}
