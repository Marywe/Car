/**
* @file
* @author María López, 2022
* @brief header de mi propio Contact Listener.
*/

#pragma once

#include <box2d/box2d.h>
#include "Car.hpp"
#include "Terrain.hpp"


//! Clase que hereda de b2ContactListener para personalizarlo a nuestro gusto. Se encarga de procesar todas las colisiones importantes en nuestro juego.
class MyContactListener : public b2ContactListener
{
private:
	Car* car;
	SensorPlat* sensorPlat;

public:

	MyContactListener(Car* _car, SensorPlat* _sensor) : car(_car), sensorPlat(_sensor) {}

	//! Función virtual. Cuando dos bodys entran en contacto, salta esta función automáticamente, y es la que gestiona los diferentes resultadosde las colisiones que nos interesan.
	void virtual BeginContact(b2Contact* contact);


};