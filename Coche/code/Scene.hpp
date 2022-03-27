#pragma once

#include <vector>
#include "Car.hpp"
#include "Utils.hpp"
#include "Terrain.hpp"
#include "MyContactListener.hpp"

//! Clase escena. La encapsulación más globa de un programa o juego. Aquí ocurre el management de todo el programa.
class Scene
{
private:

	unique_ptr<RenderWindow> window;
	unique_ptr<b2World> physics_world;
	unique_ptr<MyContactListener> myContactList;
	unique_ptr<Terrain> terrain;
	unique_ptr<Car> car;
	
public:
	//! Función que inicializa la única escena que tenemos. Se asignan los valores de inicio, se crea la ventana y los elementos del propio juego.
	void Start();

	//! Función que principalmente consiste en un do while que iterará sobre sí mismo cada frame. En este update se cuentan frames, se actualizan
	//! los eventos de Input, el render y se controla el flujo del juego.
	void Update();
};
