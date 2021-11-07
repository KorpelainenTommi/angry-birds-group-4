#include <iostream>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <Resources.hpp>

//Test code to see that libraries have been linked correctly

int main()
{

    Resources::Sprites sprite = Resources::metal_block1x1;

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    b2World world(b2Vec2(0, -9.81F));
    world.Step(0.1F, 10, 10);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}