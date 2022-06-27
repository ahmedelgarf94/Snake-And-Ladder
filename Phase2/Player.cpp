#include "Player.h"

#include "Card.h"
#include "Ladder.h"
#include "Snake.h"
#include "GameObject.h"
#include "CardEight.h"

Player::Player(Cell * pCell, int playerNum) : stepCount(0), wallet(100), playerNum(playerNum)
{
	this->pCell = pCell;
	this->turnCount = 0;
	notAllowed=false;
	// Make all the needed initialization or validations
}

// ====== Setters and Getters ======

void Player::SetCell(Cell * cell)
{
	pCell = cell;
}

Cell* Player::GetCell() const
{
	return pCell;
}

void Player::SetWallet(int wallet)
{
	this->wallet = wallet;
	// Make any needed validations
}

int Player::GetWallet() const
{
	return wallet;
}

void Player::SetTurnCount(int t)
{
	turnCount=t;
}

int Player::GetTurnCount() const
{
	return turnCount;
}

int Player::GetjustRolledDiceNum() const
{
	return justRolledDiceNum;
}

int Player::GetPlayerNum() const
{
	return playerNum;
}

void Player::SetNotAllowed(bool b){
	notAllowed=(notAllowed==true||notAllowed==false)? notAllowed:false;
}

bool Player::GetNotAllowed(){
	return notAllowed;
}

// ====== Drawing Functions ======

void Player::Draw(Output* pOut) const
{
	color playerColor = UI.PlayerColors[playerNum];


	///TODO: use the appropriate output function to draw the player with "playerColor"
	pOut->DrawPlayer(pCell->GetCellPosition(),playerNum,playerColor);
}

void Player::ClearDrawing(Output* pOut) const
{
	color cellColor = pCell->HasCard() ? UI.CellColor_HasCard : UI.CellColor_NoCard;


	///TODO: use the appropriate output function to draw the player with "cellColor" (to clear it)
	pOut->DrawPlayer(pCell->GetCellPosition(),playerNum,cellColor);
}

// ====== Game Functions ======

void Player::Move(Grid * pGrid, int diceNumber)
{
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==


	// 1- Increment the turnCount because calling Move() means that the player has rolled the dice once
	if(pCell->HasCard()==NULL||dynamic_cast<CardEight*>(pCell->HasCard()))
	turnCount++;
	// 2- Check the turnCount to know if the wallet recharge turn comes (recharge wallet instead of move)
	//    If yes, recharge wallet and reset the turnCount and return from the function (do NOT move)
	if(turnCount==3){
		//pGrid->PrintErrorMessage("Do you want to use a special attack instead of attacking? (Yes, No): ");
		// if Yes-> special attack
		// if No -> wallet+=10*diceNumber;


		wallet+=10*diceNumber;
		turnCount=0;
		return;
	}
	if(this->GetWallet()<0){
		pGrid->PrintErrorMessage("P"+to_string(playerNum)+", you don't have enough money; wait few turns until you collect some!");
		return;
	}
	// 3- Set the justRolledDiceNum with the passed diceNumber
	justRolledDiceNum=diceNumber;
	// 4- Get the player current cell position, say "pos", and add to it the diceNumber (update the position)
	//    Using the appropriate function of CellPosition class to update "pos"
	CellPosition pos=pCell->GetCellPosition();
	int cell_no=pos.GetCellNumFromPosition(pos);
	if(cell_no+justRolledDiceNum>99){
		int needed=99-cell_no;
		string strneeded=to_string (needed);
		pGrid->PrintErrorMessage("You must get a dice value equals to "+strneeded);
		return;
	}
	cell_no+=justRolledDiceNum;
	pos=pos.GetCellPositionFromNum(cell_no);
	// 5- Use pGrid->UpdatePlayerCell() func to Update player's cell POINTER (pCell) with the cell in the passed position, "pos" (the updated one)
	//    the importance of this function is that it Updates the pCell pointer of the player and Draws it in the new position
	pGrid->UpdatePlayerCell(this ,pos);
	// 6- Apply() the game object of the reached cell (if any)
	if(this->pCell->HasCard()){
		if(justRolledDiceNum!=0){
			Card *c=(Card*)this->pCell->GetGameObject();
			c->Apply(pGrid,this);
		}
	}
	else if(this->pCell->HasLadder()){
		Ladder *l=(Ladder*)this->pCell->GetGameObject();
		l->Apply(pGrid,this);
	}
	else if(this->pCell->HasSnake()){
		Snake *s=(Snake*)this->pCell->GetGameObject();
		s->Apply(pGrid,this);
	}
	// 7- Check if the player reached the end cell of the whole game, and if yes, Set end game with true: pGrid->SetEndGame(true)
	if (cell_no==99){
		pGrid->SetEndGame(true);
	}
}

void Player::AppendPlayerInfo(string & playersInfo) const
{
	playersInfo += "P" + to_string(playerNum) + "(" ;
	if(wallet<0)
		playersInfo += to_string(0) + ", ";		//for -ve wallet
	else
		playersInfo += to_string(wallet) + ", ";
	playersInfo += to_string(turnCount) + ")";
}