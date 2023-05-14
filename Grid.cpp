#include "Grid.h"

#include "Cell.h"
#include "GameObject.h"
#include "Ladder.h"
#include "Snake.h" //
#include "Card.h"
#include "Snake.h"	
#include "CardOne.h"	//
#include "CardTwo.h"	//
#include "CardThree.h"	//
#include "CardFour.h"	//
#include "CardFive.h"	//
#include "CardSix.h"	//
#include "CardSeven.h"  //
#include "Player.h"
#include <iostream>		//
#include <fstream>		//




Grid::Grid(Input* pIn, Output* pOut) : pIn(pIn), pOut(pOut) // Initializing pIn, pOut
{
	// Allocate the Cell Objects of the CellList
	for (int i = NumVerticalCells - 1; i >= 0; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CellList[i][j] = new Cell(i, j);
		}
	}

	// Allocate thePlayer Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		PlayerList[i] = new Player(CellList[NumVerticalCells - 1][0], i); // first cell
		PlayerList[i]->Draw(pOut); // initially draw players in the first cell
	}

	// Initialize currPlayerNumber with 0 (first player)
	currPlayerNumber = 0; // start with the first player

	// Initialize Clipboard with NULL
	Clipboard = NULL;

	// Initialize endGame with false
	endGame = false;
}


// ========= Adding or Removing GameObjects to Cells =========


bool Grid::AddObjectToCell(GameObject* pNewObject)  // think if any validation is needed
{
	// Get the cell position of pNewObject
	CellPosition pos = pNewObject->GetPosition();
	if (pos.IsValidCell()) // Check if valid position
	{
		// Get the previous GameObject of the Cell
		GameObject* pPrevObject = CellList[pos.VCell()][pos.HCell()]->GetGameObject();
		if (pPrevObject)  // the cell already contains a game object
			return false; // do NOT add and return false

		// Set the game object of the Cell with the new game object
		CellList[pos.VCell()][pos.HCell()]->SetGameObject(pNewObject);
		return true; // indicating that addition is done
	}
	return false; // if not a valid position
}


// Note: You may need to change the return type of this function (Think)
void Grid::RemoveObjectFromCell(const CellPosition& pos)
{
	if (pos.IsValidCell()) // Check if valid position
	{
		// Note: you can deallocate the object here before setting the pointer to null if it is needed
		delete CellList[pos.VCell()][pos.HCell()]->GetGameObject(); //
		CellList[pos.VCell()][pos.HCell()]->SetGameObject(NULL);
	}
}

void Grid::UpdatePlayerCell(Player* player, const CellPosition& newPosition)
{
	// Clear the player's circle from the old cell position
	player->ClearDrawing(pOut);

	// Set the player's CELL with the new position
	Cell* newCell = CellList[newPosition.VCell()][newPosition.HCell()];
	player->SetCell(newCell);

	// Draw the player's circle on the new cell position
	player->Draw(pOut);
}


// ========= Setters and Getters Functions =========


Input* Grid::GetInput() const
{
	return pIn;
}

Output* Grid::GetOutput() const
{
	return pOut;
}

void Grid::SetClipboard(Card* pCard) // to be used in copy/cut
{
	// you may update slightly in implementation if you want (but without breaking responsibilities)
	Clipboard = pCard;
}

Card* Grid::GetClipboard() const // to be used in paste
{
	return Clipboard;
}

void Grid::SetEndGame(bool endGame)
{
	this->endGame = endGame;
}

bool Grid::GetEndGame() const
{
	return endGame;
}

void Grid::AdvanceCurrentPlayer()
{
	currPlayerNumber = (currPlayerNumber + 1) % MaxPlayerCount; // this generates value from 0 to MaxPlayerCount - 1
}


//=================================================================================================
	// NEW ADDED functions

void Grid::SetCurretnPlayer(int x) //
{
	currPlayerNumber = x;
}

Player* Grid::GetNextPlayer(const CellPosition& position) ///
{
	int startH = position.HCell() + 1 % 11;
	for (int i = position.VCell(); i >= 0; i--)
	{
		for (int j = startH; j < NumHorizontalCells; j++)
		{
			for (int k = 0; k < MaxPlayerCount; k++)
			{
				if (PlayerList[k]->GetCell()->GetCellPosition().GetCellNum() == CellList[i][j]->GetCellPosition().GetCellNum()) {
					return PlayerList[k];
				}
			}
		}
		startH = 0;
	}
	return NULL;
}

Player* Grid::getPoorestPlayer() //
{
	int minimumCoins = 9999999999;
	Player* poorestPlayer;
	for (int i = 0; i < MaxPlayerCount; i++) {
		if (PlayerList[i]->GetWallet() < minimumCoins) {
			minimumCoins = PlayerList[i]->GetWallet();
			poorestPlayer = PlayerList[i];
		}
	}
	return poorestPlayer;
}

Cell* Grid::GetCellFromPosition(CellPosition cPos) //
{
	for (int i = 0; i < NumVerticalCells; i++)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			if (CellList[i][j]->GetCellPosition().HCell() == cPos.HCell()
				&& CellList[i][j]->GetCellPosition().VCell() == cPos.VCell())
			{
				return CellList[i][j];
			}
		}
	}
	return nullptr;
}

void Grid::SaveAll(ofstream& OutFile, GObjectsTypes Type) //
{
	if (Type == LADDER_TYPE) {
		// Count All Laders in the grid	
		int Laddercount = 0;
		for (int i = NumVerticalCells - 1; i >= 0; i--)
		{
			for (int j = 0; j < NumHorizontalCells; j++)
			{
				if (CellList[i][j]->HasLadder())
					Laddercount++;
			}
		}
		// Writes the ladders total in the file	
		OutFile << to_string(Laddercount);
		// Loops through all ladders and save its data	
		for (int i = NumVerticalCells - 1; i >= 0; i--)
		{
			for (int j = 0; j < NumHorizontalCells; j++)
			{
				if (CellList[i][j]->HasLadder())
					CellList[i][j]->GetGameObject()->Save(OutFile);
			}
		}
	}
	if (Type == SNAKE_TYPE) {
		int SnakeCount = 0;
		for (int i = NumVerticalCells - 1; i >= 0; i--)
		{
			for (int j = 0; j < NumHorizontalCells; j++)
			{
				if (CellList[i][j]->HasSnake())
					SnakeCount++;
			}
		}
		OutFile << "\n" + to_string(SnakeCount);
		for (int i = NumVerticalCells - 1; i >= 0; i--)
		{
			for (int j = 0; j < NumHorizontalCells; j++)
			{
				if (CellList[i][j]->HasSnake())
					CellList[i][j]->GetGameObject()->Save(OutFile);
			}
		}
	}
	if (Type == CARD_TYPE) {
		int Snakecount = 0;
		for (int i = NumVerticalCells - 1; i >= 0; i--)
		{
			for (int j = 0; j < NumHorizontalCells; j++)
			{
				if (CellList[i][j]->HasCard())
					Snakecount++;
			}
		}
		OutFile << "\n" + to_string(Snakecount);
		for (int i = NumVerticalCells - 1; i >= 0; i--)
		{
			for (int j = 0; j < NumHorizontalCells; j++)
			{
				if (CellList[i][j]->HasCard())
					CellList[i][j]->GetGameObject()->Save(OutFile);
			}
		}
	}
}

void Grid::LoadAll(ifstream& inFile, GObjectsTypes Type, int ObjectsCount) //
{
	if (Type == LADDER_TYPE) {
		for (int i = NumVerticalCells - 1; i >= 0; i--)
		{
			for (int j = 0; j < NumHorizontalCells; j++)
			{
				if (CellList[i][j]->HasLadder())
					this->RemoveObjectFromCell(CellList[i][j]->GetCellPosition());
			}
		}
		for (int j = 0; j < ObjectsCount; j++)
		{
			GameObject* newLadder = new Ladder(CellList[0][0]->GetCellPosition(), CellList[0][0]->GetCellPosition());
			newLadder->Load(inFile);
			this->AddObjectToCell(newLadder);
			this->UpdateInterface();
		}
	}
	if (Type == SNAKE_TYPE) {
		for (int i = NumVerticalCells - 1; i >= 0; i--)
		{
			for (int j = 0; j < NumHorizontalCells; j++)
			{
				if (CellList[i][j]->HasSnake())
					this->RemoveObjectFromCell(CellList[i][j]->GetCellPosition());
			}
		}
		for (int j = 0; j < ObjectsCount; j++)
		{
			GameObject* newsnake = new snake(CellList[0][0]->GetCellPosition(), CellList[0][0]->GetCellPosition());
			newsnake->Load(inFile);
			this->AddObjectToCell(newsnake);
			this->UpdateInterface();
		}
	}
	if (Type == CARD_TYPE) {
		for (int i = NumVerticalCells - 1; i >= 0; i--)
		{
			for (int j = 0; j < NumHorizontalCells; j++)
			{
				if (CellList[i][j]->HasCard())
					this->RemoveObjectFromCell(CellList[i][j]->GetCellPosition());
			}
		}
		for (int j = 0; j < ObjectsCount; j++)
		{
			string StringNumber = "";
			char inChar = inFile.get();
			while (inChar != '\n' && inChar != ' ' && !inFile.eof()) {
				StringNumber += inChar;
				inChar = inFile.get();
			}
			int cardNumber = stoi(StringNumber);
			GameObject* newCard = nullptr;
			switch (cardNumber)
			{
			case 1:
				newCard = new CardOne(CellList[0][0]->GetCellPosition());
				break;
			case 2:
				newCard = new CardTwo(CellList[0][0]->GetCellPosition());
				break;
			case 3:
				newCard = new CardThree(CellList[0][0]->GetCellPosition());
				break;
			case 4:
				newCard = new CardFour(CellList[0][0]->GetCellPosition());
				break;
			case 5:
				newCard = new CardFive(CellList[0][0]->GetCellPosition());
				break;
			case 6:
				newCard = new CardSix(CellList[0][0]->GetCellPosition());
				break;
			case 7:
				newCard = new CardSeven(CellList[0][0]->GetCellPosition());
				break;

			}
			if (newCard)
			{
				newCard->Load(inFile);
				this->AddObjectToCell(newCard);
				this->UpdateInterface();
			}
		}
	}
}

Ladder* Grid::CurrentCellLadder(const CellPosition& position)///
{
	Ladder* pladder;
	if (position.IsValidCell())
	{
		pladder = CellList[position.VCell()][position.HCell()]->HasLadder();
		return pladder;
	}
	else
	{
		pladder = NULL;
		return pladder;
	}
}

snake* Grid::CurrentCellSnake(const CellPosition& position) ///
{
	snake* pSnake;
	if (position.IsValidCell())
	{
		pSnake = CellList[position.VCell()][position.HCell()]->HasSnake();
		return pSnake;
	}
	else
	{
		pSnake = NULL;
		return pSnake;
	}
}

snake* Grid::GetNextSnake(const CellPosition& position) ///
{
	int startH = position.HCell(); // represents the start hCell in the current row to search for the snake in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{
			///DONETODO: Check if CellList[i][j] has a ladder, if yes return it

			snake* pSnake = CellList[i][j]->HasSnake();
			if (pSnake != NULL)
				return pSnake;


		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}

Card* Grid::CurrentCellCard(const CellPosition& position) ///
{
	Card* pCard;
	if (position.IsValidCell())
	{
		pCard = CellList[position.VCell()][position.HCell()]->HasCard();
		return pCard;
	}
	else
	{
		pCard = NULL;
		return pCard;
	}
}




//=================================================================================================

// ========= Other Getters =========


Player* Grid::GetCurrentPlayer() const
{
	return PlayerList[currPlayerNumber];
}

Ladder* Grid::GetNextLadder(const CellPosition& position)///
{

	int startH = position.HCell(); // represents the start hCell in the current row to search for the ladder in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{
			///DONETODO: Check if CellList[i][j] has a ladder, if yes return it

			Ladder* pladder = CellList[i][j]->HasLadder();
			if (pladder != NULL)
				return pladder;


		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}


// ========= User Interface Functions =========


void Grid::UpdateInterface() const
{
	if (UI.InterfaceMode == MODE_DESIGN)
	{
		// 1- Draw cells with or without cards 
		for (int i = NumVerticalCells - 1; i >= 0; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawCellOrCard(pOut);
			}
		}

		// 2- Draw other cell objects (ladders, snakes)
		for (int i = NumVerticalCells - 1; i >= 0; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawLadderOrSnake(pOut);
			}
		}

		// 3- Draw players
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->Draw(pOut);
		}
	}
	else // In PLAY Mode
	{
		// 1- Print Player's Info
		string playersInfo = "";
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->AppendPlayerInfo(playersInfo); // passed by reference
			if (i < MaxPlayerCount - 1) // except the last player
				playersInfo += ", ";
		}
		playersInfo += " | Curr = " + to_string(currPlayerNumber);

		pOut->PrintPlayersInfo(playersInfo);

		// Note: UpdatePlayerCell() function --> already update drawing players in Play Mode
		//       so we do NOT need draw all players again in UpdateInterface() of the Play mode
		// In addition, cards/snakes/ladders do NOT change positions in Play Mode, so need to draw them here too
	}
}

void Grid::PrintErrorMessage(string msg)
{
	pOut->PrintMessage(msg);
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
}


Grid::~Grid()
{
	delete pIn;
	delete pOut;

	// Deallocate the Cell Objects of the CellList
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			delete CellList[i][j];
		}
	}

	// Deallocate the Player Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		delete PlayerList[i];
	}
}