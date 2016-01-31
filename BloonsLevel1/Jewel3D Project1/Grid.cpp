#include "Grid.h"
#include <iostream>
#include <fstream>
#include <sstream>

Grid::Grid()
{

}
	


Grid::~Grid()
{
	
}

void Grid::Generate()
{
	for (int i = 0; i < Rows; ++i)
	{
		for (int j = 0; j < Columns; ++j)
		{
			Cells.push_back(std::shared_ptr<Cell>(new Cell(vec2(j * CellSize, i * CellSize)))); //shared_ptr<WhatType?>(new WhatType?(Constructor params, Constructor params ....)
		}
	}
}

bool Grid::CheckOccupyStatus(vec2 &MousePos)
{
	int index = GetIndex(MousePos);
	return Cells[index]->GetOccupied();
}

int Grid::GetIndex(vec2 &coords)
{
	//Row major index calculation.
	int colIndex = (coords.x / CellSize);
	int rowIndex = (coords.y / CellSize);
	int testInt = (rowIndex * Columns) + colIndex;
	return testInt;
}

void Grid::SetPathOccupied(std::string filePath)
{
	std::ifstream pathCoords;

	pathCoords.open(filePath);

	if (!pathCoords)
	{
		std::cerr << "Failed to open file. File not found. \n" + filePath;
		return;
	}
	
	for (std::string line; std::getline(pathCoords, line);)
	{
		std::istringstream in(line);

		float x, y;
		in >> x >> y;
		//Photoshop's y axis values are inversed from my own so I need to convert the y to my coordinate system.
		//720 is the resolution of the default screen. 
		Cells[GetIndex(vec2(x, 720 - y))]->SetOccupied(true);
	}

	pathCoords.close();
}

void Grid::SetAreaOccupied(vec2 &area)
{
	int curIndex = GetIndex(area);
	Cells[curIndex]->SetOccupied(true);
	Cells[curIndex - 1]->SetOccupied(true);
	Cells[curIndex + 1]->SetOccupied(true);
	Cells[curIndex + Columns]->SetOccupied(true);
	Cells[curIndex - Columns]->SetOccupied(true);
	Cells[curIndex + Columns - 1]->SetOccupied(true);
	Cells[curIndex + Columns + 1]->SetOccupied(true);
	Cells[curIndex - Columns - 1]->SetOccupied(true);
	Cells[curIndex - Columns + 1]->SetOccupied(true);
}

bool Grid::CanBuild(vec2 &MousePos)
{
	//This function is going to check the occupy status of all the cells around a position.
	//If any of the cells checked have an Occupy of true the function returns false.
	std::vector<std::shared_ptr<Cell>> checkCells;

	//Cell representing the current mouse position.
	int curIndex = GetIndex(MousePos);
	std::shared_ptr<Cell> tempCell = Cells[curIndex];

	//Can't forget the current cell we are at.
	checkCells.push_back(Cells[curIndex]);
	
	if (tempCell->Position.y <= CellSize) //Means it is on the bottom row so we already don't have enough space for 8 cells anyways
	{		
		return false;
	}

	else if (tempCell->Position.y >= 720 - CellSize) //Top Row not enough space for 8 squares.
	{
		return false;
	}

	else //Somewhere in between the top row and bottom row. 
	{
		if (tempCell->Position.x <= CellSize) //First column but not in a corner since we've ruled that out in the first if statement.
		{
			//There is only 5 spots to check
			return false; 
		}
		else if (tempCell->Position.x >= 1280 - CellSize) //In the furthest right column
		{
			//Only 5 spots to check.
			return false;
		}
		else //Not in first column or last column. Also not in the top row or the bottom row.  
		{
			//Eight spots to check
			
			//Check left
			checkCells.push_back(Cells[curIndex - 1]);
			//Check right
			checkCells.push_back(Cells[curIndex + 1]);
			//Check above
			checkCells.push_back(Cells[curIndex + Columns]);
			//Check below
			checkCells.push_back(Cells[curIndex - Columns]);
			//Check above left
			checkCells.push_back(Cells[curIndex + Columns - 1]);
			//Check cell to above right
			checkCells.push_back(Cells[curIndex + Columns + 1]);
			//Check bottom left
			checkCells.push_back(Cells[curIndex - Columns - 1]);
			//Check bottom right
			checkCells.push_back(Cells[curIndex - Columns + 1]);
		}
	}

	//We have gotten this far so that means we have our 8 spots to check and our initial location.
	for (std::shared_ptr<Cell> cell : checkCells)
	{
		if (cell->GetOccupied())
		{
			return false;
		}
	}
	//We have checked all the possibilities. And if we get to this line that means that the only conclusion is YES it is Buildable.
	return true;
}
