#pragma once
#include "Action.h"
class DeleteGameObject :
	public Action
{
public:
	DeleteGameObject(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual ~DeleteGameObject();
};

