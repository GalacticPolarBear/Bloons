#include "Collider.h"

Collider::Collider(Entity &owner) : Component(owner) 
{

}

Collider::Collider(Entity & owner,  vec2 & Scale) : Component(owner)
{
	SetSize(Scale);
}

int Collider::GetLayer()
{
	return Layer;
}

void Collider::SetLayer(int & newLayer)
{
	Layer = newLayer;
}

vec2 Collider::GetSize()
{
	return vec2();
}

void Collider::SetSize(vec2 &newSize)
{
	Size = newSize;
}

bool Collider::CheckBoxCollision(Collider &collidee)
{
		
	return ((Owner.Transform.Position.x  < collidee.Owner.Transform.Position.x + collidee.GetSize().x) &&
		(Owner.Transform.Position.x + GetSize().x > collidee.Owner.Transform.Position.x) &&
		(Owner.Transform.Position.y < collidee.Owner.Transform.Position.y + collidee.GetSize().y) &&
		(Owner.Transform.Position.y + GetSize().y > collidee.Owner.Transform.Position.y));
	
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

	return ((point.x >= tlEdge.x && point.x <= brEdge.x) && (point.y >= brEdge.y && point.y <= tlEdge.y));
}
