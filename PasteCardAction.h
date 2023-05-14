#pragma once
#include "Action.h"
class PasteCardAction : public Action
{
private:
	Card* pCard;
	CellPosition* Position;
public:

	PasteCardAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();                    //pasts the copied card

	virtual ~PasteCardAction();


};

