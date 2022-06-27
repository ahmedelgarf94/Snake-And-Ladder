#include "CardFour.h"
#include "Snake.h"
#include <fstream>

CardFour::CardFour(const CellPosition & pos) : Card(pos)
{
	cardNumber = 4;
}

CardFour::~CardFour(void)
{
}

void CardFour::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);

	if(pGrid->GetNextSnake((pPlayer->GetCell())->GetCellPosition()))
	{
		Snake* pSnake = pGrid->GetNextSnake((pPlayer->GetCell())->GetCellPosition());
		CellPosition pos = pSnake->GetPosition();
		pGrid->UpdatePlayerCell(pPlayer,pos);
		pSnake->Apply(pGrid,pPlayer);
	}
	else
	{
		pGrid->PrintErrorMessage("No snakes ahead!");
	}
}
void CardFour::Save(ofstream&Outfile,int type)
{
	if(type==3)
	{
	Outfile<<cardNumber<<" ";
	Card::Save(Outfile,type);
	Outfile<<" "<<endl;
	}
}
Card* CardFour::copyparameters(CellPosition pos)
{
	Card* cp = new CardFour(pos);
	return cp;
}