#include "CellPosition.h"
#include "UI_Info.h"

CellPosition::CellPosition () 
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1; 
	hCell = -1; 
}

CellPosition::CellPosition (int v, int h)
{ 
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1; 
	hCell = -1; 

	SetVCell(v);
	SetHCell(h);
}

CellPosition::CellPosition (int cellNum)
{
	(*this) = GetCellPositionFromNum(cellNum); // the function call with build a cell position (vCell and hCell)
	// from the passed (cellNum)
	// (*this) = ... --> this will copy the returned (vCell and hCell)
	//                   to the data members (vCell and hCell)
}
//Done
bool CellPosition::SetVCell(int v) 
{
	if (v>=0 && v<NumVerticalCells)
	{
		vCell=v;
		return true;
	}
	else
	{
		return false;
	}
	///TODO: Implement this function as described in the .h file (don't forget the validation)  


	// this line sould be changed with your implementation
}

//Done
bool CellPosition::SetHCell(int h) 
{
	if(h>=0 && h<NumHorizontalCells)
	{
		hCell=h;
		return true;
	}
	else
	{
		return false;
	}
	///TODO: Implement this function as described in the .h file (don't forget the validation)  


	// this line sould be changed with your implementation
}

int CellPosition::VCell() const 
{
	return vCell;
}

int CellPosition::HCell() const 
{
	return hCell;
}

//Done
bool CellPosition::IsValidCell() const 
{
	if (vCell>=0 && vCell<NumVerticalCells && hCell>=0 && hCell<NumHorizontalCells)
	{
		return true;
	}
	else
	{
		return false;
	}
	///TODO: Implement this function as described in the .h file   


	// this line sould be changed with your implementation
}

int CellPosition::GetCellNum() const
{
	return GetCellNumFromPosition(*this); // (*this) is the calling object of GetCellNum
	// which means the object of the current data members (vCell and hCell)
}

//Done
int CellPosition::GetCellNumFromPosition(const CellPosition & cellPosition)
{
	int cellnumber;
	cellnumber=(8-cellPosition.VCell())*11+cellPosition.HCell()+1;

	// Note:
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)
	// just define an integer that represents cell number and calculate it using the passed cellPosition then return it

	///TODO: Implement this function as described in the .h file 



	return cellnumber; // this line should be changed with your implementation
}
//Done
CellPosition CellPosition::GetCellPositionFromNum(int cellNum)
{
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)

	CellPosition position;
	int a, b;
	a=cellNum%10;
	b=(cellNum%100)/10;
	if (a>b)
	{
		position.SetVCell(NumVerticalCells-1-b);
		position.SetHCell(a-b-1);
	}
	else if(a<b)
	{
		position.SetVCell(NumVerticalCells-b);
		position.SetHCell(NumHorizontalCells-1-(b-a));
	}
	else if(a==b)
	{
		position.SetVCell(NumVerticalCells-b);
		position.SetHCell(NumHorizontalCells-1);
	}

	/// TODO: Implement this function as described in the .h file
	// Note: use the passed cellNum to set the vCell and hCell of the "position" variable declared inside the function
	//       I mean: position.SetVCell(...) and position.SetHCell(...) then return it

	return position;
}

void CellPosition::AddCellNum (int addedNum)
{
	int cellNum=GetCellNum();
	cellNum+=addedNum;
	vCell=GetCellPositionFromNum(cellNum).VCell();
	hCell=GetCellPositionFromNum(cellNum).HCell();
	/// TODO: Implement this function as described in the .h file
	// Note: this function updates the data members (vCell and hCell) of the calling object

}