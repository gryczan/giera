#include <iostream>
#include <SFML/Graphics.hpp>
#include <player.h>
#include <vector>
#include <cthulu.h>
#include <bullet.h>
#include <SFML/Audio.hpp>
int main ()
{
    int ile;
    std::vector <bullet> tab_bullet;
    cthulu tab_enemy1[1] =
    {
        cthulu(sf::Vector2f(100, 100))
    };

    int kontrol = 1;
    sf::Font font;
    font.loadFromFile("emulogic.ttf");
    sf::Text start;
    start.setFont(font);
    start.setString("To start a game press space");
    start.setCharacterSize(24);
    start.setFillColor(sf::Color::White);
    start.setPosition(320,400);
    player gracz(5);
    sf::Sprite tlo;
    sf::Texture texture_b1;
    texture_b1.loadFromFile("background.png");
    tlo.setTexture(texture_b1);
    int licznik;
    // audio
    sf::SoundBuffer buffer_beep;
    buffer_beep.loadFromFile("beep_1.wav");
    sf::Sound sound_beep;
    sound_beep.setBuffer(buffer_beep);
    sf::SoundBuffer buffer_boop;
    buffer_boop.loadFromFile("beep-metallic.wav");
    sf::Sound sound_boop;
    sound_boop.setBuffer(buffer_boop);


    sf::RenderWindow okno( sf::VideoMode( 1366, 768, 32 ), "Giera" );
    okno.setFramerateLimit(60);
    while( okno.isOpen() )
    {
        if(kontrol == 1)                        //rozpoczecie wyswietlania ekranu tytulowego
        {
            sf::Event zdarzenie;
            while( okno.pollEvent( zdarzenie ) )
            {
                if( zdarzenie.type == sf::Event::Closed )
                    okno.close();

                if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Escape )
                    okno.close();

                if(zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Space)
                {
                    kontrol = 3;                            //zmiana ekranu tytulowego na gre
                }


            }
            okno.clear( sf::Color( 0, 0, 0 ) );
            okno.draw(start);
        }
        else if(kontrol == 3)
        {
            sf::Event zdarzenie;
            while( okno.pollEvent( zdarzenie ) )
            {
                if( zdarzenie.type == sf::Event::Closed )
                    okno.close();

                if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Escape )
                    okno.close();

                 //********************* player move
                if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Left)
                {
                    gracz.sprite.move(-10,0);
                }
                if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Right)
                {
                  gracz.sprite.move(10,0);
                }
                if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Up)
                {
                    gracz.sprite.move(0,-10);
                }

                if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Down)
                {
                    gracz.sprite.move(0,10);
                }
                // player shoot
                if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Z)
                {
                    sf::Vector2f kordyn;
                    kordyn = gracz.sprite.getPosition();
                    kordyn.x = kordyn.x + 50;
                    kordyn.y = kordyn.y + 101;
                    bullet basic_bullet(kordyn , true);
                    tab_bullet.push_back(basic_bullet);
                    sound_beep.play();
                }
            }
            // cthulu behavior
            for(int i = 0; i < 1; i ++ )     //cthulu move
            {
                if(tab_enemy1[i].licznik < 300)                 // move left
                {
                    tab_enemy1[i].akcja(1);
                }
                if(tab_enemy1[i].licznik > 299)  //move right
                {
                    tab_enemy1[i].akcja(2);
                }
                if(tab_enemy1[i].licznik > 601)    //reset timer
                {
                    tab_enemy1[i].licznik = 0;
                }

                for(int x; x < tab_bullet.size(); x++)
                {
                    if(tab_enemy1[i].poligon.intersects(tab_bullet[i].poligon))
                    {
                        tab_enemy1[i].kolizja();
                    }
                }


                if(tab_enemy1[i].licznik%75 == 1)                  //cthulu shoot
                {
                    sf::Vector2f kordyn;
                    kordyn = tab_enemy1[i].sprite.getPosition();
                    kordyn.x = kordyn.x + 50;
                    kordyn.y = kordyn.y + 101;
                    bullet basic_bullet(kordyn , false);
                    tab_bullet.push_back(basic_bullet);
                    sound_boop.play();
                }
            }
            //BULLET BEHEVIOR
            for(int i = 0; i < tab_bullet.size(); i++)
            {
                tab_bullet[i].ruch();
            }

            okno.clear(sf::Color(155,0,0));
            okno.draw(tlo);
            for(int i = 0; i < 1; i++)
            {
                okno.draw(tab_enemy1[i].sprite);
            }
            for(int i = 0; i < tab_bullet.size(); i++)
            {
                okno.draw(tab_bullet[i].sprite);
            }
            okno.draw(gracz.sprite);

        }
        okno.display();
    }

}

