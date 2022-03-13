#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Car.hpp"

using namespace sf;
using namespace std;

/** En Box2D las coordenadas Y crecen hacia arriba y en SFML crecen hacia abajo desde el borde
     * superior. Esta función se encarga de convertir el sistema de coordenadas para que la escena
     * no se vea invertida.
     */

inline Vector2f box2d_position_to_sfml_position(const b2Vec2& box2d_position, float window_height, float scale)
{
    return Vector2f(box2d_position.x * scale, window_height - box2d_position.y * scale);
}

inline b2Vec2 sfml_position_to_box2d_position(const Vector2f& sfml_position, float window_height, float scale)
{
    return b2Vec2(sfml_position.x / scale, (window_height - sfml_position.y) / scale);
}

bool process_events(Window& window, b2World& physics_world, float window_height, float scale, Car * car = nullptr);

b2Body* create_circle(b2World& physics_world, b2BodyType body_type, float x, float y, float radius);

b2Body* create_box(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height);

b2Body* create_edge(b2World& physics_world, b2BodyType body_type, float x0, float y0, float x1, float y1);

b2RevoluteJoint* create_revolute_joint(b2World& physics_world, b2Body* body_a, b2Body* body_b, b2Vec2 offset,bool enable_motor = false); 

void render_circle(b2Vec2 center, float radius,const b2Transform& transform, RenderWindow& renderer, float window_height, float scale);

void render_segment(const Vector2f& start, const Vector2f& end, const Color& color, RenderWindow& renderer);

void render_segment
(
    b2Vec2              start,
    b2Vec2              end,
    const b2Transform& transform,
    RenderWindow& renderer,
    float               window_height,
    float               scale
);

void render_polygon
(
    const b2Vec2* vertices,
    int                 number_of_vertices,
    const b2Transform& transform,
    RenderWindow& renderer,
    float               window_height,
    float               scale
);
void render(b2World& physics_world, RenderWindow& renderer, float scale);



