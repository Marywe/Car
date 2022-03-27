#pragma once

#include <vector>
#include "Car.hpp"
#include "Utils.hpp"
#include "Terrain.hpp"
#include "MyContactListener.hpp"

//! Clase escena. La encapsulaci�n m�s globa de un programa o juego. Aqu� ocurre el management de todo el programa.
class Scene
{
private:

	unique_ptr<RenderWindow> window;
	unique_ptr<b2World> physics_world;
	unique_ptr<MyContactListener> myContactList;
	unique_ptr<Terrain> terrain;
	unique_ptr<Car> car;
	
public:
	//! Funci�n que inicializa la �nica escena que tenemos. Se asignan los valores de inicio, se crea la ventana y los elementos del propio juego.
	void Start();

	//! Funci�n que principalmente consiste en un do while que iterar� sobre s� mismo cada frame. En este update se cuentan frames, se actualizan
	//! los eventos de Input, el render y se controla el flujo del juego.
	void Update();
};
