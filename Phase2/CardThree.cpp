#include "CardThree.h"
#include "Ladder.h"
#include <fstream>

CardThree::CardThree(const CellPosition & pos) : Card(pos)
{
	cardNumber = 3;
}

CardThree::~CardThree(void)
{
}

void CardThree::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	if(pGrid->GetNextLadder((pPlayer->GetCell())->GetCellPosition()))
	{
	Ladder* pLadder = pGrid->GetNextLadder((pPlayer->GetCell())->GetCellPosition());
	CellPosition pos = pLadder->GetPosition();
		
	pGrid->UpdatePlayerCell(pPlayer,pos);	
	pLadder->Apply(pGrid,pPlayer);
	}
	else
	{
		pGrid->PrintErrorMessage("No ladders ahead!");
	}
}
void CardThree::Save(ofstream&Outfile,int type)
{
	if(type==3)
	{
	Outfile<<cardNumber<<" ";
	Card::Save(Outfile,type);
	Outfile<<" "<<endl;
	}
}
Card* CardThree::copyparameters(CellPosition pos)
{

	Card* cp = new CardThree(pos);
	return cp;

}
