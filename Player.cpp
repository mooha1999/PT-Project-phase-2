#include "Player.h"
#include "Cell.h"
#include "Card.h"
#include "Ladder.h"
#include "Snake.h"
#include "GameObject.h"

Player* Player::lowPlayer = NULL;
int Player::MinWallet = 1000;
bool Player::end = false;
Player::Player(Cell* pCell, int playerNum) : stepCount(0), wallet(100), playerNum(playerNum)
{
	this->pCell = pCell;
	this->turnCount = 0;
	ExtraRollDiceCon = 0;
	// Make all the needed initialization or validations
}

// ====== Setters and Getters ======

int Player::getdiffClosestPlayer(Player* pPlayer) {
	int diff = -1;
	if (getstepCount() < pPlayer->getstepCount()) {
		diff = (pPlayer->getstepCount()) - (getstepCount());
	}
	return diff;
}

void Player::SetstepCount(int s) {
	stepCount = s;
}
int Player::getstepCount() const {
	return stepCount;
}

int Player::getjustrolleddicenumber() const {
	return justRolledDiceNum;
}

void Player::SetCell(Cell* cell)
{
	pCell = cell;
}

void Player::SetExtraRollDiceCon(int c)
{
	ExtraRollDiceCon = c;
}
int Player::getExtraRollDiceCon()
{
	return ExtraRollDiceCon;
}

void Player::setcard4affect(bool x) {
	card4affect = x;
}

bool Player::getcard4affect() const {
	return card4affect;
}

Cell* Player::GetCell() const
{
	return pCell;
}
void Player::SetTurnCount(int turn) {
	turnCount = turn > 0 ? turn : 0;
}
void Player::SetWallet(int wallet)
{
	this->wallet = wallet >= 0 ? wallet : 0;
	// Make any needed validations
	if (wallet < MinWallet) {
		MinWallet = wallet;
		lowPlayer = this;
	}
}

Player* Player::GetPlayerThatHasLowWallet() {
	return lowPlayer;
}

int Player::GetWallet() const
{
	return wallet;
}
void Player::setmoveability(bool x) {
	HasMoveAbility = x;
}
bool Player::getmoveability() {
	return HasMoveAbility;
}
int Player::GetTurnCount() const
{
	return turnCount;
}

// ====== Drawing Functions ======

void Player::Draw(Output* pOut) const
{
	color playerColor = UI.PlayerColors[playerNum];

	///TODO: use the appropriate output function to draw the player with "playerColor"
	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, playerColor);
}

void Player::ClearDrawing(Output* pOut) const
{
	color cellColor = pCell->HasCard() ? UI.CellColor_HasCard : UI.CellColor_NoCard;

	///TODO: use the appropriate output function to draw the player with "cellColor" (to clear it)
	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, cellColor);
}

// ====== Game Functions ======

void Player::Move(Grid* pGrid, int diceNumber)
{
	Output* pOut = pGrid->GetOutput();       //used the grid pointer to get input and output pointer
	Input* pin = pGrid->GetInput();
	Output* pout = pGrid->GetOutput();
	if (!end) {
		if (pGrid->GetEndGame()) {
			pOut->PrintMessage("Congratulations P" + to_string(playerNum) + " You Win!");
			int x, y;
			pin->GetPointClicked(x, y);
			pOut->ClearStatusBar();
			end = true;
			return;
		}
		if (getcard4affect()) {
			pOut->PrintMessage("P" + to_string(playerNum) + "You Will Be Prevented from Moving this Round!  Click to Continue...");
			int x, y;
			pin->GetPointClicked(x, y);
			pOut->ClearStatusBar();
			setcard4affect(false);
			turnCount++;
			return;
		}

		if (getmoveability()) {
			///TODO: Implement this function as mentioned in the guideline steps (numbered below) below

			// == Here are some guideline steps (numbered below) to implement this function ==

			// 1- Increment the turnCount because calling Move() means that the player has rolled the dice once
			turnCount++;
			// 2- Check the turnCount to know if the wallet recharge turn comes (recharge wallet instead of move)
			//    If yes, recharge wallet and reset the turnCount and return from the function (do NOT move)
			if (turnCount >= 3) {
				/*int x, y;
				pin->GetPointClicked(x, y);
				pOut->ClearStatusBar();*/
				SetWallet(GetWallet() + (diceNumber * 10));
				turnCount = 0;
				return;
			}
			if (GetWallet() == 0) {
				turnCount++;
				return;
			}
			// 3- Set the justRolledDiceNum with the passed diceNumber
			justRolledDiceNum = diceNumber;
			// 4- Get the player current cell position, say "pos", and add to it the diceNumber (update the position)
			//    Using the appropriate function of CellPosition class to update "pos"
			CellPosition currentPos = pCell->GetCellPosition();
			currentPos.AddCellNum(justRolledDiceNum);
			if (currentPos.HCell() == -1 && currentPos.VCell() == -1) {
				currentPos.SetHCell(10);
				currentPos.SetVCell(0);
			}
			// 5- Use pGrid->UpdatePlayerCell() func to Update player's cell POINTER (pCell) with the cell in the passed position, "pos" (the updated one)
			//    the importance of this function is that it Updates the pCell pointer of the player and Draws it in the new position
			pGrid->UpdatePlayerCell(this, currentPos);
			// 6- Apply() the game object of the reached cell (if any)
			GameObject* currentGameObject = GetCell()->GetGameObject();
			if (currentGameObject)
			{
				currentGameObject->Apply(pGrid, this);
			}
			// 7- Check if the player reached the end cell of the whole game, and if yes, Set end game with true: pGrid->SetEndGame(true)
			int currenCellNum = currentPos.GetCellNum();
			if (currenCellNum >= 99) {
				pGrid->SetEndGame(true);
			}
		}
	}
}

void Player::AppendPlayerInfo(string& playersInfo) const
{
	playersInfo += "P" + to_string(playerNum) + "(";
	playersInfo += to_string(wallet) + ", ";
	playersInfo += to_string(turnCount) + ")";
}