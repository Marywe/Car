/**
* @file
* @author Mar?a L?pez, 2022
* @brief source de Utils.hpp
*/

#include "Utils.hpp"

/**
*Funci?n donde se procesan todos los eventos de input y de ventana. Comprueba el input del coche para llamarlo y hacer que se mueva / frene,
* controla el input del Reset (pulsar a la R) para volver a empezar con el coche, y por ?ltimo, cierra el bucle de llamada
* cuando el programa se cierra.
*/
bool process_events(Window& window, b2World& physics_world, float window_height, float scale, Car* car, Terrain* terrain)
{
    Event event;

    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        
        //Input de movimiento
        case Event::KeyPressed:
        {
            if (Keyboard::isKeyPressed(Keyboard::A))
            {
                car->Move(1);
            }
            if (Keyboard::isKeyPressed(Keyboard::D))
            {
                car->Move(-1);
            }
            if (Keyboard::isKeyPressed(Keyboard::Space) || (!Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::D)))
            {
                car->Brake();
            }


            if (Keyboard::isKeyPressed(Keyboard::R))
            {
                car->Reset();
            }

            if (Keyboard::isKeyPressed(Keyboard::Q))
            {
                terrain->sensorPlat->SetActivated(true);
            }

            break;
        }
        case Event::KeyReleased:
        {
            if (event.key.code == Keyboard::A || event.key.code == Keyboard::D) {
                car->Brake();
            }
            break;
        }

        case Event::Closed:
        {
            return true;
        }
        }
    }

    return false;
}


b2Body* create_box(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height)
{
    // Se crea el body:

    b2BodyDef body_definition;

    body_definition.type = body_type;
    body_definition.position.Set(x, y);                            // Posici?n inicial absoluta

    b2Body* body = physics_world.CreateBody(&body_definition);

    // Se a?ande una fixture:

    b2PolygonShape body_shape;

    body_shape.SetAsBox(width, height);

    b2FixtureDef body_fixture;

    body_fixture.shape = &body_shape;
    body_fixture.density = 1.00f;
    body_fixture.restitution = 0.50f;
    body_fixture.friction = 0.50f;
   
    body->CreateFixture(&body_fixture);

    return body;
}

b2Body* create_circle(b2World& physics_world, b2BodyType body_type, float x, float y, float radius)
{
    
    // Se crea el body:

    b2BodyDef body_definition;

    body_definition.type = body_type;
    body_definition.position.Set(x, y);                            // Posici?n inicial absoluta
   

    b2Body* body = physics_world.CreateBody(&body_definition);

    // Se a?ande una fixture:

    b2CircleShape body_shape;

    body_shape.m_radius = radius;

    b2FixtureDef body_fixture;

    body_fixture.shape = &body_shape;
    body_fixture.density = 0.50f;
    body_fixture.restitution = 0.75f;
    body_fixture.friction = 0.50f;

    body->CreateFixture(&body_fixture);

    return body;
}

b2Body* create_edge(b2World& physics_world, b2BodyType body_type, float x0, float y0, float x1, float y1)
{
    // Se crea el body:
    b2BodyDef body_definition;

    body_definition.type = body_type;
    body_definition.position.Set(0.f, 0.f);                        // Posici?n inicial absoluta

    b2Body* body = physics_world.CreateBody(&body_definition);

    // Se a?ande una fixture:

    b2EdgeShape body_shape;
    

    body_shape.SetTwoSided(b2Vec2(x0, y0), b2Vec2(x1, y1));        // Coordenadas locales respecto al centro del body
 
    b2FixtureDef body_fixture;

    body_fixture.shape = &body_shape;
   

    body->CreateFixture(&body_fixture);

    return body;
}

b2Body* create_curve(b2World& physics_world, b2BodyType body_type, float x0, float y0, float x1, float y1)
{
    b2BodyDef bd;
    bd.position.Set(x0, y0);

    b2Body* m_body = physics_world.CreateBody(&bd);

    b2EdgeShape shape;

    b2Vec2 p1, p2;

    int m_nBorderVertices = 30;

   /* for (int i = 0; i < m_nBorderVertices - 1; i++) {
        p1 = b2Vec2(((m_borderVertices[i].x - winSize.width / 2) / PTM_RATIO), ((m_borderVertices[i].y - winSize.height / 2) / PTM_RATIO));
        p2 = b2Vec2(((m_borderVertices[i + 1].x - winSize.width / 2) / PTM_RATIO), ((m_borderVertices[i + 1].y - winSize.height / 2) / PTM_RATIO));
        shape.Set(p1, p2);
        
        m_body->CreateFixture(&shape, 0);
    }*/

    return m_body;
}

b2RevoluteJoint* create_revolute_joint(b2World& physics_world, b2Body* body_a, b2Body* body_b, b2Vec2 offset, bool enable_motor)
{
    b2RevoluteJointDef joint_def;

    joint_def.localAnchorA.Set(offset.x, offset.y);
    joint_def.bodyA = body_a;
    joint_def.bodyB = body_b;
    joint_def.enableMotor = enable_motor;
    joint_def.collideConnected = false;

    return dynamic_cast<b2RevoluteJoint*>(physics_world.CreateJoint(&joint_def));
}

// ------------------------------------------------------------------------------------------ //

void render_circle
(
    b2Vec2              center,
    float               radius,
    const b2Transform& transform,
    RenderWindow& renderer,
    float               window_height,
    float               scale
)
{
    CircleShape shape;

    radius *= scale;

    shape.setPosition(box2d_position_to_sfml_position(b2Mul(transform, center), window_height, scale) - Vector2f(radius, radius));
    shape.setRadius(radius);
    shape.setFillColor(Color::Blue);

    renderer.draw(shape);
}

void render_segment
(
    const Vector2f& start,
    const Vector2f& end,
    const Color& color,
    RenderWindow& renderer
)
{
    Vertex line[] =
    {
        Vertex(start, color),
        Vertex(end, color),
    };

    renderer.draw(line, 2, Lines);
}

void render_segment
(
    b2Vec2              start,
    b2Vec2              end,
    const b2Transform& transform,
    RenderWindow& renderer,
    float               window_height,
    float               scale
)
{
    start = b2Mul(transform, start);
    end = b2Mul(transform, end);

    render_segment
    (
        box2d_position_to_sfml_position(start, window_height, scale),
        box2d_position_to_sfml_position(end, window_height, scale),
        Color::Green,
        renderer
    );
}

void render_polygon
(
    const b2Vec2* vertices,
    int                 number_of_vertices,
    const b2Transform& transform,
    RenderWindow& renderer,
    float               window_height,
    float               scale
)
{
    ConvexShape sfml_polygon;

    sfml_polygon.setPointCount(number_of_vertices);
    sfml_polygon.setFillColor(Color::Yellow);

    for (int index = 0; index < number_of_vertices; index++)
    {
        sfml_polygon.setPoint
        (
            index,
            box2d_position_to_sfml_position(b2Mul(transform, vertices[index]), window_height, scale)
        );
    }

    renderer.draw(sfml_polygon);
}

void render(b2World& physics_world, RenderWindow& renderer, float scale)
{
    // Se cachea el alto de la ventana en una variable local:

    float window_height = (float)renderer.getSize().y;

    // Se recorre toda la lista de bodies de physics_world:

    for (b2Body* body = physics_world.GetBodyList(); body != nullptr; body = body->GetNext())
    {
        // Se obtiene el transform del body:

        const b2Transform& body_transform = body->GetTransform();

        // Se recorre la lista de fixtures del body:

        for (b2Fixture* fixture = body->GetFixtureList(); fixture != nullptr; fixture = fixture->GetNext())
        {
            // Se obtiene el tipo de forma de la fixture:

            b2Shape::Type shape_type = fixture->GetShape()->GetType();

            switch (shape_type)
            {
            case b2Shape::e_circle:
            {
                // Se crea un CircleShape a partir de los atributos de la forma de la fixture y del body:
                // En SFML el centro de un c?rculo no est? en su position. Su position es la esquina superior izquierda
                // del cuadrado en el que est? inscrito. Por eso a position se le resta el radio tanto en X como en Y.

                b2CircleShape* circle = dynamic_cast<b2CircleShape*>(fixture->GetShape());

                render_circle(circle->m_p, circle->m_radius, body_transform, renderer, window_height, scale);

                break;
            }
            case b2Shape::e_edge:
            {
                // Se toman los dos v?rtices del segmento y se ajusta su posici?n usando el transform del body.
                // Los v?rtices resultantes se convierten y se ponen en un array para finalmente dibujar el segmento
                // que los une usando la sobrecarga del m?todo draw() que permite dibujar primitivas de OpenGL a
                // partir de datos de v?rtices.

                b2EdgeShape* edge = dynamic_cast<b2EdgeShape*>(fixture->GetShape());

                render_segment(edge->m_vertex1, edge->m_vertex2, body_transform, renderer, window_height, scale);

                break;
            }

            case b2Shape::e_polygon:
            {
                // Se toma la forma poligonal de Box2D (siempre es convexa) y se crea a partir de sus v?rtices un
                // ConvexShape de SFML. Cada v?rtice de Box2D hay que transformarlo usando el transform del body.

                b2PolygonShape* box2d_polygon = dynamic_cast<b2PolygonShape*>(fixture->GetShape());

                render_polygon(box2d_polygon->m_vertices, box2d_polygon->m_count, body_transform, renderer, window_height, scale);

                break;
            }
            }
        }
    }
}

