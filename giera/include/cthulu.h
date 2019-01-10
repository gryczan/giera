#ifndef CTHULU_H
#define CTHULU_H
#include <SFML/Graphics.hpp>


class cthulu
{
    public:
        cthulu(sf::Vector2f kordy);             //konstruktor
        sf::Sprite sprite;                      //sprite
        sf::Texture texture;                    //texture
        sf::Texture texture_2;                  //texture dead
        void akcja(int kontrol);                //behavior function
        sf::Vector2f kor;                       //cooridnates
        int licznik;                            //licznik
        sf::FloatRect poligon;
        void kolizja();

    protected:

    private:
};

#endif // CTHULU_H
