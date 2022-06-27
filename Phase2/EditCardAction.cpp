#include "EditCardAction.h"
#include"Grid.h"
#include"Card.h"
#include"CardTen.h"
#include"CardEleven.h"
#include"CardTwelve.h"
#include"CardThirteen.h"
#include"CardFourteen.h"
EditCardAction::EditCardAction(ApplicationManager* pApp):Action(pApp)
{
	pCard = NULL;
}

 void EditCardAction::ReadActionParameters() 
{
	 Grid* pGrid = pManager->GetGrid();
	 Output* pOut = pGrid->GetOutput();
	 Input* pIn = pGrid->GetInput();
	 pOut->PrintMessage("Edit Card: Click on source to Edit... ");
	 cardPosition = pIn->GetCellClicked();

	 if (!cardPosition.IsValidCell())
	 {
		 pGrid->PrintErrorMessage("Invalid Cell Position");

	 }
	 pGrid->EditableCard(pCard, cardPosition);
	 
	 if (pCard == NULL)
	 {
		 pGrid->PrintErrorMessage("The Source has no Card to edit");
	 }
	 else
	 {
		 CardNumber = pCard->GetCardNumber();
		 if (CardNumber >= 3 && CardNumber <= 8)
		 {
			 pGrid->PrintErrorMessage("Error ! Uneditable Card...");
			 pCard = NULL;
		 }
	 }
} 
void EditCardAction::Execute() {
	Grid* pGrid = pManager->GetGrid();

	ReadActionParameters();
	if (pCard)
	{
		if (CardNumber==10)
		{
			CardTen *EditCard=dynamic_cast<CardTen*>(pCard);
			EditCard->EditParametersInCardTen(pGrid);
		}
		else if (CardNumber==11)
		{
			CardEleven *EditCard=dynamic_cast<CardEleven*>(pCard);
			EditCard->EditParametersInCardEleven(pGrid);
		}
		else if (CardNumber==12)
		{
			CardTwelve *EditCard=dynamic_cast<CardTwelve*>(pCard);
            EditCard->EditParametersInCardTwelve(pGrid);
		}
		else if (CardNumber==13)
		{
			CardThirteen *EditCard=dynamic_cast<CardThirteen*>(pCard);
            EditCard->EditParametersInCardThirteen(pGrid);
		}
		else if (CardNumber==14)
		{
			CardFourteen *EditCard=dynamic_cast<CardFourteen*>(pCard);
            EditCard->EditParametersInCardFourteen(pGrid);
		}
		else
		{
			pCard->ReadCardParameters(pGrid);
		}	
	}

}

EditCardAction::~EditCardAction(){
 
 }