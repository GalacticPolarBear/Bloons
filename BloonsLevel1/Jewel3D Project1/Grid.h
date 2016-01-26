#pragma once
#include "Cell.h"
#include <vector>
#include <memory>

class Grid
{
public:
	Grid();
	
	
	~Grid();
	
	void Generate();
	
	bool CheckOccupyStatus(vec2&);

	int GetIndex(vec2&);
	
	//Read from file and set cells in the Grid to occupy.
	void SetPathOccupied(std::string );

	bool CanBuild(vec2&);

	//This setup ideally creates 32 columns and 18 rows of 40px wide by 40px tall on a 1280 x 720 screen
	int Columns = 32;
	int Rows = 18;
	int CellSize = 40;

	std::vector<std::shared_ptr<Cell>> Cells;
	
	
};

