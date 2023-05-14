#include "Switchtodesignmode.h"
#include"Output.h"
#include"Grid.h"

Switchtodesignmode::Switchtodesignmode(ApplicationManager* pApp) :Action(pApp) //constructor
{

}

void Switchtodesignmode::ReadActionParameters()
{
	//reading action parameters
}

void Switchtodesignmode::Execute()
{
	Grid* pGrid = pManager->GetGrid();     //Get a pointer grid from AppManager

	Output* pOut = pGrid->GetOutput();     //Get a pointer Output from Grid

	pOut->CreateDesignModeToolBar();       //calliing the function create design mode 


	pOut->ClearStatusBar();                //clear up function



}

Switchtodesignmode::~Switchtodesignmode()    //destructor
{

}