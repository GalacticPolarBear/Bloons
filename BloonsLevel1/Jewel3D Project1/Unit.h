#pragma once
#include <Jewel_Entity/Components/Base.h>
#include <Jewel_Math/Vector.h>
#include <Jewel_Entity\Entity.h>

//Class representing a unit

using namespace Jwl;

class Unit : public Component<Unit>
{
public:
	Unit() = delete;
	Unit(const Unit &) = delete;
	Unit &operator=(const Unit &) = delete;
	Unit(Entity &owner);
	virtual ~Unit() = default;
	
	void LookAtTarget(vec2&);

	void AddTarget(Entity*);

	void RemoveTarget(Entity*);

	void Update();
	
	int Cost = 100;
	std::vector<Entity *> targets;
	vec2 CurrTarget = vec2::Zero(); 
};

