#include "CardFive.h"
#include "Ladder.h"
#include "Snake.h"
#include <fstream>

CardFive::CardFive(const CellPosition & pos) : Card(pos)
{
	cardNumber = 5;
}

CardFive::~CardFive(void)
{
}

void CardFive::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);


	CellPosition pos=(pPlayer->GetCell())->GetCellPosition();
	/*if(cell_no+pPlayer->GetjustRolledDiceNum()>99){
		int needed=99-cell_no;
		pGrid->PrintErrorMessage("You must get a dice value equals to "+needed);
		return;
	}*/
	pos.AddCellNum(pPlayer->GetjustRolledDiceNum());
	pGrid->UpdatePlayerCell(pPlayer ,pos);

	Cell pCell(pos);
	if(pCell.HasCard()){
		Card *c=(Card*)pCell.GetGameObject();
		c->Apply(pGrid,pPlayer);
	}
	else if(pCell.HasLadder()){
		Ladder *l=(Ladder*)pCell.GetGameObject();
		l->Apply(pGrid,pPlayer);
	}
	else if(pCell.HasSnake()){
		Snake *s=(Snake*)pCell.GetGameObject();
		s->Apply(pGrid,pPlayer);
	}

}
Card* CardFive::copyparameters(CellPosition pos)
{

	Card* cp = new CardFive(pos);
	return cp;
}
void CardFive::Save(ofstream&Outfile,int type)
{
	if(type==3)
	{
	Outfile<<cardNumber<<" ";
	Card::Save(Outfile,type);
	Outfile<<" "<<endl;
	}
}