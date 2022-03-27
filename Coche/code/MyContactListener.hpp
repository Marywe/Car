#pragma once

#include <box2d/box2d.h>
#include "Car.hpp"
#include "Terrain.hpp"

 class MyContactListener : public b2ContactListener
{
private:
	Car* car;
	SensorPlat* sensorPlat;

public:

	MyContactListener(Car* _car, SensorPlat* _sensor) : car(_car), sensorPlat(_sensor) {}
	void virtual BeginContact(b2Contact* contact);
		

};