/**
* @file
* @author María López, 2022
* @brief source de Scene.hpp
*/

#include "Scene.hpp"

void Scene::Start()
{
    constexpr auto window_width = 1200u;
    constexpr auto window_height = 800u;

    window = make_unique<RenderWindow>(VideoMode(window_width, window_height), "Car",
        Style::Titlebar | Style::Close, ContextSettings(32));

    window->setVerticalSyncEnabled(true);
   

    this->physics_world = make_unique<b2World>(b2Vec2{ 0, -10.f });

    //Terreno    
    terrain = make_unique<Terrain>();
    terrain->CreateTerrain(*physics_world);

    //Coche
    b2Vec2 carPos;
    carPos.x = 2;
    carPos.y = 1;
    car = make_unique<Car>(carPos);
      
    car->CreateCar(*physics_world, carPos);

    //Set del contact listener para que se ajuste al mío propio
    myContactList = make_unique<MyContactListener>(car.get (), terrain->sensorPlat);
    physics_world->SetContactListener(myContactList.get ());
}

void Scene::Update()
{
    const float physics_to_graphics_scale = 100.f;      // Escala para pasar de unidades de física a unidades de gráficos

   // Se ejecuta el bucle principal de la animación:    
    const float target_fps = 60.f;                     // Cuántos fotogramas por segundo se busca conseguir
    const float target_time = 1.f / target_fps;         // Duración en segundos de un fotograma a la tasa deseada

    float delta_time = target_time;                     // Previsión de la duración del fotograma actual
    bool  exit = false;

    Clock timer;

    do
    {

        terrain->Update();

        timer.restart();

        // Process window events:
        exit = process_events(*window, *physics_world, 800, physics_to_graphics_scale, car.get ());
        // Update:
        physics_world->Step(delta_time, 8, 4);

        // Render:
        window->clear();

        render(*physics_world, *window, physics_to_graphics_scale);

        window->display();

        // Si resulta necesario se detiene la ejecución unos instantes para no exceder la tasa de
        // fotogramas por segundo deseada:
        float elapsed = timer.getElapsedTime().asSeconds();

        if (elapsed < target_time)
        {
            sleep(seconds(target_time - elapsed));
        }

        // Se restablece la estimación de la duración del siguiente fotograma:
        delta_time = timer.getElapsedTime().asSeconds();
    } 
    while (!exit);
}