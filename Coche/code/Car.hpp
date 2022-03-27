/**
* @file
* @author Mar�a L�pez, 2022
* @brief header del Car o Player. Tiene las funciones y atributos para guardar y crear sus partes adem�s de para moverlo
*/

#pragma once

#include <box2d/box2d.h>
#include "Utils.hpp"


//! Clase del player, que en nuestro juego ser� un coche que podr� controlar de dos formas: movi�ndolo de forma Horizontal (A - D) y frenando con el espacio o no movi�ndote.
class Car 
{
private:

    b2Vec2 pos;
    b2Vec2 initialPos;

public:

    //! Constructor con posici�n. Intent� hacerlo hardcodeando las posiciones y midiendo bien pero es mucho m�s f�cil tener una pos de referencia.
    Car(b2Vec2 pos);

    b2Body* chasis;

    b2RevoluteJoint* joints[2];
    b2Body* Wheels[2];

    b2Body* CreateWheel(b2World& physics_world, b2BodyType body_type, float x, float y, float radius);
    b2Body* CreateChasis(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height);

    //! Encapsulsa todos los elementos que se crean del coche en una �nica funci�n que llama al resto.
    void CreateCar(b2World& physics_world, b2Vec2 pos);

    void Brake();
    //! Este Move se llama en el procesador de eventos cuando se pulsa para mover el coche, envi�ndole adem�s la direcci�n en la que quiere ir.
    void Move(int dir = 0);

    //! Funci�n qu devuelve el coche a su posici�n original. Puede ocurrir si le das a la "R" o si te caes por el precipicio.
    void Reset();


};