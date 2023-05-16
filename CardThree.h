#pragma once

#include "Card.h"

class CardThree : public Card
{
private:

public:
	CardThree(const CellPosition& pos);

	virtual void ReadCardParameters(Grid* pGrid);

	virtual void Apply(Grid* pGrid, Player* pPlayer);

	virtual void Load(ifstream& Infile);

	virtual ~CardThree();
};
