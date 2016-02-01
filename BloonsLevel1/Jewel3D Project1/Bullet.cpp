#include "Bullet.h"



Bullet::Bullet(Entity & owner) : Component(owner)
{

}

Bullet::Bullet(Entity &owner, vec2& traj, int damage, Entity* spawningTower) : Component(owner)
{
	Trajectory = traj;
	Damage = damage;
	SpawningTower = spawningTower;
}

void Bullet::Update()
{
	Owner.Transform.Position += vec3(Trajectory * Speed, 0);
}
