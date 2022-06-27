#pragma once
#include "Card.h"
class CardTwo :
	public Card
{
	// CardTwo Parameters:
	int walletAmount; // the wallet value to increase to the player

public:
	CardTwo(const CellPosition& pos); // A Constructor takes card position
	void setwalletamount(int);

	virtual void ReadCardParameters(Grid* pGrid); // Reads the parameters of CardTwo which is: walletAmount

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardTwo on the passed Player
	virtual void Save(ofstream&OutFile,int type);
									  // by incrementing the player's wallet by the walletAmount data member
	virtual Card* copyparameters(CellPosition);
	virtual ~CardTwo(); // A Virtual Destructor
};

