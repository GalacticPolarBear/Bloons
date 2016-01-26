#pragma once
#include <Jewel_Math\Vector.h>
using namespace Jwl;

class Cell
{
public:
	Cell();
	Cell(vec2 &, bool = false);
	~Cell();

	void SetOccupied(bool);
	bool GetOccupied();

	vec2 Position;
	
private: 
	bool Occupied = false;

};

