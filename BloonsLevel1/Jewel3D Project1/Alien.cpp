#include "Alien.h"


#define MAX_FORCE 1.2
#define MAX_VELOCITY 3.1

bool startPath = false;
	
	Alien::Alien(Entity &owner)
		: Component(owner)
	{
		
	}
		
	void Alien::Update(float deltaTime)
	{
		if (!DoneMoving)
		{
			Position = Owner.Transform.Position.ToVec2();

			Steering = PathFollowing();
			Truncate(Steering, MAX_FORCE);
			Steering *= 1 / Mass;

			Velocity += Steering;
			Truncate(Velocity, MAX_VELOCITY);
			Owner.Transform.Position += vec3(Velocity.x, Velocity.y, 0);
		}
	}
	
	vec2 Alien::PathFollowing()
	{
		auto target = vec2::Zero();

		if (AlienPath.GetNodes().size() > 0 && !DoneMoving)
		{
			auto nodes = AlienPath.GetNodes();

			target = nodes[CurrentNode];

			if((Owner.Transform.Position.ToVec2() - target).Length() <= 20)
			{
				CurrentNode ++;

				if (CurrentNode > nodes.size() - 1)
				{
					CurrentNode = 0;
					//target = nodes[0];
					DoneMoving = true;
					//Notify Game we hit the end so player loses a life.
					EventData e(SCREEN_COLL, static_cast<void *>(&Owner));
					EventManager::PostEvent(e);
				}
			}
		}
		
		return Seek(target);
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
				
		//Getting the final force which will represent the vector between the straight line target and our current velocity.
		force = DesiredVelocity - Velocity;
		return force;

	}

	//This function adjusts the Vector so its x and y values do not exceed the max scalar value (Typically the MAX_FORCE).
	void Alien::Truncate(vec2 &vec, const float &scalar)
	{
		float retVal = scalar / vec.Length();
		if (retVal < 1.0) {
			retVal = 1.0;
		}
		else {
			retVal =retVal;
		}
		vec *= retVal;
	}

	
