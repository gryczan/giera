#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>


class bullet
{
    public:
        bullet(sf::Vector2f kordy, bool x);
        sf::Sprite sprite;
        sf::Texture texture;
        bool zwrot;
        void ruch();
        bool aktywny;
        sf::FloatRect poligon;

    protected:

    private:
};

#endif // BULLET_H
