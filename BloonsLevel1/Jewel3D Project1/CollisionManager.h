#pragma once
#include <Jewel_OS\EventManager.h>
#include <vector>
#include "Collider.h"
#include <Jewel_Input\InputKeyboard.h>

using namespace Jwl;

class CollisionManager
{
public:
	CollisionManager();

	void CheckCollisions();
	
	~CollisionManager();
};

