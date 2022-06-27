#include"SaveGridAction.h"
#include"Output.h"
#include"Grid.h"
#include<fstream>
using namespace std;
SaveGridAction::SaveGridAction(ApplicationManager*pApp)
	:Action(pApp)
{

}
void SaveGridAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("Enter File Name...");
	name=pIn->GetSrting(pOut);
	pOut->ClearStatusBar();
}

void SaveGridAction::Execute()
{
	Grid*pGrid=pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	ReadActionParameters();
	name=name + ".txt";
	int ladders=pGrid->GetNumOfLadders();
	int snakes=pGrid->GetNumOfSnakes();
	int cards=pGrid->GetNumOfCards();

	ofstream outFile(name,ios::out);
	outFile<<ladders<<endl;
	pGrid->SaveAll(outFile,1);
	outFile<<snakes<<endl;
	pGrid->SaveAll(outFile,2);
	outFile<<cards<<endl;
	pGrid->SaveAll(outFile,3);

}

SaveGridAction::~SaveGridAction()
{

}