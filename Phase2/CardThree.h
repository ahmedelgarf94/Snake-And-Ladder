#pragma once

#include "Card.h"


class CardThree :	public Card
{
public:
	CardThree(const CellPosition & pos);
	virtual void Apply(Grid* pGrid, Player* pPlayer); 
	virtual Card* copyparameters(CellPosition);
	virtual void Save(ofstream&OutFile,int type);

	virtual ~CardThree(); 
};

