#include "Bullet.h"



Bullet::Bullet(Entity & owner) : Component(owner)
{

}

Bullet::Bullet(Entity &owner, vec2& traj) : Component(owner)
{
	Trajectory = traj;
}

void Bullet::Update()
{
	Owner.Transform.Position += vec3(Trajectory * Speed, 0);
}
