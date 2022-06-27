#include "NewGameAction.h"
#include"Grid.h"
//Mario
NewGameAction::NewGameAction(ApplicationManager * pApp):Action(pApp)
{
	Grid* pGrid = pApp->GetGrid();
	Output* pOut = pGrid->GetOutput();
}

void NewGameAction::ReadActionParameters()
{
	// no parameters to read from user
}

void NewGameAction::Execute(){
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	pGrid->newGame();
	pGrid->SetEndGame(false);
}

NewGameAction::~NewGameAction()
{
}