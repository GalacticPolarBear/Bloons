#include "Path.h"


Path::Path()
{
}


Path::~Path()
{
}

void Path::AddNode(const vec2& newNode)
{
	Nodes.push_back(newNode);
}

std::vector<vec2> Path::GetNodes()
{
	return Nodes;
}

void Path::SetPath(Path &newPath)
{
	Nodes = newPath.GetNodes();
}
