#include "OpenGridAction.h"
#include "Grid.h"
#include <fstream>
OpenGridAction::OpenGridAction(ApplicationManager* pApp) : Action(pApp)
{
}

void OpenGridAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	pOut->PrintMessage("Enter the fileName you would like to load from(i.e : \"test.txt\")");
	filename = pIn->GetSrting(pOut);
	pOut->ClearStatusBar();
}

void OpenGridAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	ReadActionParameters();
	try {
		ifstream myfile(filename);
		// Loading Ladders
		int LaddersCount;
		myfile >> LaddersCount;
		pGrid->PrintErrorMessage("You Have " + to_string(LaddersCount) + " Ladders");
		pGrid->LoadAll(myfile, LADDER_TYPE, LaddersCount);
		// Loading Snakes
		int SnakesCount;
		myfile >> SnakesCount;
		pGrid->PrintErrorMessage("You Have " + to_string(SnakesCount) + " Snakes");
		pGrid->LoadAll(myfile, SNAKE_TYPE, SnakesCount);
		// Loading Cards
		int CardsCount;
		myfile >> CardsCount;
		pGrid->PrintErrorMessage("You Have " + to_string(CardsCount) + " Cards");
		pGrid->LoadAll(myfile, CARD_TYPE, CardsCount);
		// Remaining operations
		pGrid->UpdateInterface();
		pGrid->PrintErrorMessage("Loaded Successfully (click to continue ...)");
		myfile.close();
	}
	catch (exception e) {
		pGrid->PrintErrorMessage("Failed to load to the file check the name (click to continue ...)");
	}
}

OpenGridAction::~OpenGridAction()
{
}