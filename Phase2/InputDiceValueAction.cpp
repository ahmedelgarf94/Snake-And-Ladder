#include "InputDiceValueAction.h"

#include "ApplicationManager.h"
#include "Grid.h"
#include "Player.h"
#include "Input.h"
#include "Output.h"


InputDiceValueAction::InputDiceValueAction(ApplicationManager *pApp) : Action(pApp)
{
}

void InputDiceValueAction::ReadActionParameters()
{
	// no parameters to read from user
}

void InputDiceValueAction::Execute()
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Check if the Game is ended (Use the GetEndGame() function of pGrid), if yes, make the appropriate action

	Grid *pGrid=pManager->GetGrid();
	if(pGrid->GetEndGame()){
		//pGrid->
		pGrid->GetOutput()->PrintMessage("Game is over!");
		return;
	}
	// -- If not ended, do the following --:
	else{
		// 2- Get dice value from user
		Input* pIn = pGrid->GetInput();
		Output* pOut = pGrid->GetOutput();
		pOut->PrintMessage("Input dice value: ");
		int diceNumber = pIn->GetInteger(pOut);
		while (diceNumber<0||diceNumber>6)
		{
			pOut->PrintMessage("Please enter a correct dice value within range: ");
			int*v=&diceNumber;
			*v= pIn->GetInteger(pOut);
			pOut->ClearStatusBar();
		}
		pOut->ClearStatusBar();
		// 3- Get the "current" player from pGrid
		Player *p=pGrid->GetCurrentPlayer();
		// 4- Move the currentPlayer using function Move of class player
		p->Move(pGrid,diceNumber);
		// 5- Advance the current player number of pGrid
		pGrid->AdvanceCurrentPlayer();
	}
}

InputDiceValueAction::~InputDiceValueAction()
{
}
