#pragma once

#include "Utils.hpp"

/**
* Clase donde se define la torreta que contiene un joint y se mueve cuando el player se queda encima de una plataforma.
* Al activarse el joint y moverse hacia abajo, la plataforma que tiene encima cae y deja caer pelotas encima del coche.
*/
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


/**
* Esta clase es la que lleva el objeto plataforma del circuito (la que sube). Una vez haya llegado al sesor de las pelotas,
* esta plataforma subir� un poquito hasta la altura del suelo, y cuando el coche est� encima, subir� hasta la plataforma volante 
* donde se encuentra la meta
*/
class Platform
{
    b2Body* base;
    b2Body* floor;
    b2Vec2 pos;
    bool isDown = true;

public:


    void CreateBase(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height);

    /**
    *Crea el suelo, que es donde el coche se apoya para subir y el que tendr� contacto con �l para identificar cu�ndo
    * se para y, una vez ocurra, suba la plataforma entera
    */
    void CreateFloor(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height);

    inline b2Body* GetBase() { return base; }
    inline b2Body* GetFloor() { return floor; }
    inline b2Vec2 GetPos() { return pos; }
    inline void SetPos(b2Vec2 _pos) { pos = _pos; }
    inline bool GetDown() { return isDown; }
    inline void SetDown(bool d) { isDown = d; }

    void Move();

};

class SensorPlat
{
    b2Body* base;
    b2Vec2 pos;
    bool activated = false;

public:

    const string data = "SENSOR";

    void CreateBase(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height);

    inline b2Body* GetBase() { return base; }

    inline b2Vec2 GetPos() { return pos; }
    inline void SetPos(b2Vec2 _pos) { pos = _pos; }
    inline bool GetActivated() { return activated; }

};

static class Terrain
{
    
public:
    Turret* turret;
    Platform* platform;
    SensorPlat* sensorPlat;

/**
* En esta funci�n se crean todos los elementos del terreno, el circuito entero. Se crea y se coloca la base, edges para que el
* coche no se salga; y se colocan los diferentes elementos como plataformas voladoras, m�viles, la torreta...
* Para ello se tiene en cuenta la resoluci�n de la ventana que hemos creado anteriormente.
*/
    void CreateTerrain(b2World& physics_world);
    void Update();
};
