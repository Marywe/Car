/**
* @file
* @author María López, 2022
* @brief source de Car.hpp
*/

#include "Car.hpp"

Car::Car(b2Vec2 _pos)
{
    this->pos = _pos;
    this->initialPos = _pos;
}

void Car::Brake() 
{
    joints[0]->SetMotorSpeed(0);
    joints[1]->SetMotorSpeed(0);
}

void Car::Move(int dir) 
{
    joints[0]->SetMotorSpeed(70*dir);
    joints[1]->SetMotorSpeed(70*dir);
    
}

b2Body* Car::CreateWheel(b2World& physics_world, b2BodyType body_type, float x, float y, float radius)
{
    // Se crea el body:

    b2BodyDef body_definition;

    body_definition.type = body_type;
    body_definition.position.Set(x, y);                            // Posición inicial absoluta

    b2Body* body = physics_world.CreateBody(&body_definition);

    // Se añande una fixture:

    b2CircleShape body_shape;

    body_shape.m_radius = radius;

    b2FixtureDef body_fixture;

    body_fixture.shape = &body_shape;
    body_fixture.density = 0.10f;
    body_fixture.restitution = 0.75f;
    body_fixture.friction = 0.50f;

    Tag* tag = new Tag;
    tag->TAG = "wheel";
    body_fixture.userData.pointer = uintptr_t(tag);

    body->CreateFixture(&body_fixture);

    return body;
}

void Car::CreateCar(b2World& physics_world, b2Vec2 carPos)
{
    Wheels[2] = CreateWheel(physics_world, b2_dynamicBody, carPos.x, carPos.y, 0.07f);

    chasis = CreateChasis(physics_world, b2_dynamicBody, carPos.x, carPos.y, 0.55f, 0.1f);
    Wheels[0] = CreateWheel(physics_world, b2_dynamicBody, 0.1f, 1, 0.15f);
    Wheels[1] = CreateWheel(physics_world, b2_dynamicBody, 0.4, 1, 0.15f);

    joints[0] = create_revolute_joint(physics_world, chasis, Wheels[0], b2Vec2(-0.5f, -0.15), true);
    joints[1] = create_revolute_joint(physics_world, chasis, Wheels[1], b2Vec2(0.5f, -0.15), true);

    joints[2] = create_revolute_joint(physics_world, chasis, Wheels[2], b2Vec2(-0.55f, 0.1f), true);

    joints[0]->SetMaxMotorTorque(50);
    joints[1]->SetMaxMotorTorque(100);

}

b2Body* Car::CreateChasis(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height)
{
    // Se crea el body:

    b2BodyDef body_definition;

    body_definition.type = body_type;
    body_definition.position.Set(x, y);                            // Posición inicial absoluta

    b2Body* body = physics_world.CreateBody(&body_definition);

    // Se añande una fixture:

    b2PolygonShape body_shape;

    body_shape.SetAsBox(width, height);

    b2FixtureDef body_fixture;

    body_fixture.shape = &body_shape;
    body_fixture.density = 1.00f;
    body_fixture.restitution = 0.50f;
    body_fixture.friction = 0.50f;

    body->CreateFixture(&body_fixture);

    return body;
}

void Car::Reset()
{
    pos = initialPos;
    Brake();
    chasis->SetTransform(initialPos, 0);
}
