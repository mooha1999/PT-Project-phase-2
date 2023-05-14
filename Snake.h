#pragma once

#include "GameObject.h"
class snake : public GameObject // inherited from GameObject
{
	//  "position" data member inherited from the GameObject class is used as the ladder's "Start Cell Position"

	CellPosition endCellPos; // here is the ladder's End Cell Position

public:

	snake(const CellPosition& startCellPos, const CellPosition& endCellPos); // A constructor for initialization

	virtual void Draw(Output* pOut) const; // Draws a ladder from its start cell to its end cell

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applys the effect of the ladder by moving player to ladder's end cell

	virtual void Load(ifstream& Infile);	// Loads and Reads the GameObject parameters from the file

	CellPosition GetEndPosition() const; // A getter for the endCellPos data member
	virtual bool IsOverLapping(GameObject* newObj) const;
	void Save(ofstream& file);

	virtual ~snake(); // Virtual destructor
};
