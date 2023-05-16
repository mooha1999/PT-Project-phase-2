#pragma once

#include "Card.h"

class CardFour : public Card
{
private:

public:
	CardFour(const CellPosition& pos);

	virtual void ReadCardParameters(Grid* pGrid);

	virtual void Apply(Grid* pGrid, Player* pPlayer);

	virtual void Load(ifstream& Infile);

	virtual ~CardFour();
};
