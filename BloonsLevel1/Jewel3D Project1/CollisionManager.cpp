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
			//Tower vs. Alien Collision
			if ((collVec[i]->Type == ALIEN && collVec[k]->Type == TOWER))
			{
				if (collVec[k]->CheckCircleBoxCollision(*collVec[i]))
				{
					EventData e(TOWER_COLL, reinterpret_cast<int>(&collVec[i]->Owner), reinterpret_cast<int>(&collVec[k]->Owner));
					EventManager::PostEvent(e);
				}
			}

			//Bullet vs. Alien
			else if (collVec[i]->Type == ALIEN && collVec[k]->Type == BULLET)
			{
				if (collVec[k]->CheckBoxCollision(*collVec[i]))
				{
					EventData e(BULLET_COLL, reinterpret_cast<int>(&collVec[k]->Owner), reinterpret_cast<int>(&collVec[i]->Owner));
					EventManager::PostImmediateEvent(e);
					Log("Bullet event fired");
				}
			}
			
			
		}
	}
}

CollisionManager::~CollisionManager()
{
}
