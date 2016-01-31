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
				if (collVec[i]->CheckBoxCollision(*collVec[k]))
				{
					EventData e(BULLET_COLL, *reinterpret_cast<int *>(&collVec[i]->Owner), *reinterpret_cast<int *>(&collVec[k]->Owner));
					EventManager::PostEvent(e);
				}
			}
			
			//Tower vs. Alien Collision
			else if ((collVec[i]->Type == TOWER && collVec[k]->Type == ALIEN))
			{
				if (collVec[i]->CheckCircleBoxCollision(*collVec[k]))
				{
					EventData e(TOWER_COLL, *reinterpret_cast<int *>(&collVec[i]->Owner), *reinterpret_cast<int *>(&collVec[k]->Owner));
					EventManager::PostEvent(e);
				}
			}			
		}
	}
}

CollisionManager::~CollisionManager()
{
}
