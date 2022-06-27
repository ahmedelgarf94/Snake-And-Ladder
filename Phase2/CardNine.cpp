#include "CardNine.h"
#include <fstream>

CardNine::CardNine(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 9; // set the inherited cardNumber data member with the card number (1 here)
}

CardNine::~CardNine(void)
{
}

void CardNine::setpassedcellnum(int p)
{
	passedcellnum=p;
}
void CardNine::ReadCardParameters(Grid* pGrid)
{


	Input* pin = pGrid->GetInput();
	Output* pout = pGrid->GetOutput();

	pout->PrintMessage("New CardNine : Enter cell number to go to ...");
	int newcellnum = pin->GetInteger(pout);
	passedcellnum = (newcellnum > 0) ? newcellnum : 0;
	

	pout->ClearStatusBar();
}

void CardNine::Apply(Grid* pGrid, Player* pPlayer)
{

	Card::Apply(pGrid, pPlayer);
	pGrid->UpdatePlayerCell(pPlayer,CellPosition::GetCellPositionFromNum(passedcellnum));
}
void CardNine::Save(ofstream&Outfile,int type)
{
	if(type==3)
	{
	Outfile<<cardNumber<<" ";
	Card::Save(Outfile,type);
	Outfile<<" "<<passedcellnum<<endl;
	}
}
Card* CardNine::copyparameters(CellPosition pos)
{
	Card* cp = new CardNine(pos);
	((CardNine*)cp)->passedcellnum = passedcellnum;
	return cp;

}
