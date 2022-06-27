#pragma once
#include "Card.h"
class CardEight :
	public Card
{
public:
	CardEight(const CellPosition& pos); // 

	virtual void ReadCardParameters(Grid* pGrid);

	virtual void Apply(Grid* pGrid, Player* pPlayer);
	virtual Card* copyparameters(CellPosition);
	virtual void Save(ofstream&OutFile,int type);
	virtual ~CardEight();

};

