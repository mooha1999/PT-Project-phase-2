#pragma once
#include "Action.h"
class Switchtodesignmode :public Action
{
public:

	Switchtodesignmode(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();


	virtual ~Switchtodesignmode();

};
