#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>


class player
{
    public:
        player(int zmienna);
        sf::Texture texture;
        sf::Sprite sprite;
        int licznik;
        sf::FloatRect poligon;


    protected:

    private:
};

#endif // PLAYER_H
