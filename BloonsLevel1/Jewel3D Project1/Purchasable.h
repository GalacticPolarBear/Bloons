#pragma once
#include <Jewel_Entity/Components/Base.h>

using namespace Jwl;

enum BuildType
{
	TOWERRED,
	TOWERBLUE
};

class Purchasable : public Component<Purchasable>
{
public:

	Purchasable() = delete;
	Purchasable(const Purchasable &) = delete;
	Purchasable &operator=(const Purchasable &) = delete;
	Purchasable(Entity &owner, int cost, BuildType type);
	virtual ~Purchasable() = default;
	
	BuildType Type = TOWERRED;
	
	int Cost = 0;
};

