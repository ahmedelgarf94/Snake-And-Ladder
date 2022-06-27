#include "PasteCardAction.h"

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

PasteCardAction::PasteCardAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

PasteCardAction::~PasteCardAction()
{
}

void PasteCardAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	//if (cardPosition.IsValidCell() == false)
	//{
	//pOut->PrintMessage("invaild click on a cell");
	//return;
	//}

	//Card* pCard=pGrid->hasacard(cardPosition);
	//if (pCard)                        /////INCOMPLETEEE MISSING THE VALIDATION OF THERE IS A START OF LADDEROR SNAKE
	//{
	//return;
	//}



	pOut->ClearStatusBar();
	//Card *cardtopaste=pGrid->GetClipboard();


}

void PasteCardAction::Execute()
{


	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	ReadActionParameters();
	pOut->PrintMessage("click on the destination cell");
	CellPosition cardPosition = pIn->GetCellClicked();


	Card* pCard; // will point to the card object type

	pCard = pGrid->GetClipboard();     
	cardNumber = pCard->GetCardNumber();


	Card* cc=NULL;
	cc = pCard->copyparameters(cardPosition);


	bool hasobject = pGrid->AddObjectToCell(cc);                //creat a Card in this cell
	if (hasobject == false)
	{
		pGrid->PrintErrorMessage("This Cell has object");
	}

	pOut->ClearStatusBar();	
	// Here, the card is created and added to the GameObject of its Cell, so we finished executing the AddCardAction

}
