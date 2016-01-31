#include "Tower.h"

Tower::Tower(Entity &owner)
	: Component(owner)
{

}

void Tower::LookAtTarget(vec2& target)
{
	vec2 newTarget = Owner.Transform.Position.ToVec2() - target;
	
	if (newTarget.Length() > 0)
	{
		newTarget.Normalize();
		vec3 right = Cross((-vec3::UnitZ()), vec3(newTarget, 0));
		Owner.Transform.Rotation = quat(right, vec3(newTarget, 0), vec3::UnitZ());
	}
}

float Tower::Distance(vec2 &vecToCheck)
{
	vec2 Pos = Owner.Transform.Position.ToVec2();
	return sqrt(((Pos.x - vecToCheck.x) * (Pos.x - vecToCheck.x)) + ((Pos.y - vecToCheck.y) * (Pos.y - vecToCheck.y)));

}

//Returns true if needle is in Targets and false if not.
bool Tower::FindTarget(Entity *needle)
{
	auto index = std::find(Targets.begin(), Targets.end(), needle);
	
	return (index != Targets.end());
}

void Tower::AddTarget(Entity *toAdd)
{
	Targets.push_back(toAdd);
}

void Tower::RemoveTarget(Entity *toRemove)
{
	Targets.erase(std::find(Targets.begin(), Targets.end(), toRemove));
	Targets.shrink_to_fit();
}

void Tower::Update(float deltaTime)
{
	ElapsedTime += deltaTime;
	if (!Targets.empty())
	{
		CurrTarget = Targets[0]->Transform.Position.ToVec2();
		LookAtTarget(CurrTarget);
		if(Distance(CurrTarget) <= Range)
		if (ElapsedTime >= FireTimer)
		{
			ElapsedTime = 0;
			EventData e(SHOOT_BULLET, static_cast<void *>(&Owner));
			EventManager::PostEvent(e);
		}

	}
}


