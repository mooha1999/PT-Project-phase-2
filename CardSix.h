#pragma once
#include "Card.h"
class CardSix : public Card
{
private:

	CellPosition SpecificCell;

public:

	CardSix(const CellPosition& pos);

	void ReadCardParameters(Grid* pGrid);

	void Apply(Grid* pGrid, Player* pPlayer);

	virtual void Save(ofstream& OutFile);
	virtual void Load(ifstream& Infile);
	~CardSix();
};
