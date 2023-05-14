#pragma once
#include "Action.h"

class AddSnakeAction :public Action
{
	CellPosition startPos;
	CellPosition endPos;
	int flag;

public:
	AddSnakeAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual ~AddSnakeAction();
};