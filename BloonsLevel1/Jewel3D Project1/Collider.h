#pragma once
#include <Jewel_Entity/Components/Base.h>
#include <Jewel_Entity\Entity.h>
#include <Jewel_Math/Vector.h>

using namespace Jwl;

class Collider : public Component<Collider>
{

public:
	
	Collider () = delete;
	Collider(const Collider &) = delete;
	Collider &operator=(const Collider &) = delete;
	Collider (Entity &owner);
	Collider(Entity &owner, vec2& Scale);
	virtual ~Collider() = default;
	

	int GetLayer();
	void SetLayer(int&);

	vec2 GetSize();
	void SetSize(vec2 &);

	bool CheckBoxCollision(Collider&);
	bool CheckPointCollision(vec2&);
		
		
private:
	vec2 Size;
	int Layer;
};

