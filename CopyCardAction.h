#pragma once
#include "Action.h"
class CopyCardAction :public Action
{
public:


	CopyCardAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();


	virtual void Execute();


	~CopyCardAction();



};