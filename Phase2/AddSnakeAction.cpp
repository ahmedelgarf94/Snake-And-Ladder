#include "AddSnakeAction.h"

#include "Input.h"
#include "Output.h"
#include "Snake.h"

AddSnakeAction::AddSnakeAction(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

AddSnakeAction::~AddSnakeAction()
{
}

void AddSnakeAction::ReadActionParameters() 
{	
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the startPos parameter
	pOut->PrintMessage("New Snake: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();

	// Read the endPos parameter
	pOut->PrintMessage("New Snake: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();

	// Clear messages
	pOut->ClearStatusBar();

	///TODO: Make the needed validations on the read parameters
	if(startPos.IsValidCell()==false||endPos.IsValidCell()==false){
		pOut->PrintMessage("Check Snake specifications!");
		return;
	}

	if(pGrid->gCell(endPos)->HasSnake()){
		pOut->PrintMessage("Snake's end cell cannot be a start of another snake!");
		return;
	}
	if(pGrid->gCell(endPos)->HasLadder()){
		pOut->PrintMessage("Snake's end cell cannot be a start of another ladder!");
		return;
	}
	if(startPos.HCell()!=endPos.HCell()){
		pOut->PrintMessage("End cell and start cell are not in the same column!");
		return;
	}
	if(startPos.VCell()>endPos.VCell()){
		pOut->PrintMessage("End cell of snake must be smaller than start cell!");
		return;
	}
	Snake * pSnake = new Snake(startPos, endPos);
	if(pGrid->overLapping(pSnake)){
		pOut->PrintMessage("Two snakes cannot overlap!");
		return;
	}
}


// Execute the action
void AddSnakeAction::Execute() 
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();

	// Create a Snake object with the parameters read from the user
	Snake * sSnake = new Snake(startPos, endPos);

	if(startPos.IsValidCell()==false||endPos.IsValidCell()==false||startPos.HCell()!=endPos.HCell()||startPos.VCell()>endPos.VCell())
		return;

	Grid * pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager
	if(pGrid->gCell(endPos)->HasSnake()||pGrid->gCell(endPos)->HasLadder())
		return;
	if(pGrid->overLapping(sSnake))
		return;
	// Add the card object to the GameObject of its Cell:
	bool added = pGrid->AddObjectToCell(sSnake);

	// if the GameObject cannot be added
	if (! added)
	{
		// Print an appropriate message
		pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
	}
	// Here, the snake is created and added to the GameObject of its Cell, so we finished executing the AddSnakeAction

}
