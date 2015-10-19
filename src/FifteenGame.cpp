#include "FifteenGame.h"

Cell::Cell() : xCoord(0), yCoord(0), value(0) {}

Cell::Cell(int x, int y, int v) : xCoord(x), yCoord(y), value(v) {}

COORD Cell::GetCoords() const
{
	COORD c;
	c.X = xCoord;
	c.Y = yCoord;
	return c;
}

void Cell::SetCoords(int x, int y)
{
	SetXCoord(x);
	SetYCoord(y);
}

void Cell::SetXCoord(int x)
{
	x >= 0 ? xCoord = x : xCoord = 0;
}

void Cell::SetYCoord(int y)
{
	y >= 0 ? yCoord = y : yCoord = 0;
}

void Cell::SetValue(int v)
{
	v >= 0 ? value = v : value = 0;
}

Fifteen::Fifteen() : fieldSize(SIZE)
{
	FillField();
}

Fifteen::Fifteen(int s) : fieldSize(SIZE)
{
	if(s >= 0 && s <= 10)
	{
		fieldSize = s;
	}
	FillField();
}

void Fifteen::FillField()
{
	int index = 0;
	for(int i = 0; i < fieldSize; i++)
	{
		for(int j = 0; j < fieldSize; j++)
		{
			field.push_back( index != 15 ? Cell(j, i, index + 1) : Cell(j, i, 0));
			index++;
		}
	}
}

bool Fifteen::GetCell(int index, Cell& cell)
{
	if(index >=0 && index < fieldSize * fieldSize)
	{
		cell = field[index];
		return true;
	}
	return false;
}

bool Fifteen::GetCell(int x, int y, Cell& cell)
{
	if(x >= 0 && x < fieldSize)
	{
		if(y >= 0 && y < fieldSize)
		{
			int index = x + y * fieldSize;
			cell = field[index];
			return true;
		}
	}
	return false;
}

bool Fifteen::MoveCell(int index)
{
	int x = index % fieldSize;
	int y = index / fieldSize;
	
	Cell cell;
	int dest = -1;														
	
	if ( GetCell(x, y - 1, cell) && cell.GetValue() == 0 )
	{
		dest = cell.GetXCoord() + cell.GetYCoords() * fieldSize;
	}
	else if( GetCell(x, y + 1, cell) && cell.GetValue() == 0 )
	{
		dest = cell.GetXCoord() + cell.GetYCoords() * fieldSize;
	}
	else if( GetCell(x - 1, y, cell) && cell.GetValue() == 0 )
	{
		dest = cell.GetXCoord() + cell.GetYCoords() * fieldSize;
	}
	else if( GetCell(x + 1, y, cell) && cell.GetValue() == 0 )
	{
		dest = cell.GetXCoord() + cell.GetYCoords() * fieldSize;
	}
	
	if(dest >= 0)
	{
		SwapCell(index, dest);
		return true;
	}
	return false;
}

void Fifteen::SwapCell(int source, int dest)
{
	int tmpValue;
	tmpValue = field[source].GetValue();
	field[source].SetValue(field[dest].GetValue());
	field[dest].SetValue(tmpValue);
}

bool Fifteen::isWin()
{
	for(int i = 0; i < fieldSize * fieldSize - 2; i++)
	{
		if( field[i].GetValue() > field[i + 1].GetValue() )
		{
			return false;
		}
	}
	return true;
}

void Fifteen::Shuffle()
{
	int empty =  fieldSize * fieldSize - 1;
	int xEmpty = fieldSize - 1;
	int yEmpty = fieldSize - 1;					
	int direction = 0;
	int dest = 0;
	Cell tmp;

	for(int i = 0; i < SHUFFLE; i++)
	{
		direction = rand() % 4 + 1;
		dest = -1;

		switch (direction)
		{
		case TOP:
			if( GetCell(xEmpty, yEmpty - 1, tmp) )
			{
				dest = tmp.GetXCoord() + tmp.GetYCoords() * fieldSize;
			}
			break;
		case RIGHT:
			if( GetCell(xEmpty + 1, yEmpty, tmp) )
			{
				dest = tmp.GetXCoord() + tmp.GetYCoords() * fieldSize;
			}
			break;
		case DOWN:
			if( GetCell(xEmpty, yEmpty + 1, tmp) )
			{
				dest = tmp.GetXCoord() + tmp.GetYCoords() * fieldSize;
			}
			break;
		case LEFT:
			if( GetCell(xEmpty - 1, yEmpty, tmp) )
			{
				dest = tmp.GetXCoord() + tmp.GetYCoords() * fieldSize;
			}
			break;
		}

		if(dest > 0)
		{
			SwapCell(empty, dest);
			xEmpty = dest % fieldSize;
			yEmpty = dest / fieldSize;
			empty = dest;
		}
	}
}