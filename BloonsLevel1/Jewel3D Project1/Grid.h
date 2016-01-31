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

	void SetAreaOccupied(vec2&);

	bool CanBuild(vec2&);

	//This setup ideally creates 32 columns and 18 rows of 20px wide by 20px tall on a 1280 x 720 screen
	int Columns = 64;
	int Rows = 36;
	int CellSize = 20;

	std::vector<std::shared_ptr<Cell>> Cells;
	
	
};

