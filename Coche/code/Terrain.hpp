#pragma once

#include "Utils.hpp"

class Turret 
{
    const char data[4] = { 't', 'u', 'r', 'r' };
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

    /**
    *Crea el suelo, que es donde el coche se apoya para subir y el que tendrá contacto con él para identificar cuándo
    * se para y, una vez ocurra, suba la plataforma entera
    */
    void CreateFloor(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height);

    inline b2Body* GetBase() { return base; }
    inline b2Body* GetFloor() { return floor; }
    inline b2Vec2 GetPos() { return pos; }
    inline void SetPos(b2Vec2 _pos) { pos = _pos; }

    void Move();

};

class SensorPlat
{
    b2Body* base;
    b2Vec2 pos;

public:

    void CreateBase(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height);

    inline b2Body* GetBase() { return base; }

    inline b2Vec2 GetPos() { return pos; }
    inline void SetPos(b2Vec2 _pos) { pos = _pos; }


};

static class Terrain
{
    
public:
    Turret* turret;
    Platform* platform;
    SensorPlat* sensorPlat;

/**
* En esta función se crean todos los elementos del terreno, el circuito entero. Se crea y se coloca la base, edges para que el
* coche no se salga; y se colocan los diferentes elementos como plataformas voladoras, móviles, la torreta...
* Para ello se tiene en cuenta la resolución de la ventana que hemos creado anteriormente.
*/
    void CreateTerrain(b2World& physics_world);
};
