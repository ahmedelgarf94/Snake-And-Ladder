#include "CardEight.h"
#include <fstream>

CardEight::CardEight(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 8; // set the inherited cardNumber data member with the card number (8 here)
}

CardEight::~CardEight(void)
{
}

void CardEight::ReadCardParameters(Grid* pGrid)
{


	Input* pin = pGrid->GetInput();
	Output* pout = pGrid->GetOutput();

	pout->PrintMessage("New CardEight.");
	pout->ClearStatusBar();
}

void CardEight::Apply(Grid* pGrid, Player* pPlayer)
{

	Card::Apply(pGrid, pPlayer);
	pPlayer->SetNotAllowed(true);

}


Card* CardEight::copyparameters(CellPosition pos)
{
	Card* cp = new CardEight(pos);
	return cp;

}
void CardEight::Save(ofstream&Outfile,int type)
{
	if(type==3)
	{
	Outfile<<cardNumber<<" ";
	Card::Save(Outfile,type);
	Outfile<<" "<<endl;
	}
}