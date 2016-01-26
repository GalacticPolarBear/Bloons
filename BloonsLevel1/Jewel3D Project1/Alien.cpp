#include "Alien.h"
#include <math.h>
#include <Jewel_Input/InputKeyboard.h>
#include <Jewel_OS/Windows/Console.h>

#define MAX_FORCE 1.2
#define MAX_VELOCITY 3.1
float Mass = 5;
bool startPath = false;

	
	Alien::Alien(Entity &owner)
		: Component(owner)
	{
		
	}
		
	void Alien::Update(float deltaTime)
	{
		Position = Owner.Transform.Position.ToVec2();
		
		//this->Owner.Transform.Position += vec3(1,1,0);	
		/*
				Target = vec2(Input::GetMouseX(), -(Input::GetMouseY() - Console::GetScreenHeight()));
		
		Steering = Seek(Target);
		
		Truncate(Steering, MAX_FORCE);
	    Steering *= 1 / Mass;
		
		Velocity += Steering;
		
		Velocity.Normalize();
		//Velocity *= deltaTime;
		
		Owner.Transform.Position += vec3(Velocity.x, Velocity.y, 0);
		*/
		
		Steering = PathFollowing();

		Truncate(Steering, MAX_FORCE);
		
		Steering *= 1 / Mass;

		Velocity += Steering;
		Truncate(Velocity, MAX_VELOCITY);
  		Owner.Transform.Position += vec3(Velocity.x, Velocity.y, 0);		
	}
	
	vec2 Alien::PathFollowing()
	{
		auto target = vec2::Zero();

		if (AlienPath.GetNodes().size() > 0 && !DoneMoving)
		{
			auto nodes = AlienPath.GetNodes();

			target = nodes[CurrentNode];

			//if (Distance(vec2(Owner.Transform.Position.x, Owner.Transform.Position.y), target) <= 2)
			//(Owner.Transform.Position.ToVec2() - target).Length() < = 2))
			if((Owner.Transform.Position.ToVec2() - target).Length() <= 20)
			{
				CurrentNode ++;

				if (CurrentNode > nodes.size() - 1)
				{
					CurrentNode = 0;
					target = nodes[0];
					//DoneMoving = true;
				}
			}
		}
		else
			return vec2::Zero();

		return Seek(target);
	}
	
	float Alien::Distance(vec2 & a, vec2 & b)
	{
		return sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	}
	
	vec2 Alien::Seek(vec2 &target)
	{
		float slowRadius = 100.f;
		//Force to return
		vec2 force = vec2::Zero();
		
		//(Owner.Transform.Position.ToVec2() - target).Length();

		//Getting a vector between the target and the sprite's position.
		vec2 DesiredVelocity = target - Position;
		
		float Distance = DesiredVelocity.Length();

		//Normalizing the vector because we only really want the direction without its magnitude.
		DesiredVelocity.Normalize();
		
		if (Distance < slowRadius)
		{
 			DesiredVelocity *= MAX_VELOCITY * (Distance/slowRadius);
		}
		else 
		{
			DesiredVelocity *= MAX_VELOCITY;
		}
		//Multiplying by the Max_velocity so that we have a force which pushes towards our Seek target.
		
		
		//Getting the final force which will represent the vector between the straight line target and our current velocity.
		force = DesiredVelocity - Velocity;
		return force;

	}

	//This function adjusts the Vector so its x and y values do not exceed the max scalar value (Typically the MAX_FORCE).
	void Alien::Truncate(vec2 &vec, const float &scalar)
	{
		float retVal = scalar / VectorLength(vec);
		if (retVal < 1.0) {
			retVal = 1.0;
		}
		else {
			retVal =retVal;
		}
		vec *= retVal;
	}
	float Alien::VectorLength(vec2 &temp)
	{
		return sqrtf((temp.x*temp.x) + (temp.y * temp.y));
	}
	
