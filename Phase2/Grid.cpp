#include "Grid.h"

#include "Cell.h"
#include "GameObject.h"
#include "Ladder.h"
#include "Snake.h"
#include "Card.h"
#include "Player.h"
#include<fstream>

Grid::Grid(Input * pIn, Output * pOut) : pIn(pIn), pOut(pOut) // Initializing pIn, pOut
{
	// Allocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CellList[i][j] = new Cell(i, j);
		}
	}

	// Allocate thePlayer Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		PlayerList[i] = new Player(CellList[NumVerticalCells-1][0], i); // first cell
		PlayerList[i]->Draw(pOut); // initially draw players in the first cell
	}

	// Initialize currPlayerNumber with 0 (first player)
	currPlayerNumber = 0; // start with the first player

	// Initialize Clipboard with NULL
	Clipboard = NULL;

	// Initialize endGame with false
	endGame = false;
}


// ========= Adding or Removing GameObjects to Cells =========


bool Grid::AddObjectToCell(GameObject * pNewObject)  // think if any validation is needed
{
	// Get the cell position of pNewObject
	CellPosition pos = pNewObject->GetPosition();
	if (pos.IsValidCell()) // Check if valid position
	{
		// Get the previous GameObject of the Cell
		GameObject * pPrevObject = CellList[pos.VCell()][pos.HCell()]->GetGameObject();
		if( pPrevObject)  // the cell already contains a game object
			return false; // do NOT add and return false

		// Set the game object of the Cell with the new game object
		CellList[pos.VCell()][pos.HCell()]->SetGameObject(pNewObject);
		return true; // indicating that addition is done
	}
	return false; // if not a valid position
}

void Grid::RemoveObjectFromCell(const CellPosition & pos)
{
	if (pos.IsValidCell()) // Check if valid position
	{
		// Note: you can deallocate the object here before setting the pointer to null if it is needed

		CellList[pos.VCell()][pos.HCell()]->SetGameObject(NULL);
	}
}

void Grid::UpdatePlayerCell(Player * player, const CellPosition & newPosition)
{
	// Clear the player's circle from the old cell position
	player->ClearDrawing(pOut);

	// Set the player's CELL with the new position
	Cell * newCell = CellList[newPosition.VCell()][newPosition.HCell()];
	player->SetCell(newCell);	

	// Draw the player's circle on the new cell position
	player->Draw(pOut);
}


// ========= Setters and Getters Functions =========


Input * Grid::GetInput() const
{
	return pIn;
}

Output * Grid::GetOutput() const
{
	return pOut;
}

void Grid::SetClipboard(Card * pCard) // to be used in copy/cut
{
	// you may update slightly in implementation if you want (but without breaking responsibilities)
	Clipboard = pCard;
}

Card * Grid::GetClipboard() const // to be used in paste
{
	return Clipboard;
}

void Grid::SetEndGame(bool endGame)
{
	this->endGame = endGame;
}

bool Grid::GetEndGame() const
{
	return endGame;
}

void Grid::AdvanceCurrentPlayer()
{
	currPlayerNumber = (currPlayerNumber + 1) % MaxPlayerCount; // this generates value from 0 to MaxPlayerCount - 1
}

// ========= Other Getters =========


Player * Grid::GetCurrentPlayer() const
{
	return PlayerList[currPlayerNumber];
}

Ladder * Grid::GetNextLadder(const CellPosition & position)
{

	int startH = position.HCell(); // represents the start hCell in the current row to search for the ladder in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{


			///TODO: Check if CellList[i][j] has a ladder, if yes return it
			if(CellList[i][j]->HasLadder())
				return CellList[i][j]->HasLadder();

		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}


Snake * Grid::GetNextSnake(const CellPosition & position)
{

	int startH = position.HCell(); 
	for (int i = position.VCell(); i >= 0; i--)
	{
		for (int j = startH; j < NumHorizontalCells; j++)
		{


			if(CellList[i][j]->HasSnake())
				return CellList[i][j]->HasSnake();

		}
		startH = 0; 
	}
	return NULL;
}

// ========= User Interface Functions =========


void Grid::UpdateInterface() const
{
	if (UI.InterfaceMode == MODE_DESIGN)
	{
		// 1- Draw cells with or without cards 
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawCellOrCard(pOut);
			}
		}

		// 2- Draw other cell objects (ladders, snakes)
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawLadderOrSnake(pOut);
			}
		}

		// 3- Draw players
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->Draw(pOut);
		}
	}
	else // In PLAY Mode
	{
		// 1- Print Player's Info
		string playersInfo = "";
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->AppendPlayerInfo(playersInfo); // passed by reference
			if (i < MaxPlayerCount-1) // except the last player
				playersInfo += ", ";
		}
		playersInfo += " | Curr = " + to_string(currPlayerNumber);

		pOut->PrintPlayersInfo(playersInfo);

		// Note: UpdatePlayerCell() function --> already update drawing players in Play Mode
		//       so we do NOT need draw all players again in UpdateInterface() of the Play mode
		// In addition, cards/snakes/ladders do NOT change positions in Play Mode, so need to draw them here too
	}
}

void Grid :: newGame(){
	for(int i=0;i< MaxPlayerCount;i++){
		UpdateInterface();
		PlayerList[i]->SetWallet(100);
		PlayerList[i]->SetTurnCount(0);
		UpdatePlayerCell(PlayerList[i], CellPosition::GetCellPositionFromNum(1));
	}
	currPlayerNumber=0;
}

bool Grid::overLapping(GameObject* pNew) const
{
	CellPosition NewObjectPosition=pNew->GetPosition();
	if(dynamic_cast<Ladder*>(pNew)){
		for(int i=NumVerticalCells-1;i>=0;i--){		
			for(int j=0;j<NumHorizontalCells;j++){		
				Ladder*CurrLadder=CellList[i][j]->HasLadder();
				if(CurrLadder && CurrLadder->GetPosition().HCell()==NewObjectPosition.HCell()){
					if(CurrLadder->overLapping(pNew))
					{
						return true;
					}
				}
			}
		}
	}
	else{
		for(int i=NumVerticalCells-1;i>=0;i--){		
			for(int j=0;j<NumHorizontalCells;j++){		
				Snake*CurrSnake=CellList[i][j]->HasSnake();
				if(CurrSnake && CurrSnake->GetPosition().HCell()==NewObjectPosition.HCell())
				{
					if(CurrSnake->overLapping(pNew))
						return true;
				}
			}
		}
	}
	return false;
}

void Grid::PrintErrorMessage(string msg)
{
	pOut->PrintMessage(msg);
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
}

void Grid::EditableCard(Card*& pCard, CellPosition& cardPosition)
{
	if (pCard == NULL)
	{
		pCard = CellList[cardPosition.VCell()][cardPosition.HCell()]->HasCard();

	}
}

void Grid::RemoveAllObjects()
{
	for (int i = NumVerticalCells - 1; i >= 0; i--) // bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // left to right
		{
			CellList[i][j]->SetGameObject(NULL);
		}
	}
}

Card* Grid :: GetCardPointer(CellPosition position, int Card_Number)                                          
{
	int Cell_Number_of_Passed_Position = position.GetCellNum();
	Card* pCard = this->CellList[position.VCell()][position.HCell()]->HasCard();
	if (pCard != NULL)
	{
		int Clicked_Card_Number= pCard->GetCardNumber();

		int Cell_Number_Of_Card = (pCard->GetPosition()).GetCellNum();   
		if (Cell_Number_of_Passed_Position == Cell_Number_Of_Card  && Clicked_Card_Number== Card_Number)
		{
			return pCard;
		}
	}
	return 0;
}

bool Grid::IsThereACard(const CellPosition position, int &Clicked_Card_Number)/// ana elli mezewedaha hena w fel .h
{
	int Cell_Number_Of_Position = position.GetCellNum();
	Card* pcard = this->CellList[position.VCell()][position.HCell()]->HasCard();
	if (pcard != NULL)
	{
		int Cell_Number_Of_Card = (pcard->GetPosition()).GetCellNum();
		if (Cell_Number_Of_Position  == Cell_Number_Of_Card)
		{
			Clicked_Card_Number = pcard->GetCardNumber();
			return true;
		}
	}
	return false;
}

Cell* Grid::gCell(CellPosition &c) const
{
	int v=c.VCell();
	int h=c.HCell();
	return CellList[v][h];
}

Card* Grid::hasacard(CellPosition pos)
{
	Card* pCard;
	CellPosition endpointlad;
	for (int i = NumVerticalCells - 1; i >= pos.VCell(); i--)
	{

		pCard = CellList[i][pos.HCell()]->HasCard();
		if (pCard)
		{
			return pCard;

		}

	}
	return false;

}

void Grid::notadvancecurrentplayer()
{
	currPlayerNumber = (currPlayerNumber - 1) % MaxPlayerCount;
}

Grid::~Grid()
{
	delete pIn;
	delete pOut;

	// Deallocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) 
	{
		for (int j = 0; j < NumHorizontalCells; j++) 
		{
			delete CellList[i][j];
		}
	}

	// Deallocate the Player Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		delete PlayerList[i];
	}
}

void Grid::SaveAll(ofstream&OutFile,int type)
{
	int startH = 0; 
	for (int i =8; i >= 0; i--) 
	{
		for (int j = startH; j < NumHorizontalCells; j++) 
		{
			if(CellList[i][j]->GetGameObject())
			{
				CellList[i][j]->GetGameObject()->Save(OutFile,type);
			}		
		}
		startH = 0; 
	}


}
int Grid::GetNumOfLadders()
{
	int count=0;
	int startH = 0; 
	for (int i =8; i >= 0; i--) 
	{
		for (int j = startH; j < NumHorizontalCells; j++) 
		{



			if(CellList[i][j]->HasLadder())
				count++;

		}
		startH = 0; 
	}
	return count;
}

int Grid::GetNumOfSnakes()
{
	int count=0;
	int startH =0; 
	for (int i = 8; i >= 0; i--) 
	{
		for (int j = startH; j < NumHorizontalCells; j++) 
		{
			if(CellList[i][j]->HasSnake())
				count++;

		}
		startH = 0; 
	}
	return count;
}

int Grid::GetNumOfCards()
{
	int count=0;
	int startH =0; 
	for (int i = 8; i >= 0; i--) 
	{
		for (int j = startH; j < NumHorizontalCells; j++) 
		{
			if(CellList[i][j]->HasCard())
				count++;

		}
		startH = 0; 
	}
	return count;
}