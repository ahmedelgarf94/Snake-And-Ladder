#pragma once
#include "Action.h"
//Mario
class NewGameAction :public Action
{
	CellPosition cellpos;
public:
	NewGameAction(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters();

	virtual void Execute(); // Creates a new Card Object of the specific Card Number
							// and Reads the Parameters of This Card Number (if any)
							// then Sets this Card Object to GameObject Pointer of its Cell

	virtual ~NewGameAction(); // A Virtual Destructor

};