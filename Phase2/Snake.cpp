#include "Snake.h"

#include "Ladder.h"
#include "Card.h"
#include<fstream>

Snake::Snake(const CellPosition & startCellPos, const CellPosition & endCellPos) : GameObject(startCellPos)
{
	this->endCellPos = endCellPos;

	///TODO: Do the needed validation
}

void Snake::Draw(Output* pOut) const
{
	pOut->DrawSnake(position, endCellPos);
}

void Snake::Apply(Grid* pGrid, Player* pPlayer) 
{


	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "You have reached a snake. Click to continue ..." and wait mouse click
	pGrid->PrintErrorMessage("You have reached a snake. Click to continue ...");
	// 2- Apply the snake's effect by moving the player to the endCellPos
	//    Review the "pGrid" functions and decide which function can be used for that
	pGrid->UpdatePlayerCell(pPlayer ,endCellPos);

	if(pPlayer->GetCell()->HasCard()){
		Card *c=(Card*)pPlayer->GetCell()->GetGameObject();
		c->Apply(pGrid,pPlayer);
	}
	else if(pPlayer->GetCell()->HasLadder()){
		Ladder *l=(Ladder*)pPlayer->GetCell()->GetGameObject();
		l->Apply(pGrid,pPlayer);
	}
	else if(pPlayer->GetCell()->HasSnake()){
		Snake *s=(Snake*)pPlayer->GetCell()->GetGameObject();
		s->Apply(pGrid,pPlayer);
	}


	if (CellPosition::GetCellNumFromPosition(endCellPos)==99){
		pGrid->SetEndGame(true);
	}
}

bool Snake::overLapping(GameObject* pNew) const{
	Snake* newSnake=dynamic_cast<Snake*>(pNew);
	if(newSnake){
		if((newSnake->position.GetCellNum() >= this->position.GetCellNum()&&
			newSnake->endCellPos.GetCellNum() < this->position.GetCellNum())
			|| (newSnake->position.GetCellNum() >= this->endCellPos.GetCellNum()
			&& newSnake->position.GetCellNum() <= this->position.GetCellNum()))
			return true;
	}
	return false;
}

CellPosition Snake::GetEndPosition() const
{
	return endCellPos;
}

void Snake::Save(ofstream&OutFile,int type)
{
	if(type==2)
	{
		GameObject::Save(OutFile,type);
		int n=endCellPos.GetCellNum();
		OutFile<<n<<endl;
	}
}

Snake::~Snake()
{
}
