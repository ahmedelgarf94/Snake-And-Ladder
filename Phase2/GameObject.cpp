#include "GameObject.h"
#include<fstream>

GameObject::GameObject(const CellPosition & pos)
{
	position = pos; // Sets Position
}

CellPosition GameObject::GetPosition() const
{
	return position;
}

void GameObject::Save(ofstream &OutFile,int type)
{
	int cellnum=position.GetCellNum();
	OutFile<<cellnum<<" ";
}

GameObject::~GameObject()
{
}