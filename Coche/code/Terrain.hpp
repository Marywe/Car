#pragma once

#include "Utils.hpp"

class Turret 
{
    b2Body* base;
    b2Vec2 pos;

public:
      
    b2RevoluteJoint* joint;
    b2Body* V[2];
    b2Body* circle;

    b2Body* CreateBase(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height);
    void CreateV(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height);

    inline b2Vec2 GetPos() { return pos; }
    inline b2Body* GetBase() { return base; }
    inline void SetPos(b2Vec2 _pos) { pos = _pos; }

};

class Platform
{
    b2Body* base;
    b2Body* floor;
    b2Vec2 pos;
    bool isDown = true;

public:

    void CreateBase(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height);
    void CreateFloor(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height);

    inline b2Body* GetBase() { return base; }
    inline b2Body* GetFloor() { return floor; }
    inline b2Vec2 GetPos() { return pos; }
    inline void SetPos(b2Vec2 _pos) { pos = _pos; }

    void Move();

};

class Sensor
{

};

static class Terrain
{
    
public:
    Turret* turret;
    Platform* platform;

    void CreateTerrain(b2World& physics_world);
};
