#include"LoadGridAction.h"
#include"Input.h"
#include"Output.h"
#include"Grid.h"
#include"ApplicationManager.h"
#include"Cell.h"
#include"Card.h"
#include "CardOne.h"
#include "CardTwo.h"
#include "CardThree.h"
#include "CardFour.h"
#include "CardFive.h"
#include "CardSix.h"
#include "CardSeven.h"
#include "CardEight.h"
#include "CardNine.h"
#include"CardTen.h"
#include "CardEleven.h"
#include "CardTwelve.h"
#include "CardThirteen.h"
#include "CardFourteen.h"
#include"Ladder.h"
#include"Snake.h"
#include<fstream>

using namespace std;

LoadGridAction::LoadGridAction(ApplicationManager*pApp)
	:Action(pApp)
{

}

LoadGridAction::~LoadGridAction()
{

}
void LoadGridAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("Enter File Name...");
	name=pIn->GetSrting(pOut);
	pOut->ClearStatusBar();
}
void LoadGridAction::Execute()
{
	Grid*pGrid=pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	ReadActionParameters();
	ifstream LoadFile(name);
	int numofladders;
	LoadFile>>numofladders;
	for (int i = 0; i < numofladders; i++)
	{
		int startcell ,endcell;
		LoadFile>>startcell>>endcell;
		CellPosition start(startcell),end(endcell);
		Ladder*l=new Ladder(start,end);
		pGrid->AddObjectToCell(l);
	}
	int numofsnakes;
	LoadFile>>numofsnakes;
	for (int i = 0; i < numofsnakes; i++)
	{
		int startcell ,endcell;
		LoadFile>>startcell>>endcell;
		CellPosition start(startcell),end(endcell);
		Snake*s=new Snake(start,end);
		pGrid->AddObjectToCell(s);
	}
	int numofcards;
	LoadFile>>numofcards;
	for (int i = 0; i < numofcards; i++)
	{
		int cardnum;
		LoadFile>>cardnum;

		if(cardnum==1){
			int cell,walletamount;
			LoadFile>>cell>>walletamount;
			CellPosition Cell(cell);
			CardOne* c=new CardOne(Cell);
			c->setwalletamount(walletamount);
			pGrid->AddObjectToCell(c);
		}
		else if(cardnum==2){
			int cell;
			int walletamount;
			LoadFile>>cell>>walletamount;
			CellPosition Cell(cell);
			CardTwo* c2=new CardTwo(Cell);
			c2->setwalletamount(walletamount);
			pGrid->AddObjectToCell(c2);
		}
		else if(cardnum==3){
			int cell;
			LoadFile>>cell;
			CellPosition Cell(cell);
			CardThree* c=new CardThree(Cell);
			pGrid->AddObjectToCell(c);
		}
		else if(cardnum==4){
			int cell;
			LoadFile>>cell;
			CellPosition Cell(cell);
			CardFour* c=new CardFour(Cell);
			pGrid->AddObjectToCell(c);
		}
		else if(cardnum==5){
			int cell;
			LoadFile>>cell;
			CellPosition Cell(cell);
			CardFive* c=new CardFive(Cell);
			pGrid->AddObjectToCell(c);
		}
		else if(cardnum==6){
			int cell;
			LoadFile>>cell;
			CellPosition Cell(cell);
			CardSix* c=new CardSix(Cell);
			pGrid->AddObjectToCell(c);
		}
		else if(cardnum==7){
			int cell;
			LoadFile>>cell;
			CellPosition Cell(cell);
			CardSeven* c=new CardSeven(Cell);
			pGrid->AddObjectToCell(c);
		}
		else if(cardnum==8){
			int cell;
			LoadFile>>cell;
			CellPosition Cell(cell);
			CardEight* c=new CardEight(Cell);
			pGrid->AddObjectToCell(c);
		}
		else if(cardnum==9){
			int cell,cellnum;
			LoadFile>>cell>>cellnum;
			CellPosition Cell(cell);
			CardNine*c9 =new CardNine(Cell);
			c9->setpassedcellnum(cellnum);
			pGrid->AddObjectToCell(c9);
		}
		else if(cardnum==10){
			int cell,price,rent;
			LoadFile>>cell>>price>>rent;
			CellPosition Cell(cell);
			CardTen*c10 =new CardTen(Cell);
			c10->setrent(rent);
			c10->setprice(price);
			pGrid->AddObjectToCell(c10);
		}
		else if(cardnum==11){
			int cell,price,rent;
			LoadFile>>cell>>price>>rent;
			CellPosition Cell(cell);
			CardEleven*c11 =new CardEleven(Cell);
			c11->setrent(rent);
			c11->setprice(price);
			pGrid->AddObjectToCell(c11);
		}else if(cardnum==12){
			int cell,price,rent;
			LoadFile>>cell>>price>>rent;
			CellPosition Cell(cell);
			CardTwelve*c12 =new CardTwelve(Cell);
			c12->setrent(rent);
			c12->setprice(price);
			pGrid->AddObjectToCell(c12);
		}else if(cardnum==13){
			int cell,price,rent;
			LoadFile>>cell>>price>>rent;
			CellPosition Cell(cell);
			CardThirteen*c13 =new CardThirteen(Cell);
			c13->setrent(rent);
			c13->setprice(price);
			pGrid->AddObjectToCell(c13);
		}else if(cardnum==14){
			int cell,price,rent;
			LoadFile>>cell>>price>>rent;
			CellPosition Cell(cell);
			CardFourteen*c14 =new CardFourteen(Cell);
			c14->setrent(rent);
			c14->setprice(price);
			pGrid->AddObjectToCell(c14);
		}
		}
	}