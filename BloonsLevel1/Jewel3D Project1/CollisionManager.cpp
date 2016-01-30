#include "CollisionManager.h"



CollisionManager::CollisionManager()
{
}

void CollisionManager::CheckCollisions()
{
	auto collVec = Collider::GetAll();

	for (int i = 0; i < collVec.size(); ++i)
	{
		for (int k = i + 1; k < collVec.size(); ++k)
		{
			//Bullet vs. Alien
			if (collVec[i]->Type == BULLET && collVec[k]->Type == ALIEN)
			{
				EventData e(BULLET_COLL, *reinterpret_cast<int *>(&collVec[i]->Owner), *reinterpret_cast<int *>(&collVec[k]->Owner));
				EventManager::PostEvent(e);
			}
			
			//Tower vs. Alien Collision
			else if ((collVec[i]->Type == TOWER && collVec[k]->Type == ALIEN))
			{
				EventData e(TOWER_COLL, *reinterpret_cast<int *>(&collVec[i]->Owner), *reinterpret_cast<int *>(&collVec[k]->Owner));
				EventManager::PostEvent(e);
			}
			
			//Mouse vs. UI 
			else if (collVec[i]->Type == UI)
			{
				if (collVec[i]->CheckPointCollision(vec2((float)Input::GetMouseX(), (float)Input::GetMouseY())))
				{
					EventData e(BUILD_COLL, static_cast<void *>(&collVec[i]->Owner));
					EventManager::PostEvent(e);
				}
			}
		}
	}
}

CollisionManager::~CollisionManager()
{
}
