#include "Unit.h"

Unit::Unit(Entity &owner)
	: Component(owner)
{

}

void Unit::LookAtTarget(vec2& target)
{
	vec2 newTarget = Owner.Transform.Position.ToVec2() - target;
	
	if (newTarget.Length() > 0)
	{
		newTarget.Normalize();
		vec3 right = Cross((-vec3::UnitZ()), vec3(newTarget, 0));
		Owner.Transform.Rotation = quat(right, vec3(newTarget, 0), vec3::UnitZ());
	}
}


void Unit::AddTarget(Entity *toAdd)
{
	targets.push_back(toAdd);
}

void Unit::RemoveTarget(Entity *toRemove)
{
	targets.erase(std::find(targets.begin(), targets.end(), toRemove));
	targets.shrink_to_fit();
}

void Unit::Update()
{
	if (!targets.empty())
	{
		CurrTarget = targets[0]->Transform.Position.ToVec2();
		LookAtTarget(CurrTarget);
	}
}


