#include "RemoveAllObjectsAction.h"
#include"Grid.h"
#include "Input.h"
#include "Output.h"

RemoveAllObjectsAction::RemoveAllObjectsAction(ApplicationManager* pApp) : Action(pApp)
{
	Grid* pGrid = pApp->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	// Initializes the pManager pointer of Action with the passed pointer
}

RemoveAllObjectsAction::~RemoveAllObjectsAction()
{
}
void RemoveAllObjectsAction::ReadActionParameters()
{

}
void RemoveAllObjectsAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pGrid->newGame();
	pGrid->RemoveAllObjects();

}
