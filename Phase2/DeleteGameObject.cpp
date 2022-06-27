#include "DeleteGameObject.h"
#include"Grid.h"

DeleteGameObject::DeleteGameObject(ApplicationManager * pApp):Action(pApp)
{
	Grid* pGrid = pApp->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
}
DeleteGameObject::~DeleteGameObject()
{
}
void DeleteGameObject::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	pOut->PrintMessage("click to the object to delete");
    cellpos=pIn->GetCellClicked();

	pOut->ClearStatusBar();
}
void DeleteGameObject::Execute()
{
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	pGrid->RemoveObjectFromCell(cellpos);

}
