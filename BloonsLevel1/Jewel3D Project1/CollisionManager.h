#pragma once
#include <Jewel_OS\EventManager.h>
#include <vector>
#include "Collider.h"

using namespace Jwl;

class CollisionManager
{
public:
	CollisionManager();

	void CheckCollisions();
	
	~CollisionManager();
};

