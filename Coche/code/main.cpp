// María López
// 2022


#include <ciso646>
#include <memory>
#include <vector>
#include "Car.hpp"
#include "Utils.hpp"

using namespace sf;
using namespace std;

int main ()
{
    //Se crea la ventana y el mundo
    constexpr auto window_width  = 800u;
    constexpr auto window_height = 600u;

    RenderWindow window(VideoMode(window_width, window_height), "Box2D Joints", 
                                  Style::Titlebar | Style::Close, ContextSettings(32));
    window.setVerticalSyncEnabled (true);

    b2World physics_world{ b2Vec2{ 0, -10.f } };

    //Edges del mundo
    constexpr float left   = 0.01f;
    constexpr float right  = 8.00f;
    constexpr float top    = 6.00f;
    constexpr float bottom = 0.01f;

    create_edge (physics_world, b2_staticBody, left,  bottom, right, bottom);
    create_edge (physics_world, b2_staticBody, left,  bottom, left,  top   );
    create_edge (physics_world, b2_staticBody, left,  top,    right, top   );
    create_edge (physics_world, b2_staticBody, right, bottom, right, top   );

    //Coche

    b2Vec2 carPos;
    carPos.x = 2;
    carPos.y = 1;
    Car car(carPos);

    auto* chasis = car.CreateCar(physics_world, b2_dynamicBody, carPos.x, carPos.y, 1, 0.1f);
    car.Wheels[0] = car.CreateWheel(physics_world, b2_dynamicBody, 1.5f, 1, .3f);
    car.Wheels[1] = car.CreateWheel(physics_world, b2_dynamicBody, 0.5f, 1, .3f);

    auto* jointA = create_revolute_joint(physics_world, chasis, car.Wheels[0], b2Vec2(-0.5f, -0.25), true);
    jointA->SetMaxMotorTorque(75.f);
    jointA->SetMotorSpeed(-1.f);

    auto* jointB = create_revolute_joint(physics_world, chasis, car.Wheels[1], b2Vec2(0.5f, -0.25), true);
    jointB->SetMaxMotorTorque(75.f);
    jointB->SetMotorSpeed(-1.f);


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

        exit = process_events (window, physics_world, window_height, physics_to_graphics_scale);

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
    while (not exit);

    return 0;
}
