#pragma once

#include <box2d/box2d.h>

class Car 
{
private:

    b2Vec2 pos;   

public:

    Car(b2Vec2 pos);

    b2Body* chasis;

    b2RevoluteJoint* joints[2];
    b2Body* Wheels[2];

    b2Body* CreateWheel(b2World& physics_world, b2BodyType body_type, float x, float y, float radius);

    b2Body* CreateCar(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height);

    void Brake();

    void Move(int dir = 0);


};