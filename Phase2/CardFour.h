#pragma once

#include "Card.h"


class CardFour :	public Card
{
public:
	CardFour(const CellPosition & pos);
	virtual void Apply(Grid* pGrid, Player* pPlayer); 
	virtual Card* copyparameters(CellPosition);
	virtual void Save(ofstream&OutFile,int type);
	virtual ~CardFour();
};

