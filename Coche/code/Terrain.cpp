#include "Terrain.hpp"

b2Body* Turret::CreateBase(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height)
{
	this->base = create_box(physics_world, body_type, x, y, width, height);
	return base;
	

}

void Turret::CreateV(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height)
{

}
