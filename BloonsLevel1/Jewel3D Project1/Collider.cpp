#include "Collider.h"

Collider::Collider(Entity &owner) : Component(owner) 
{
	
}

Collider::Collider(Entity & owner, vec2 & Scale) : Component(owner)
{
	SetSize(Scale);
}

Collider::Collider(Entity & owner, vec2 & Scale, ColliderType type) : Component(owner)
{
	Size = Scale;
	Type = type;
	//Used for Targeting
	if (Type == TOWER)
	{
		Radius = 88;
	}
}




vec2 Collider::GetSize()
{
	return Size;
}

void Collider::SetSize(vec2 &newSize)
{
	Size = newSize;
}

bool Collider::CheckBoxCollision(Collider &rect)
{
	return ((Owner.Transform.Position.x  < rect.Owner.Transform.Position.x + rect.GetSize().x) &&
			(Owner.Transform.Position.x + GetSize().x > rect.Owner.Transform.Position.x) &&
			(Owner.Transform.Position.y < rect.Owner.Transform.Position.y + rect.GetSize().y) &&
			(Owner.Transform.Position.y + GetSize().y > rect.Owner.Transform.Position.y));
}

//Only for AABB
//Check is point is between left and right sides of collider.
bool Collider::CheckPointCollision(vec2 &point)
{
	//Reduce function calling for a vec2
	vec2 ownerPosition = Owner.Transform.Position.ToVec2();
	//HalfWidth HalfHeight vector
	vec2 hwHHVec = GetSize() / 2; 
	
	//vec2 blEdge(ownerPosition.x - hwHHVec.x, ownerPosition.y - hwHHVec.y);
	vec2 tlEdge(ownerPosition.x - hwHHVec.x, ownerPosition.y + hwHHVec.y);
	//vec2 trEdge(ownerPosition.x + hwHHVec.x, ownerPosition.y + hwHHVec.y);
	vec2 brEdge(ownerPosition.x + hwHHVec.x, ownerPosition.y - hwHHVec.y);

	return ((point.x >= tlEdge.x && point.x <= brEdge.x)
		&& (point.y >= brEdge.y && point.y <= tlEdge.y));
}

//We treat this object as the Circle.
bool Collider::CheckCircleBoxCollision(Collider &rect)
{
 	vec2 circleDistance = vec2::Zero();
	vec2 rectPos = rect.Owner.Transform.Position.ToVec2();
	vec2 hwHHVec = rect.GetSize() / 2;
	
	circleDistance.x = abs(Owner.Transform.Position.x - rectPos.x);
	circleDistance.y = abs(Owner.Transform.Position.y - rectPos.y);
	
	if (circleDistance.x > (hwHHVec.x + Radius)) return false;
	if (circleDistance.y > (hwHHVec.y + Radius)) return false;

	if (circleDistance.x <= (rectPos.x + hwHHVec.x) && (circleDistance.y <= (rectPos.y + hwHHVec.y)))
	{
		return true;
	}
	float cornerDistance_sq = ((circleDistance.x - (rectPos.x + hwHHVec.x)) * (circleDistance.x - (rectPos.x + hwHHVec.x)))
		                      + ((circleDistance.y - (rectPos.y + hwHHVec.y)) * (circleDistance.y - (rectPos.y + hwHHVec.y)));
	
	return (cornerDistance_sq <= (Radius * Radius));
}

