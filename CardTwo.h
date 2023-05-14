#pragma once


#include "Grid.h"
#include "Cell.h"
#include "Card.h"

class CardTwo : public Card
{
private:

public:
	CardTwo(const CellPosition& pos);
	virtual void Apply(Grid* pGrid, Player* pPlayer);
	virtual ~CardTwo();

};

