/**
* @file
* @author Mar�a L�pez, 2022
* @brief header para el objeto Terrain y los objetos que va a guardar el Terrain.
*/

#pragma once

#include "Utils.hpp"


//! Clase donde se define la torreta que contiene un joint y se mueve cuando el player se queda encima de una plataforma. Al activarse el joint y moverse hacia abajo, la plataforma que tiene encima cae y deja caer pelotas encima del coche.
class Turret 
{
    b2Body* base;
    b2Vec2 pos;

public:
      
    b2RevoluteJoint* joint;
    b2RevoluteJoint* joint2;
    b2Body* V;
    b2Body* circle;

    b2Body* CreateBase(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height);
    void CreateV(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height);

    inline b2Vec2 GetPos() { return pos; }
    inline b2Body* GetBase() { return base; }
    inline void SetPos(b2Vec2 _pos) { pos = _pos; }

    void ActivateTurret();

};



//! Esta clase es la que lleva el objeto plataforma del circuito (la que sube). Una vez haya llegado al sesor de las pelotas, esta plataforma subir� un poquito hasta la altura del suelo, y cuando el coche est� encima, subir� hasta la plataforma volante donde se encuentra la meta
class Platform
{
    b2Body* base;
    b2Body* floor;
    b2Vec2 pos;
    bool isDown = true;

public:


    void CreateBase(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height);

    //!Crea el suelo, que es donde el coche se apoya para subir y el que tendr� contacto con �l para identificar cu�ndo
    //! se para y, una vez ocurra, suba la plataforma entera
    void CreateFloor(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height);

    inline b2Body* GetBase() { return base; }
    inline b2Body* GetFloor() { return floor; }
    inline b2Vec2 GetPos() { return pos; }
    inline void SetPos(b2Vec2 _pos) { pos = _pos; }
    inline bool GetDown() { return isDown; }
    inline void SetDown(bool d) { isDown = d; }

    void Move();

};



//! Plataforma de sensor que activa los mecanismos
class SensorPlat
{
    b2Body* base;
    b2Vec2 pos;
    bool activated = false;

public:

    void CreateBase(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height);

    inline b2Body* GetBase() { return base; }

    inline b2Vec2 GetPos() { return pos; }
    inline void SetPos(b2Vec2 _pos) { pos = _pos; }
    inline bool GetActivated() { return activated; }
    inline void SetActivated(bool _act) { activated = _act;  }

};



//!Se crea un �nico terreno, el propio escenario. Este terreno est� formado por diferentes bloques y elementos, como las Turrets, Platforms o Sensors.
class Terrain
{
    
public:
    Turret* turret;
    Platform* platform;
    SensorPlat* sensorPlat;


//!En esta funci�n se crean todos los elementos del terreno, el circuito entero. Se crea y se coloca la base, edges para que el
//!coche no se salga; y se colocan los diferentes elementos como plataformas voladoras, m�viles, la torreta...
//!Para ello se tiene en cuenta la resoluci�n de la ventana que hemos creado anteriormente.
    void CreateTerrain(b2World& physics_world);

    //! Este Update personal servir� para encapsular un poco el c�digo. Aqu� ocurrir�n las comprobaciones del terreno, como si ha saltado la rampa,
    //! si h activado la torreta, etc.
    void Update();
};
