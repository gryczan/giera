#include "laser.h"

laser::laser(sf::Vector2f kordy)
{
    texture_1.loadFromFile("splush.png");
    texture_2.loadFromFile("splush_dead.png");
    sprite.setTexture(texture_1);
    sprite.setPosition(kordy);
    int control = 0;
}

void laser::ruch()
{
    switch(control)
    {
    case 1:
        sprite.move(1,0);
        break;

    case 2:
        sprite.move(-1,0);
        break;
    }
}
