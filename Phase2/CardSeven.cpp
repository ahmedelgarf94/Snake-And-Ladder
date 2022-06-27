#include "CardSeven.h"
#include "RollDiceAction.h"
#include <fstream>

CardSeven::CardSeven(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 7; // set the inherited cardNumber data member with the card number (1 here)
}

CardSeven::~CardSeven(void)
{
}

void CardSeven::ReadCardParameters(Grid* pGrid)
{

	Input* pin = pGrid->GetInput();
	Output* pout = pGrid->GetOutput();

	pout->PrintMessage("New CardSeven : ...");
	pout->ClearStatusBar();
}

void CardSeven::Apply(Grid* pGrid, Player* pPlayer)
{

	Card::Apply(pGrid, pPlayer);
	pGrid->notadvancecurrentplayer();
	


}
void CardSeven::Save(ofstream&Outfile,int type)
{
	if(type==3)
	{
	Outfile<<cardNumber<<" ";
	Card::Save(Outfile,type);
	Outfile<<" "<<endl;
	}
}
Card* CardSeven::copyparameters(CellPosition pos)
{
	Card* cp = new CardSeven(pos);
	return cp;

}
