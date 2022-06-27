#include "CutCardAction.h"

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

CutCardAction::CutCardAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

CutCardAction::~CutCardAction()
{
}

void CutCardAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	pOut->PrintMessage("click on the source cell");
	Cellpos = pIn->GetCellClicked();

	pOut->ClearStatusBar();
}


void CutCardAction::Execute()
{

	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	ReadActionParameters();



	Card* pCard = pGrid->hasacard(Cellpos);
	//Cell* pCell = pGrid->GetCell(Cellpos);
	//Card* CopyCard = pCell->HasCard();
	if (pCard)
	{
		//pCard = (Card*)(pCell->GetGameObject());
		pGrid->SetClipboard(pCard);
		pGrid->RemoveObjectFromCell(Cellpos);
	}

	else
	{
		pOut->PrintMessage("invalid this cell has no card,click to continue");
		return;
	}
	



}

