#pragma once

#include <vector>
#include "Car.hpp"
#include "Utils.hpp"
#include "Terrain.hpp"
#include "MyContactListener.hpp"


class Scene
{
private:

	unique_ptr<RenderWindow> window;
	unique_ptr<b2World> physics_world;
	unique_ptr<MyContactListener> myContactList;
	unique_ptr<Terrain> terrain;
	unique_ptr<Car> car;
	
public:

	void Start();
	void Update();
};
