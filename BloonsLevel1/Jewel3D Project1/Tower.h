#pragma once
#include <Jewel_Entity/Components/Base.h>
#include <Jewel_Math/Vector.h>
#include <Jewel_Entity\Entity.h>
#include <algorithm>
#include <Jewel_OS\EventManager.h>
//Class representing a unit

using namespace Jwl;

class Tower : public Component<Tower>
{
public:
	Tower() = delete;
	Tower(const Tower &) = delete;
	Tower &operator=(const Tower &) = delete;
	Tower(Entity &owner);
	virtual ~Tower() = default;
	
	void LookAtTarget(vec2&);

	//Get's distance between this position and the passed one. 
	float Distance(vec2&);

	bool FindTarget(Entity *);

	void AddTarget(Entity*);

	void RemoveTarget(Entity*);

	void Update(float deltaTime);
	
	int Cost = 100;
	std::vector<Entity *> Targets;
	vec2 CurrTarget = vec2::Zero();
	float FireTimer = 2;
	float ElapsedTime = 0;
	float Range = 88;
};

