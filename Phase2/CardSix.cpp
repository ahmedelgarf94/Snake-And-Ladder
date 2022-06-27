#include "CardSix.h"
#include "Ladder.h"
#include "Snake.h"
#include <fstream>
CardSix::CardSix(const CellPosition & pos) : Card(pos)
{
	cardNumber = 6;
}

CardSix::~CardSix(void)
{
}

void CardSix::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);

	CellPosition pos=(pPlayer->GetCell())->GetCellPosition();
	pos.AddCellNum(-pPlayer->GetjustRolledDiceNum());
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
void CardSix::Save(ofstream&Outfile,int type)
{
	if(type==3)
	{
	Outfile<<cardNumber<<" ";
	Card::Save(Outfile,type);
	Outfile<<" "<<endl;
	}
}
Card* CardSix::copyparameters(CellPosition pos)
{
	Card* cp = new CardSix(pos);
	return cp;

}