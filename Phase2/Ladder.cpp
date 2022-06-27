#include "Ladder.h"

#include "Snake.h"
#include "Card.h"
#include<fstream>

Ladder::Ladder(const CellPosition & startCellPos, const CellPosition & endCellPos) : GameObject(startCellPos)
{
	this->endCellPos = endCellPos;

	///TODO: Do the needed validation
}

void Ladder::Draw(Output* pOut) const
{
	pOut->DrawLadder(position, endCellPos);
}

void Ladder::Apply(Grid* pGrid, Player* pPlayer) 
{


	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "You have reached a ladder. Click to continue ..." and wait mouse click
	pGrid->PrintErrorMessage("You have reached a ladder. Click to continue ...");
	// 2- Apply the ladder's effect by moving the player to the endCellPos
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

bool Ladder::overLapping(GameObject* pNew) const{
	Ladder* newLadder=dynamic_cast<Ladder*>(pNew);
	if(newLadder){
		if((newLadder->position.GetCellNum() >= this->position.GetCellNum()&& 
			newLadder->position.GetCellNum() <= this->endCellPos.GetCellNum()) 
			|| (newLadder->position.GetCellNum() <= this->position.GetCellNum()
			&& newLadder->endCellPos.GetCellNum() >= this->position.GetCellNum()))
			return true;
	}
	return false;
}

CellPosition Ladder::GetEndPosition() const
{
	return endCellPos;
}

void Ladder::Save(ofstream&OutFile,int type)
{
	if(type==1)
	{
		GameObject::Save(OutFile,type);
		int n=endCellPos.GetCellNum();
		OutFile<<n<<endl;
	}
	return;
}

Ladder::~Ladder()
{
}
