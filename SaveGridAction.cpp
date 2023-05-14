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
	ofstream myfile;
	filename = pIn->GetSrting(pOut);
	myfile.open(filename.c_str());
	if (myfile.is_open() == false)
	{
		ofstream data(filename.c_str());
	}
	//pGrid->calcnumberofobjects();
	pGrid->SaveAll(myfile, LADDER_TYPE);
	pGrid->SaveAll(myfile, LADDER_TYPE);
	pGrid->SaveAll(myfile, LADDER_TYPE);
	myfile.close();
	pOut->PrintMessage("Grid Data Saved Successfully");

}

SaveGridAction::~SaveGridAction()
{
}
