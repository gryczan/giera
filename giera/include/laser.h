#ifndef LASER_H
#define LASER_H
#include <SFML/Graphics.hpp>


class laser
{
    public:
        sf::Sprite sprite;
        sf::Texture texture_1;
        sf::Texture texture_2;
        laser(sf::Vector2f kordy);
        void ruch();
        int control;

    protected:

    private:
};

#endif // LASER_H
