#include "CardTwo.h"
#include <fstream>
CardTwo::CardTwo(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 2; // set the inherited cardNumber data member with the card number (1 here)
}

CardTwo::~CardTwo(void)
{
}

void CardTwo::setwalletamount(int w)
{
	walletAmount=w;
}
void CardTwo::ReadCardParameters(Grid* pGrid)
{


	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==

	//Done
	// 1- Get a Pointer to the Input / Output Interfaces from the Grid
	Input* pin = pGrid->GetInput();
	Output* pout = pGrid->GetOutput();

	//Done
	// 2- Read an Integer from the user using the Input class and set the walletAmount parameter with it
	//    Don't forget to first print to a descriptive message to the user like:"New CardTwo: Enter its wallet amount ..."
	pout->PrintMessage("New CardTwo : Enter its wallet amount ...");
	int walletamount = pin->GetInteger(pout);

	walletAmount = (walletamount >= 0)?walletamount:0;

	// [ Note ]:
	// In CardTwo, the only parameter of CardTwo is the "walletAmount" value to increase to player
	// Card parameters are the inputs you need to take from the user in the time of adding the Card in the grid
	// to be able to perform his Apply() action
	//Done
	// 3- Clear the status bar
	pout->ClearStatusBar();
}

void CardTwo::Apply(Grid* pGrid, Player* pPlayer)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==

	// 1- Call Apply() of the base class Card to print the message that you reached this card number

	Card::Apply(pGrid, pPlayer);
	// 2- Increment the wallet of pPlayer by the walletAmount data member of CardOne

	int wallet = pPlayer->GetWallet();
	pPlayer->SetWallet(wallet += walletAmount);

}
Card* CardTwo::copyparameters(CellPosition pos)
{
	Card* cp = new CardTwo(pos);
	((CardTwo*)cp)->walletAmount = walletAmount;
	return cp;

}
void CardTwo::Save(ofstream&OutFile,int type)
{	if(type==3)
	{
	OutFile<<cardNumber<<" ";
	Card::Save(OutFile,type);
	OutFile<<" "<<walletAmount;
	OutFile<<" "<<endl;
	}
}