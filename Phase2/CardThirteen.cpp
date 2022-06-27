#include "CardThirteen.h"
#include <fstream>

CardThirteen::CardThirteen(const CellPosition & pos) : Card(pos)		//set the cell position of the card
{
	cardNumber = 13;		 //set the inherited cardNumber data member with the card number (12 here)
	size=0;				     //set size with 0
	pPlayerOwner=NULL;		 //set owner of the cell with Null and change it later on
}

CardThirteen::~CardThirteen(void)
{
}
void CardThirteen::setprice(int p)
{
	Price_Of_Cell=p;
}
void CardThirteen::setrent(int r)
{
	Rent=r;
}
void CardThirteen::ReadCardParameters(Grid * pGrid)
{
	Input *pIn = pGrid-> GetInput();
	Output *pOut = pGrid-> GetOutput();
    Added=false;
	int Cell_Of_Card13;
	for (int i=1; i<100;i++)
	{
		CellPosition Cell_Position(i);
		Card *pCard=pGrid->GetCardPointer(Cell_Position,13);      //return pointer on the card;
		if (pCard!=NULL)
		{
			Added=true;
			Cell_Of_Card13=i;
			break;
		}
	}
	if (Added)
	{
		CellPosition position(Cell_Of_Card13);
		CardThirteen *pCardThirteen=dynamic_cast<CardThirteen*>(pGrid->GetCardPointer(position,13));
		Price_Of_Cell=pCardThirteen->Price_Of_Cell;
		Rent=pCardThirteen->Rent;
	}
	else
	{

		pOut->PrintMessage("Enter The Price For The Cell: ");
		Price_Of_Cell= pIn->GetInteger(pOut);
		while (Price_Of_Cell<=0)
		{
			pGrid->PrintErrorMessage("Invalid Price! ");
			pOut->PrintMessage("Enter The Price For The Cell: ");
			Price_Of_Cell= pIn->GetInteger(pOut);
		}

		pOut->PrintMessage("Enter The Rent Of The Cell:  ");
		Rent= pIn->GetInteger(pOut);
		while (Rent<=0)
		{
			pGrid->PrintErrorMessage("Invalid Rent!");
			pOut->PrintMessage("Enter The Rent Of The Cell: ");
			Rent= pIn->GetInteger(pOut);
		}
	}
	pOut->ClearStatusBar();
}

void CardThirteen::EditParametersInCardThirteen(Grid*pGrid)
{
	Input *pIn = pGrid-> GetInput();
	Output *pOut = pGrid-> GetOutput();
	pOut->PrintMessage("Enter The Price For The Cell: ");
	int New_Price=pIn->GetInteger(pOut);
	pOut->PrintMessage("Enter The Rent Of The Cell: ");
	int New_Rent=pIn->GetInteger(pOut);
	Price_Of_Cell=New_Price;
	Rent=New_Rent;
	pOut->ClearStatusBar();
	for (int i=1; i<100;i++)
	{
		CellPosition Cell_Position(i);
		CardThirteen *pCardThirteen=dynamic_cast<CardThirteen*>(pGrid->GetCardPointer(Cell_Position,13));
	      //return pointer on the card;
		if (pCardThirteen!=NULL)
		{
			pCardThirteen->Price_Of_Cell=Price_Of_Cell;
			pCardThirteen->Rent;
		}
	}
}

void CardThirteen::Apply(Grid* pGrid, Player* pPlayer)
{
	if (pPlayerOwner==NULL)		//check if the cell has an owner or not
	{
		Card :: Apply(pGrid, pPlayer);
		Input *pIn = pGrid-> GetInput();
		Output *pOut = pGrid-> GetOutput();

		pOut->PrintMessage("Do You Want To Buy This Cell? (Y/N)    The Price:"+ to_string(Price_Of_Cell));
		string answer= pIn->GetSrting(pOut);
		while (answer !="Y" &&  answer != "N"  && answer != "y" && answer != "n") 
		{
			pOut->PrintMessage("Invalid Answer! Do you want to buy this cell? Y/N ");
			string *ans=&answer;
			*ans= pIn->GetSrting(pOut);
			pOut->ClearStatusBar();
		}
		if ( answer=="N" || answer== "n")
		{
			pOut->ClearStatusBar();
			return ;
		}
		if ( answer=="Y" || answer== "y")
		{
			int Player_Wallet= pPlayer->GetWallet();

			if(Player_Wallet>= Price_Of_Cell)
			{
				Player_Wallet= Player_Wallet - Price_Of_Cell;
				pPlayer->SetWallet(Player_Wallet);
				pPlayerOwner=pPlayer;
				//array that includes all the cells that contains card10
				int k=0;
				for (int i=1; i<100;i++)
				{
					CellPosition Cell_Position(i);
					int Clicked_Card_Number=0;
					bool ans= pGrid->IsThereACard(Cell_Position,Clicked_Card_Number);      //take a position and check for card 10(position,card number)

					if (ans==true && Clicked_Card_Number==13)
						size++;
				}
				if (size==0)
				{
					return;
				}
				else if (size!=0)
				{
					Array_Of_Cells= new CellPosition[size];

					for (int i=1; i<100;i++)
					{
						CellPosition Cell_Position(i);
						int Clicked_Card_Number=0;
						bool ans= pGrid-> IsThereACard(Cell_Position,Clicked_Card_Number);     //take a position and check for card 10(position,card number)

						if (ans==true && Clicked_Card_Number==13)
						{ Array_Of_Cells[k]=Cell_Position;
						k++;
						}
					}

				}
				//Make the owner owns all the cells that contain card 13

				for (int i=0; i<size; i++)
				{ Card* pCard;

				pCard= pGrid->GetCardPointer(Array_Of_Cells[i], 13);
				((CardThirteen*)pCard)->setPlayerOwner(pPlayerOwner);
				((CardThirteen*)pCard)->PassedArrayOfCells(Array_Of_Cells);
				}  
			}
		}
		else if (pPlayer->GetWallet()< Price_Of_Cell)
		{
			pGrid->PrintErrorMessage("You Don't Have Enough Money To Buy This Cell!");
			return;
		}
	}
	if(pPlayerOwner!=NULL)
	{ CollectingRent( pPlayer);
	return;
	}
} 



void CardThirteen :: setPlayerOwner(Player* pPlayer)
{
	pPlayerOwner= pPlayer;
}

void CardThirteen :: PassedArrayOfCells (CellPosition* &Cell_Position)
{
	Array_Of_Cells= Cell_Position;
}
void CardThirteen :: CollectingRent(Player* pPlayer)
{
	if (pPlayer != pPlayerOwner)
	{
		int Player_Wallet= pPlayer->GetWallet();
		Player_Wallet= Player_Wallet - Rent;
		pPlayer->SetWallet(Player_Wallet);		//Take rent from the players except the owner
		//Add the rent to the owner of the cells
		int Owner_Wallet= pPlayerOwner->GetWallet();
		Owner_Wallet= Owner_Wallet+Rent;
		pPlayerOwner->SetWallet(Owner_Wallet);
	}
}
Card* CardThirteen::copyparameters(CellPosition pos)
{
	Card* cp = new CardThirteen(pos);
	return cp;
}
void CardThirteen::Save(ofstream&Outfile,int type)
{
	if(type==3)
	{
	Outfile<<cardNumber<<" ";
	Card::Save(Outfile,type);
	Outfile<<" "<<Price_Of_Cell<<" "<<Rent<<endl;
	}
}