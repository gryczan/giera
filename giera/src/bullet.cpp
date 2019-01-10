#include "bullet.h"

bullet::bullet(sf::Vector2f kordy, bool x )
{
    aktywny = true;
    sprite.setPosition(kordy);
    texture.loadFromFile("bullet.png");
    sprite.setTexture(texture);
    zwrot = x;
    poligon = sprite.getGlobalBounds();
}

void bullet::ruch()
{
    switch(zwrot)
    {
        case 0:
            sprite.move(0, 10);
            break;

        case 1:
            sprite.move(0, -10);
            break;
    }
}
