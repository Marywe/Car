/**
* @file
* @author María López, 2022
* @brief source de MyContactListener.hpp
*/

#include "MyContactListener.hpp"

void MyContactListener::BeginContact(b2Contact* contact)
{
	Tag* tagA = (Tag*)contact->GetFixtureA()->GetUserData().pointer;
	Tag* tagB = (Tag*)contact->GetFixtureB()->GetUserData().pointer;

	//Colisión del coche
	if (tagA && tagB) 
	{
		if (tagA->TAG == "wheel" || tagB->TAG == "wheel")
		{
			if (tagA->TAG == "sensor")
			{
				// Haz cosas
			}
			else if (tagB->TAG == "sensor")
			{
				// Haz cosas
			}
		}
	}
	
}
