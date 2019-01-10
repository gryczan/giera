#include "player.h"

player::player(int zmienna)
{
    texture.loadFromFile("player.png");
    sprite.setTexture(texture);
    sprite.setPosition(500, 500);
    licznik = zmienna;
    poligon = sprite.getGlobalBounds();
}
