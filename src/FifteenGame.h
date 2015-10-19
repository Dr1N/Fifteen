#pragma once
#include "mystdafx.h"

class Cell
{
	int xCoord;
	int yCoord;
	int value;
public:
	Cell();
	Cell(int x, int y, int v);
	
	void SetCoords(int x, int y);
	COORD GetCoords() const;

	void SetXCoord(int x);
	int GetXCoord() const { return xCoord; }

	void SetYCoord(int y);
	int GetYCoords() const { return yCoord; }

	void SetValue(int v);
	int GetValue() const { return value; }
};

class Fifteen
{
private:
	int fieldSize;
	std::vector<Cell> field;
	void SwapCell(int source, int dest);
public:
	Fifteen();
	Fifteen(int fSize);
	
	void FillField();
	std::vector<Cell>& GetField() { return field; }
	
	bool GetCell(int index, Cell& cell);
	bool GetCell(int x, int y, Cell& cell);

	bool MoveCell(int index);
	
	bool isWin();
	
	void Shuffle();
};