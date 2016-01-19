#pragma once
#include <Jewel_Math\Vector.h>
#include <vector>

using namespace Jwl;

class Path
{
	public:
		Path();
		~Path();
		void AddNode(const vec2&);
		std::vector<vec2> GetNodes();
			
	private:
		std::vector<vec2> Nodes;

};


