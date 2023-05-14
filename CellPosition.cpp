#include "CellPosition.h"
#include "UI_Info.h"

CellPosition::CellPosition()
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1;
	hCell = -1;
}

CellPosition::CellPosition(int v, int h)
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1;
	hCell = -1;

	SetVCell(v);
	SetHCell(h);
}

CellPosition::CellPosition(int cellNum)
{
	(*this) = GetCellPositionFromNum(cellNum); // the function call with build a cell position (vCell and hCell)
	// from the passed (cellNum)
	// (*this) = ... --> this will copy the returned (vCell and hCell)
	//                   to the data members (vCell and hCell)
}

bool CellPosition::SetVCell(int v)
{
	///TODO: Implement this function as described in the .h file (don't forget the validation)

	if ((v >= 0) && (v <= (NumVerticalCells - 1)))
	{
		vCell = v;
		return true;
	}
	else
	{
		vCell = -1;
		return false; // this line sould be changed with your implementation
	}

}

bool CellPosition::SetHCell(int h)
{
	///TODO: Implement this function as described in the .h file (don't forget the validation)
	if ((h >= 0) && (h <= (NumHorizontalCells - 1)))
	{
		hCell = h;
		return true;
	}
	else
	{
		hCell = -1;
		return false; // this line sould be changed with your implementation
	}
}

int CellPosition::VCell() const
{
	return vCell;
}

int CellPosition::HCell() const
{
	return hCell;
}

bool CellPosition::IsValidCell() const
{
	///TODO: Implement this function as described in the .h file
	if ((vCell >= 0) && (vCell <= NumVerticalCells - 1) && (hCell >= 0) && (hCell <= NumHorizontalCells - 1))
	{
		return true;
	}
	/*else
	{
		SetVCell(-1);
		SetHCell(-1);
		return false; // this line sould be changed with your implementation
	}
	*/
	return false;
}

int CellPosition::GetCellNum() const
{
	return GetCellNumFromPosition(*this); // (*this) is the calling object of GetCellNum
	// which means the object of the current data members (vCell and hCell)
}

int CellPosition::GetCellNumFromPosition(const CellPosition& cellposition)
{
	int cellNum;

	// get hcell & vcell of cellposition
	// Note:
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)
	// just define an integer that represents cell number and calculate it using the passed cellPosition then return it

	if (cellposition.IsValidCell())
	{
		int v = cellposition.VCell();
		int h = cellposition.HCell();

		int v1 = (NumVerticalCells - 1) - v; //v1 and h1 are the scale inversed
		int h1 = (NumHorizontalCells - 1) - h;

		cellNum = ((v1 + 1) * NumHorizontalCells) - h1;

		///TODO: Implement this function as described in the .h file
		return cellNum; // this line should be changed with your implementation

	}
	return 0;
}

CellPosition CellPosition::GetCellPositionFromNum(int cellNum)
{
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)

	CellPosition position;

	/// TODO: Implement this function as described in the .h file
	// Note: use the passed cellNum to set the vCell and hCell of the "position" variable declared inside the function
	//       I mean: position.SetVCell(...) and position.SetHCell(...) then return it

	if ((cellNum >= 0) && (cellNum <= NumVerticalCells * NumHorizontalCells))
	{
		int temp = cellNum / 10; //temp is the first digit of each cellnum
		int v1;
		if ((cellNum <= temp * NumHorizontalCells) && (temp * NumHorizontalCells - cellNum) < NumHorizontalCells)
		{
			v1 = temp - 1;
		}
		else if ((temp * NumHorizontalCells - cellNum) >= NumHorizontalCells)
		{
			int x = NumHorizontalCells - 11; //x is the change in no of columns in respect to the standard 11 column display
			if (x < 0)
			{
				x = x * (-1);
			}
			v1 = temp - x;
		}

		else v1 = temp;

		int v = (NumVerticalCells - 1) - v1;
		int h1 = ((v1 + 1) * NumHorizontalCells) - cellNum;
		int h = (NumHorizontalCells - 1) - h1;

		position.SetVCell(v);
		position.SetHCell(h);

		return position;
	}
	else return position;
}

void CellPosition::AddCellNum(int addedNum)
{

	/// TODO: Implement this function as described in the .h file
	// Note: this function updates the data members (vCell and hCell) of the calling object

	int newCellNum = addedNum + GetCellNum();

	GetCellPositionFromNum(newCellNum);



}
