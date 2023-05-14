#pragma once
#include "Action.h"
class Switchtoplaymode : public Action
{
public:
	Switchtoplaymode(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	~Switchtoplaymode();



};
