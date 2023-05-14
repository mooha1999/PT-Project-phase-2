#include "ApplicationManager.h"

#include "Grid.h"
#include "AddSnakeAction.h"	  //
#include "AddLadderAction.h"	
#include "AddCardAction.h"	
#include "CopyCardAction.h"	  //
#include "CutCardAction.h"	  //
#include "PasteCardAction.h"  //
#include "SaveGridAction.h"	  //
#include "OpenGridAction.h"	  //
#include "RollDiceAction.h"
#include "InputDiceValueAction.h"	//
#include "Switchtodesignmode.h"     //
#include "Switchtoplaymode.h"	    //
#include "DeleteGameObject.h"	//


///DONETODO: Add #include for all action types

ApplicationManager::ApplicationManager()
{
	// Create Input, output and Grid
	pOut = new Output();
	pIn = pOut->CreateInput();
	pGrid = new Grid(pIn, pOut);
}

////////////////////////////////////////////////////////////////////////////////////

ApplicationManager::~ApplicationManager()
{
	delete pGrid;
}

//==================================================================================//
//								Interface Management Functions						//
//==================================================================================//

Grid* ApplicationManager::GetGrid() const
{
	return pGrid;
}

void ApplicationManager::UpdateInterface() const
{
	pGrid->UpdateInterface();
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//

ActionType ApplicationManager::GetUserAction() const
{
	// Ask the input to get the action from the user.
	return pIn->GetUserAction();
}

////////////////////////////////////////////////////////////////////////////////////

// Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;

	// According to Action Type, create the corresponding action object
	switch (ActType)
	{
	case ADD_LADDER:
		pAct = new AddLadderAction(this);
		break;
	case ADD_SNAKE:
		pAct = new AddSnakeAction(this);
		break;
	case ADD_CARD:
		pAct = new AddCardAction(this);
		break;
	case COPY_CARD:
		pAct = new CopyCardAction(this);
		break;
	case CUT_CARD:
		pAct = new CutCardAction(this);
		break;
	case PASTE_CARD:
		pAct = new PasteCardAction(this);
		break;
	case DELETE_GAME_OBJECTS:
		pAct = new DeleteGameObject(this);
		break;
	case SAVE_GRID:
		pAct = new SaveGridAction(this);
		break;
	case OPEN_GRID:
		pAct = new OpenGridAction(this);
		break;
	case EXIT:
		break;
	case SWITCH_TO_PLAY_MODE:
		pAct = new Switchtoplaymode(this);
		break;
	case ROLL_DICE:
		pAct = new RollDiceAction(this);
		break;
	case INPUT_DICE_VALUE:
		pAct = new InputDiceValueAction(this);
		break;

	case SWITCH_TO_DESIGN_MODE:
		pAct = new Switchtodesignmode(this);
		break;
	case STATUS:	// a click on the status bar ==> no action	
		return;
	}

	// Execute the created action
	if (pAct != NULL)
	{
		pAct->Execute(); // Execute
		delete pAct;	 // Action is not needed any more after executing ==> delete it
		pAct = NULL;
	}
}
