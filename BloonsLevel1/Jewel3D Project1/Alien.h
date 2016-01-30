#pragma once
#include "Path.h"
#include <Jewel_Entity/Components/Base.h>
#include <Jewel_Input/InputKeyboard.h>
#include <Jewel_OS/Windows/Console.h>
#include <Jewel_Math/Vector.h>
#include <Jewel_Entity\Entity.h>
#include <Jewel_OS\EventManager.h>

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
		vec2 Seek(vec2&);
		void Truncate(vec2 &, const float &);

		//Class Member Variables
		int CurrentNode = 0;
		Path AlienPath;
		vec2 Velocity = vec2(-1, -2);
		vec2 Position = Owner.Transform.Position.ToVec2();
		vec2 Steering = vec2::Zero();
		vec2 Target;
		bool DoneMoving = false;
		int Health = 240;
		int GoldGain = 15;
		float Mass = 5;
};


