#include "AddLadderAction.h"

#include "Input.h"
#include "Output.h"
#include "Ladder.h"

AddLadderAction::AddLadderAction(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

AddLadderAction::~AddLadderAction()
{
}

void AddLadderAction::ReadActionParameters() 
{	
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the startPos parameter
	pOut->PrintMessage("New Ladder: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();

	// Read the endPos parameter
	pOut->PrintMessage("New Ladder: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();

	// Clear messages
	pOut->ClearStatusBar();

	///TODO: Make the needed validations on the read parameters
	if(startPos.IsValidCell()==false||endPos.IsValidCell()==false){
		pOut->PrintMessage("Check Ladder specifications!");
		return;
	}

	if(pGrid->gCell(endPos)->HasSnake()){
		pOut->PrintMessage("Ladder's end cell cannot be a start of another snake!");
		return;
	}
	if(pGrid->gCell(endPos)->HasLadder()){
		pOut->PrintMessage("Ladder's end cell cannot be a start of another ladder!");
		return;
	}
	if(startPos.HCell()!=endPos.HCell()){
		pOut->PrintMessage("End cell and start cell are not in the same column!");
		return;
	}
	if(startPos.VCell()<endPos.VCell()){
		pOut->PrintMessage("End cell of ladder cannot be smaller than start cell!");
		return;
	}
	Ladder * pLadder = new Ladder(startPos, endPos);
	if(pGrid->overLapping(pLadder)){
		pOut->PrintMessage("Two ladders cannot overlap!");
		return;
	}
}


// Execute the action
void AddLadderAction::Execute() 
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();

	// Create a Ladder object with the parameters read from the user
	Ladder * pLadder = new Ladder(startPos, endPos);

	if(startPos.IsValidCell()==false||endPos.IsValidCell()==false||startPos.HCell()!=endPos.HCell()||startPos.VCell()<endPos.VCell())
		return;

	Grid * pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager
	if(pGrid->gCell(endPos)->HasSnake()||pGrid->gCell(endPos)->HasLadder())
		return;

	if(pGrid->overLapping(pLadder))		
		return;
	// Add the card object to the GameObject of its Cell:
	bool added = pGrid->AddObjectToCell(pLadder);

	// if the GameObject cannot be added
	if (! added)
	{
		// Print an appropriate message
		pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
	}
	// Here, the ladder is created and added to the GameObject of its Cell, so we finished executing the AddLadderAction

}
