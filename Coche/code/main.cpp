// María López
// 2022


#include <vector>
#include "Car.hpp"
#include "Utils.hpp"
#include "Terrain.hpp"
#include "MyContactListener.hpp"

using namespace sf;
using namespace std;

int main ()
{
    //Se crea la ventana y el mundo
    constexpr auto window_width  = 1200u;
    constexpr auto window_height = 800u;

    RenderWindow window(VideoMode(window_width, window_height), "Car", 
                                  Style::Titlebar | Style::Close, ContextSettings(32));
    window.setVerticalSyncEnabled (true);

    b2World physics_world{ b2Vec2{ 0, -10.f } };

    //Terreno    
    Terrain* terrain = new Terrain();
    terrain->CreateTerrain(physics_world);

    //Coche

    b2Vec2 carPos;
    carPos.x = 2;
    carPos.y = 1;
    Car car(carPos);

    car.chasis = car.CreateChasis(physics_world, b2_dynamicBody, carPos.x, carPos.y, 0.5f, 0.1f);
    car.Wheels[0] = car.CreateWheel(physics_world, b2_dynamicBody, 0.1f, 1, 0.1f);
    car.Wheels[1] = car.CreateWheel(physics_world, b2_dynamicBody, 0.4, 1, 0.1f);

    car.joints[0] = create_revolute_joint(physics_world, car.chasis, car.Wheels[0], b2Vec2(-0.5f, -0.1), true);
    car.joints[1] = create_revolute_joint(physics_world, car.chasis, car.Wheels[1], b2Vec2(0.5f, -0.1), true);
    car.joints[0]->SetMaxMotorTorque(1.f);
    car.joints[1]->SetMaxMotorTorque(1);



    MyContactLister* myContactList = new MyContactLister(&car, terrain->sensorPlat);


    const float physics_to_graphics_scale = 100.f;      // Escala para pasar de unidades de física a unidades de gráficos

    // Se ejecuta el bucle principal de la animación:    
    const float target_fps  = 60.f;                     // Cuántos fotogramas por segundo se busca conseguir
    const float target_time = 1.f / target_fps;         // Duración en segundos de un fotograma a la tasa deseada

    float delta_time = target_time;                     // Previsión de la duración del fotograma actual
    bool  exit       = false;

    Clock timer;

    do
    {
        timer.restart ();

        // Process window events:
        exit = process_events (window, physics_world, window_height, physics_to_graphics_scale, &car);

        // Update:
        physics_world.Step (delta_time, 8, 4);

        // Render:
        window.clear ();

        render (physics_world, window, physics_to_graphics_scale);

        window.display ();

        // Si resulta necesario se detiene la ejecución unos instantes para no exceder la tasa de
        // fotogramas por segundo deseada:
        float elapsed = timer.getElapsedTime ().asSeconds ();

        if (elapsed < target_time)
        {
            sleep (seconds (target_time - elapsed));
        }

        // Se restablece la estimación de la duración del siguiente fotograma:
        delta_time = timer.getElapsedTime ().asSeconds ();
    }
    while (!exit);

    return 0;
}

