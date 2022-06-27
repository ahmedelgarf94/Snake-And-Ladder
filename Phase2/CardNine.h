#pragma once
#include "Card.h"
class CardNine :
	public Card
{
	int passedcellnum;
public:
	CardNine(const CellPosition& pos);
		void setpassedcellnum(int w);

	virtual void ReadCardParameters(Grid* pGrid); 

	virtual void Apply(Grid* pGrid, Player* pPlayer);
	virtual Card* copyparameters(CellPosition);
	virtual void Save(ofstream&OutFile,int type);
	~CardNine(void);
};

