#pragma once
#include <Jewel_Entity/Components/Base.h>
#include <Jewel_Entity\Entity.h>
#include <Jewel_Math/Vector.h>
#include <math.h> 
using namespace Jwl;

//What it's attached to
enum ColliderType {
	ALIEN,
	TOWER,
	UIELEMENT,
	BULLET
};

class Collider : public Component<Collider>
{

public:
	
	Collider () = delete;
	Collider(const Collider &) = delete;
	Collider &operator=(const Collider &) = delete;
	Collider (Entity &owner);
	Collider(Entity &owner, vec2& Scale, ColliderType = ALIEN);
	Collider(Entity &owner, vec2& Scale);
	virtual ~Collider() = default;

	vec2 GetSize();
	void SetSize(vec2 &);

	bool CheckBoxCollision(Collider&);
	bool CheckPointCollision(vec2&);
	bool CheckCircleBoxCollision(Collider&);
	ColliderType Type;
	float Radius = 0;
private:
	vec2 Size;
	
};

