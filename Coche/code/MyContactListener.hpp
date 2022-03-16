#pragma once

#include <box2d/box2d.h>
#include "Car.hpp"
#include "Terrain.hpp"

 class MyContactLister : public b2ContactListener
{
private:
	Car* car;
	SensorPlat* sensorPlat;

public:

	MyContactLister(Car* _car, SensorPlat* _sensor) : car(_car), sensorPlat(_sensor) {}
	void virtual BeginContact(b2Contact* contact);
	
	

};