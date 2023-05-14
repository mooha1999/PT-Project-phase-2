#include "Switchtoplaymode.h"
#include"Output.h"
#include"Grid.h"

Switchtoplaymode::Switchtoplaymode(ApplicationManager* pApp) :Action(pApp)  //constructor
{

}

void Switchtoplaymode::ReadActionParameters()
{
	//reading action parameters 
}

void Switchtoplaymode::Execute()
{
	Grid* pGrid = pManager->GetGrid();     //get a pointer Grid from AppManager

	Output* pOut = pGrid->GetOutput();     //get a pointer Output from Grid

	pOut->CreatePlayModeToolBar();         //calling the function create play mode tool bar

	pOut->ClearStatusBar();                //clear up function



}

Switchtoplaymode::~Switchtoplaymode()      //destructor
{

}