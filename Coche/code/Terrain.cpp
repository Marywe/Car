#include "Terrain.hpp"

b2Body* Turret::CreateBase(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height)
{
	this->base = create_box(physics_world, body_type, x, y, width, height);
	return base;
	

}

void Turret::CreateV(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height)
{

}

void Platform::CreateBase(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height)
{
	this->base = create_box(physics_world, body_type, x, y, width, height);

}
void Platform::CreateFloor(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height)
{
	this->floor = create_box(physics_world, body_type, x, y, width, height);
}

void Terrain::CreateTerrain(b2World& physics_world)
{
    //Edges del mundo
    constexpr float left = 0.01f;
    constexpr float right = 12.00f;
    constexpr float top = 8.00f;
    constexpr float bottom = 0.01f;

    create_edge(physics_world, b2_staticBody, left, bottom, right, bottom);
    create_edge(physics_world, b2_staticBody, left, bottom, left, top);
    create_edge(physics_world, b2_staticBody, left, top, right, top);
    create_edge(physics_world, b2_staticBody, right, bottom, right, top);


    turret = new Turret();
    turret->SetPos(b2Vec2(3, 2));
    turret->circle = create_circle(physics_world, b2_staticBody, turret->GetPos().x, turret->GetPos().y + 0.4, 0.2f);
    turret->CreateBase(physics_world, b2_staticBody, turret->GetPos().x, turret->GetPos().y, .2f, .5f);
    //turret->joint = create_revolute_joint(physics_world, terrain->turret->circle, car.Wheels[0], b2Vec2(-0.5f, -0.1), true);

    platform = new Platform();
    platform->SetPos(b2Vec2(6, 1));
    platform->CreateFloor(physics_world, b2_kinematicBody, platform->GetPos().x, platform->GetPos().y + 0.5f, 1, 0.05f);
    platform->CreateBase(physics_world, b2_kinematicBody, platform->GetPos().x, platform->GetPos().y, .05f, .5f);

}


