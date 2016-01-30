#pragma once
#pragma once
#include <Jewel_Entity/Components/Base.h>
#include <Jewel_Math/Vector.h>
#include <Jewel_Entity\Entity.h>

using namespace Jwl;

class Bullet : public Component<Bullet>
{
public:
	Bullet() = delete;
	Bullet(const Bullet &) = delete;

	Bullet &operator=(const Bullet &) = delete;
	
	Bullet(Entity &owner);
	Bullet(Entity &owner, vec2&);
	void Update();

	virtual ~Bullet() = default;

	int Damage = 60;
	vec2 Trajectory = vec2::Zero();
	float Speed = 1.5f;
};


