#pragma once

#include "Card.h"


class CardSix :	public Card
{
public:
	CardSix(const CellPosition & pos);
	virtual void Apply(Grid* pGrid, Player* pPlayer); 
	virtual Card* copyparameters(CellPosition);
	virtual void Save(ofstream&OutFile,int type);
	virtual ~CardSix(); 
};

