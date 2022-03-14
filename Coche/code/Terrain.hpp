#pragma once

#include "Utils.hpp"



class Turret 
{
    b2Body* base;

public:
      
    b2RevoluteJoint* joint;
    b2Body* V[2];
    b2Body* circle;

    b2Body* CreateBase(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height);
    void CreateV(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height);



};

class Platform
{

};

static class Terrain
{

public:
    Turret* turret;
};
