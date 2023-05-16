#include "InputDiceValueAction.h"

#include "Grid.h"
#include "Player.h"

InputDiceValueAction::InputDiceValueAction(ApplicationManager* pApp) : Action(pApp)
{
}

void InputDiceValueAction::ReadActionParameters()
{
}

void InputDiceValueAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	if (pGrid->GetEndGame()) {
		pGrid->GetOutput()->PrintMessage("Game Ended");
		return;
	}
	pOut->PrintMessage("Input Dice Value (1-6)");
	int diceNumber = pIn->GetInteger(pOut);
	if (diceNumber < 1 || diceNumber > 6) {
		pOut->PrintMessage("Invalid Input(Click to continue)");
		int x, y;
		pIn->GetPointClicked(x, y);
		Execute();
		return;
	}
	pOut->ClearStatusBar();

	Player* player = pGrid->GetCurrentPlayer();
	player->Move(pGrid, diceNumber);
	if (player->getExtraRollDiceCon() == 0)
		pGrid->AdvanceCurrentPlayer();
	else {
		player->SetExtraRollDiceCon(0);
	}
	pGrid->UpdateInterface();
}

InputDiceValueAction::~InputDiceValueAction()
{
}