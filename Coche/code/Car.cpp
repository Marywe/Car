#include "Car.hpp"

Car::Car(b2Vec2 _pos)
{
    _pos = this->pos;
}

void Car::Brake() 
{
    joints[0]->SetMotorSpeed(0);
    joints[1]->SetMotorSpeed(0);
    chasis->SetLinearVelocity(b2Vec2_zero);
    chasis->SetAngularVelocity(0);
}

void Car::Move(int dir) 
{
    chasis->SetLinearVelocity(b2Vec2(3*dir,0));
    joints[0]->SetMotorSpeed(500*dir);
    joints[1]->SetMotorSpeed(500*dir);
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

    body->CreateFixture(&body_fixture);

    return body;
}

b2Body* Car::CreateCar(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height)
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
