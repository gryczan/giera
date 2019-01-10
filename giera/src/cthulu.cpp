#include "cthulu.h"

cthulu::cthulu(sf::Vector2f kordy)
{
    texture.loadFromFile("ctjulu.png");
    texture_2.loadFromFile("cthulu_dead.png");
    sprite.setTexture(texture);
    sf::Vector2f xy(kordy);
    sprite.setPosition(xy);
    licznik = 0;
    poligon = sprite.getGlobalBounds();
}
void cthulu::akcja(int kontrol)
{
   switch(kontrol)
   {
   case 1:
    sprite.move(3,0);
    licznik++;
    break;

   case 2:
    sprite.move(-3,0);
    licznik++;
    break;
   }
}

void cthulu::kolizja()
{
    sprite.setTexture(texture_2);
    sprite.move(0, 50);
}


