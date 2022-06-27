#pragma once

#include "Action.h"
#include<string>
class LoadGridAction : public Action
{
protected:
	string name;
public:
	LoadGridAction(ApplicationManager*pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual~LoadGridAction();
};