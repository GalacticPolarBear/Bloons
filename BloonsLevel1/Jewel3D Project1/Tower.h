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
	Tower(Entity &owner, int cost);
	
	virtual ~Tower() = default;
	
	void LookAtTarget(vec2&);

	//Get's distance between this position and the passed one. 
	float Distance(vec2&);

	bool FindTarget(Entity *);

	void AddTarget(Entity*);

	void RemoveTarget(Entity*);

	void Update(float deltaTime);
		
	int Damage = 60;
	int Cost = 0;

	std::vector<Entity *> Targets;
	Entity* CurrTarget = nullptr;
	
	float FireTimer = .5;
	float ElapsedTime = 0;
	float Range = 88;
};

