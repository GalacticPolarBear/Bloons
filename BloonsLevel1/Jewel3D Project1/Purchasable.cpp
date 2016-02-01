#include "Purchasable.h"


Purchasable::Purchasable(Entity & owner, int cost, BuildType type) : Component(owner)
{
	Cost = cost;
	Type = type;
}

