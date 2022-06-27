#pragma once
#include"Action.h"
#include<string>
#include"Input.h"
#include"ApplicationManager.h"
#include"Cell.h"
#include"Card.h"
#include<iostream>
class SaveGridAction:public Action
{
protected:
	string name;
public:
	SaveGridAction(ApplicationManager*pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual~SaveGridAction();
};