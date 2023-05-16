#include "SaveGridAction.h"
#include "Grid.h"
#include <fstream>

SaveGridAction::SaveGridAction(ApplicationManager* pApp) : Action(pApp)
{
}

void SaveGridAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	pOut->PrintMessage("Enter the fileName you would like to save to (i.e : \"test.txt\")");
	filename = pIn->GetSrting(pOut);
	pOut->ClearStatusBar();
}

void SaveGridAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	ReadActionParameters();
	try
	{
		ofstream myfile(filename);
		pGrid->SaveAll(myfile, LADDER_TYPE);
		pGrid->SaveAll(myfile, SNAKE_TYPE);
		pGrid->SaveAll(myfile, CARD_TYPE);
		myfile.close();
		pOut->PrintMessage("Grid Data Saved Successfully");
	}
	catch (const std::exception&)
	{
		pOut->PrintMessage("Could not open file \"" + filename + "\"");
	}
	//pGrid->calcnumberofobjects();
}

SaveGridAction::~SaveGridAction()
{
}