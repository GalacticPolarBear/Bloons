#pragma once
#include <Jewel_Entity/Components/Base.h>
#include <Jewel_Math/Vector.h>
#include <Jewel_Entity\Entity.h>
#include "Path.h"
//Class representing a single alien


	class Alien : public Component<Alien>
	{
	public:
		Alien() = delete;
		Alien(const Alien &) = delete;
		Alien &operator=(const Alien &) = delete;
		Alien(Entity &owner);
		virtual ~Alien() = default;
		
		//Class functions
		void Update(float);
		vec2 PathFollowing();
		float Distance(vec2&, vec2&);
		vec2 Seek(vec2&);

		void Truncate(vec2 &, const float &);

		float VectorLength(vec2&);

		//Class Member Variables
		int CurrentNode = 0;
		Path AlienPath;
		vec2 Velocity = vec2(-1, -2);
		vec2 Position = vec2(Owner.Transform.Position.x, Owner.Transform.Position.y);
		vec2 Steering = vec2::Zero();
		vec2 Target;
		bool DoneMoving = false;
	};


