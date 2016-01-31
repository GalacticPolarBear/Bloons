#include "Bullet.h"



Bullet::Bullet(Entity & owner) : Component(owner)
{

}

Bullet::Bullet(Entity &owner, vec2& traj, int damage) : Component(owner)
{
	Trajectory = traj;
	Damage = damage;
}

void Bullet::Update()
{
	Owner.Transform.Position += vec3(Trajectory * Speed, 0);
}
