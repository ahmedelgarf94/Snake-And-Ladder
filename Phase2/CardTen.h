#pragma once

#include "Card.h"

// [ CardOne ] Summary:
// Its Apply() Function: Decrements the value of the passing player’s wallet by a value
// Its Parameters: The Wallet Value to decrease --> put it as a "data member" and read it in ReadCardParameters()

class CardTen :	public Card
{
	int Price_Of_Cell;
	int Rent;
	
	int size;
	CellPosition* Array_Of_Cells;

	Player* pPlayerOwner;
	bool Added;

public:
	CardTen(const CellPosition & pos); // A Constructor takes card position
	void setprice(int);
	void setrent(int);
	virtual void ReadCardParameters(Grid * pGrid); // Reads the parameters of CardOne which is: walletAmount

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardOne on the passed Player
	                                                  // by decrementing the player's wallet by the walletAmount data member
	void CollectingRent(Player* pPlayerpaying);
	virtual ~CardTen(); // A Virtual Destructor

	
	void PassedArrayOfCells (CellPosition *&Cell_Position);
	void EditParametersInCardTen(Grid*pGrid);
	void setPlayerOwner(Player* pPlayer);
	virtual Card* copyparameters(CellPosition);
	virtual void Save(ofstream&OutFile,int type);

};

