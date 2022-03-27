/**
* @file
* @author María López, 2022
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
   // Posición inicial absoluta    
    b2BodyDef V_body_def;

    V_body_def.type = body_type;
    V_body_def.position.Set(base->GetPosition().x, base->GetPosition().y);                                    // Posición inicial absoluta
    V_body_def.angle = 0.0f;

    b2Body* vBody = physics_world.CreateBody(&V_body_def);
    // Se añande una fixture al body:

    b2PolygonShape v_left_shape;
    v_left_shape.SetAsBox(width, height, b2Vec2(-0.5f, 1.2f), 45);
    b2PolygonShape v_right_shape;
    v_right_shape.SetAsBox(width, height, b2Vec2(0.5f, 1.2f), -45);

    b2FixtureDef v_left_fixture;
    b2FixtureDef v_right_fixture;

    v_left_fixture.shape = &v_left_shape;
    v_right_fixture.shape = &v_right_shape;

    v_left_fixture.density = 0.100f;
    v_left_fixture.restitution = 0.050f;
    v_left_fixture.friction = 1.0f;

    v_right_fixture.density = 0.100f;
    v_right_fixture.restitution = 0.05f;
    v_right_fixture.friction = 1.0f;

    vBody->CreateFixture(&v_left_fixture);
    vBody->CreateFixture(&v_right_fixture);

    this->V = vBody;
}

void Turret::ActivateTurret()
{
    joint->EnableLimit(false);
    joint->SetMaxMotorTorque(50);
    joint->SetMotorSpeed(10);
}

////////////////////////////////////////////////////////////////////////////

void Platform::CreateBase(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height)
{
	this->base = create_box(physics_world, body_type, x, y, width, height);

}

void Platform::CreateFloor(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height)
{
	this->floor = create_box(physics_world, body_type, x, y, width, height);
}

void Platform::Move() 
{

}

////////////////////////////////////////////////////////////////////////////

void SensorPlat::CreateBase(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height)
{
    // Se crea el body:

    b2BodyDef body_definition;

    body_definition.type = body_type;
    body_definition.position.Set(x, y);                            // Posición inicial absoluta
   base = physics_world.CreateBody(&body_definition);

    // Se añande una fixture:

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

////////////////////////////////////////////////////////////////////////////

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
    turret->circle = create_circle(physics_world, b2_dynamicBody, turret->GetPos().x, turret->GetPos().y + 0.7, 0.15f);
    turret->CreateBase(physics_world, b2_kinematicBody, turret->GetPos().x, turret->GetPos().y, .1f, .7f);
    turret->CreateV(physics_world, b2_dynamicBody, turret->GetPos().x, turret->GetPos().y, 0.1f, 0.6f);
    turret->joint = create_revolute_joint(physics_world, turret->V, turret->circle, b2Vec2(0, 0.65f), true);
    turret->joint->SetLimits(0, 0);
    turret->joint->EnableLimit(true);
    turret->joint2 = create_revolute_joint(physics_world, turret->GetBase(), turret->circle, b2Vec2(0, 0.65), true);
    

    platform = new Platform();
    platform->SetPos(b2Vec2(6, -0.5f));
    platform->CreateFloor(physics_world, b2_kinematicBody, platform->GetPos().x, platform->GetPos().y + 0.5f, 1, 0.1f);
    platform->CreateBase(physics_world, b2_kinematicBody, platform->GetPos().x, platform->GetPos().y, .1f, .5f);


    sensorPlat = new SensorPlat();
    sensorPlat->SetPos(b2Vec2(10,0));
    sensorPlat->CreateBase(physics_world, b2_kinematicBody, sensorPlat->GetPos().x, sensorPlat->GetPos().y, 1.5f, .1f);
}

void Terrain::Update() 
{    

    if (sensorPlat->GetActivated() && platform->GetDown())
    {
        platform->SetDown(false);
        turret->ActivateTurret();
    }

    if (!platform->GetDown())
    {
        platform->Move();

    }    


}


