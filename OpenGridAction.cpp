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
	pOut->PrintMessage("Enter the fileName you would like to save to (i.e : \"test.txt\")");
	filename = pIn->GetSrting(pOut);
	pOut->ClearStatusBar();
}

void OpenGridAction::Execute()
{
	Action* pAct = NULL;
	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	ReadActionParameters();
	ifstream myfile;
	try {
		myfile.open(filename);
		// Loading Ladders	
		string StringNumber = "";
		char inChar = myfile.get();
		while (inChar != '\n' && inChar != ' ' && !myfile.eof()) {
			StringNumber += inChar;
			inChar = myfile.get();
		}
		int LaddersCount = stoi(StringNumber);
		pGrid->PrintErrorMessage("You Have " + StringNumber + " Ladders");
		pGrid->LoadAll(myfile, LADDER_TYPE, LaddersCount);
		// Loading Snakes	
		StringNumber = "";
		inChar = myfile.get();
		while (inChar != '\n' && inChar != ' ' && !myfile.eof()) {
			StringNumber += inChar;
			inChar = myfile.get();
		}
		int SnakesCount = stoi(StringNumber);
		pGrid->PrintErrorMessage("You Have " + StringNumber + " Snakes");
		pGrid->LoadAll(myfile, SNAKE_TYPE, SnakesCount);
		// Loading Cards	
		StringNumber = "";
		inChar = myfile.get();
		while (inChar != '\n' && inChar != ' ' && !myfile.eof()) {
			StringNumber += inChar;
			inChar = myfile.get();
		}
		int CardsCount = stoi(StringNumber);
		pGrid->PrintErrorMessage("You Have " + StringNumber + " Cards");
		pGrid->LoadAll(myfile, CARD_TYPE, CardsCount);
		pGrid->UpdateInterface();
	}
	catch (exception e) {
		pGrid->PrintErrorMessage("Failed to load to the file check the name (click to continue ...)");
	}
	pGrid->PrintErrorMessage("Loaded Successfully (click to continue ...)");
	myfile.close();
}

OpenGridAction::~OpenGridAction()
{
}
