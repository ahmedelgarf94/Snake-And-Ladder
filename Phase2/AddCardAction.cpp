#include "AddCardAction.h"
#include"Grid.h"

#include "Input.h"
#include "Output.h"
#include "CardOne.h"
#include "CardTwo.h"
#include "CardThree.h"
#include "CardFour.h"
#include "CardFive.h"
#include "CardSix.h"
#include "CardSeven.h"
#include "CardEight.h"
#include "CardNine.h"
#include "CardTen.h"
#include "CardEleven.h"
#include "CardTwelve.h"
#include "CardThirteen.h"
#include "CardFourteen.h"

AddCardAction::AddCardAction(ApplicationManager *pApp) : Action(pApp)
{
	Grid *pGrid = pApp->GetGrid();
	Input *pIn = pGrid-> GetInput();
	Output *pOut = pGrid-> GetOutput();
	// Initializes the pManager pointer of Action with the passed pointer
}

AddCardAction::~AddCardAction()
{
}

void AddCardAction::ReadActionParameters() 
{	

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Get a Pointer to the Input / Output Interfaces    // DONE

	// 2- Read the "cardNumber" parameter and set its data member //Done

	// 3- Read the "cardPosition" parameter (its cell position) and set its data member //Done

	// 4- Make the needed validations on the read parameters //DONE 

	// 5- Clear status bar  //DONE

	Grid * pGrid = pManager->GetGrid();
	Input *pIn = pGrid-> GetInput();
	Output *pOut = pGrid-> GetOutput();

	pOut->PrintMessage("Enter Card Number: ");
	cardNumber= pIn->GetInteger(pOut);
	while (cardNumber<1 || cardNumber>14)
	{
		pGrid->PrintErrorMessage("Invalid Card Number");
		cardPosition= pIn->GetCellClicked();
		cardNumber = pIn->GetInteger(pOut);
	}

	pOut->PrintMessage("Choose the card position by pointing on a cell");
	cardPosition= pIn->GetCellClicked();
	while (!cardPosition.IsValidCell())
	{
		pGrid->PrintErrorMessage("Invalid Cell Position");
		cardPosition= pIn->GetCellClicked();
	}

	pOut->ClearStatusBar();
}

void AddCardAction::Execute() 
{


	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- The first line of any Action Execution is to read its parameter first

	// 2- Switch case on cardNumber data member and create the appropriate card object type //DONE
	ReadActionParameters();

	Card * pCard = NULL; // will point to the card object type
	//Grid * pGrid = pManager->GetGrid();
	//pGrid->AddObjectToCell(pCard);
	//Grid * pGrid = pManager->GetGrid(); 	
	switch (cardNumber)
	{
	case 1:
		pCard = new CardOne(cardPosition);
		break;

		// A- Add the remaining cases

	case 2:
		pCard = new CardTwo(cardPosition);
		break;

	case 3:
		pCard = new CardThree(cardPosition);
		break;

	case 4:
		pCard = new CardFour(cardPosition);
		break;

	case 5:
		pCard = new CardFive(cardPosition);
		break;

	case 6:
		pCard = new CardSix(cardPosition);
		break;

	case 7:
		pCard = new CardSeven(cardPosition);
		break;

	case 8:
		pCard = new CardEight(cardPosition);
		break;

	case 9:
		pCard = new CardNine(cardPosition);
		break;

	case 10:
		pCard = new CardTen(cardPosition);
		break;

	case 11:
		pCard = new CardEleven(cardPosition);
		break;

	case 12:
		pCard = new CardTwelve(cardPosition);
		break;

	case 13:
		pCard = new CardThirteen(cardPosition);
		break;

	case 14:
		pCard = new CardFourteen(cardPosition);
		break; 
	}

	// 3- if pCard is correctly set in the switch case (i.e. if pCard is pointing to an object -- NOT NULL) //DONE
	if (pCard)
	{
		Grid * pGrid = pManager->GetGrid();
		Output *pOut = pGrid-> GetOutput();

		pCard->ReadCardParameters(pGrid);

		// A- We get a pointer to the Grid from the ApplicationManager

		// B- Make the "pCard" reads its card parameters: ReadCardParameters(), It is virtual and depends on the card type

		// C- Add the card object to the GameObject of its Cell:

		// D- if the GameObject cannot be added in the Cell, Print the appropriate error message on statusbar

		bool answerOfAddOTC= pGrid->AddObjectToCell(pCard);
		if (answerOfAddOTC== false)
			pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
	}

	// Here, the card is created and added to the GameObject of its Cell, so we finished executing the AddCardAction

}