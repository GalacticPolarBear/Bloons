#include "Cell.h"



Cell::Cell()
{
}

Cell::Cell(vec2& pos, bool occ)
{
	Position = pos;

	Occupied = occ;
}


Cell::~Cell()
{
}

void Cell::SetOccupied(bool occ)
{
	Occupied = occ;
}

bool Cell::GetOccupied()
{
	return Occupied;
}
