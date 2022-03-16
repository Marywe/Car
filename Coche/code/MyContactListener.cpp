#include "MyContactListener.hpp"

void MyContactLister::BeginContact(b2Contact* contact)
{
	b2BodyUserData userDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	b2BodyUserData userDataB = contact->GetFixtureA()->GetBody()->GetUserData();
	
	//Colisión del coche
	if (userDataA.pointer == car->chasis->GetFixtureList()->GetBody()->GetUserData().pointer ||
		userDataB.pointer == car->chasis->GetFixtureList()->GetBody()->GetUserData().pointer)
	{
		if (userDataA.pointer == sensorPlat->GetBase()->GetFixtureList()->GetBody()->GetUserData().pointer ||
			userDataB.pointer == sensorPlat->GetBase()->GetFixtureList()->GetBody()->GetUserData().pointer)
		{
			car->Reset();

		}
	}
}
