/**
* @file
* @author Mar�a L�pez, 2022
* @brief source de Terrain.hpp
*/

#include "Terrain.hpp"

b2Body* Turret::CreateBase(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height)
{
  
	this->base = create_box(physics_world, body_type, x, y, width, height);
	return base;
	
}

void Turret::CreateV(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height)
{

   // Posici�n inicial absoluta    
    b2BodyDef V_body_def;

    V_body_def.type = body_type;
    V_body_def.position.Set(base->GetPosition().x, base->GetPosition().y);                                    // Posici�n inicial absoluta
    V_body_def.angle = 0.0f;

    b2Body* vBody = physics_world.CreateBody(&V_body_def);
    // Se a�ande una fixture al body:

    b2PolygonShape v_left_shape;
    v_left_shape.SetAsBox(width, height, b2Vec2(-0.5f, 1.2f), 45);
    b2PolygonShape v_right_shape;
    v_right_shape.SetAsBox(width, height, b2Vec2(0.5f, 1.2f), -45);

    b2FixtureDef v_left_fixture;
    b2FixtureDef v_right_fixture;

    v_left_fixture.shape = &v_left_shape;
    v_right_fixture.shape = &v_right_shape;

    vBody->CreateFixture(&v_left_fixture);
    vBody->CreateFixture(&v_right_fixture);

    this->V = vBody;
}

void Platform::CreateBase(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height)
{
	this->base = create_box(physics_world, body_type, x, y, width, height);

}
void Platform::CreateFloor(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height)
{
	this->floor = create_box(physics_world, body_type, x, y, width, height);
}
void SensorPlat::CreateBase(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height)
{
    // Se crea el body:

    b2BodyDef body_definition;

    body_definition.type = body_type;
    body_definition.position.Set(x, y);                            // Posici�n inicial absoluta
   base = physics_world.CreateBody(&body_definition);

    // Se a�ande una fixture:

    b2PolygonShape body_shape;

    body_shape.SetAsBox(width, height);

    b2FixtureDef body_fixture;

    body_fixture.shape = &body_shape;
    body_fixture.density = 1.00f;
    body_fixture.restitution = 0.50f;
    body_fixture.friction = 1.50f;

    Tag* tag = new Tag;
    tag->TAG = "sensor";
    body_fixture.userData.pointer = uintptr_t(tag);

    base->CreateFixture(&body_fixture);

   
}

void Platform::Move() {

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
    turret->SetPos(b2Vec2(9, 2));
    turret->circle = create_circle(physics_world, b2_dynamicBody, turret->GetPos().x, turret->GetPos().y + 0.65, 0.2f);
    turret->CreateBase(physics_world, b2_kinematicBody, turret->GetPos().x, turret->GetPos().y, .1f, .65f);
    turret->CreateV(physics_world, b2_dynamicBody, turret->GetPos().x, turret->GetPos().y, 0.1f, 0.6f);
    turret->joint = create_revolute_joint(physics_world, turret->V, turret->circle, b2Vec2(0, 0.65), true);
   // turret->joint2 = create_revolute_joint(physics_world, turret->GetBase(), turret->circle, b2Vec2(0, 0.65), true);
    

    platform = new Platform();
    platform->SetPos(b2Vec2(6, -0.5f));
    platform->CreateFloor(physics_world, b2_kinematicBody, platform->GetPos().x, platform->GetPos().y + 0.5f, 1, 0.1f);
    platform->CreateBase(physics_world, b2_kinematicBody, platform->GetPos().x, platform->GetPos().y, .1f, .5f);


    sensorPlat = new SensorPlat();
    sensorPlat->SetPos(b2Vec2(9,0));
    sensorPlat->CreateBase(physics_world, b2_kinematicBody, sensorPlat->GetPos().x, sensorPlat->GetPos().y, 1.3f, .1f);
}

void Terrain::Update() 
{    

    if (sensorPlat->GetActivated())
    {
        platform->SetDown(false);
    }

    if (!platform->GetDown())
    {
        platform->Move();

        turret->joint->SetMotorSpeed(600);
        turret->joint->SetMaxMotorTorque(100);
    }


    


}


