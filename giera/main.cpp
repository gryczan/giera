#include <iostream>
#include <SFML/Graphics.hpp>
#include <player.h>
#include <vector>
#include <cthulu.h>
#include <bullet.h>
#include <SFML/Audio.hpp>
#include <laser.h>
int main ()
{
    int ile;
    std::vector <bullet> tab_bullet;
    cthulu tab_enemy1[4] =
    {
        cthulu(sf::Vector2f(100, 100)),
        cthulu(sf::Vector2f(250 ,100)),
        cthulu(sf::Vector2f(450, 100)),
        cthulu(sf::Vector2f(650, 100))
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
    sf::Texture texture_b1;                             //********TEXTURE 1 LVL
    sf::Texture texture_bl_2;
    texture_b1.loadFromFile("background.png");
    texture_bl_2.loadFromFile("desert.png");
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

                if(zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Num2)
                {
                    kontrol = 5;                            //lvl 2
                }
            }
            okno.clear( sf::Color( 0, 0, 0 ) );
            okno.draw(start);
        }
        else if(kontrol == 3)
        {
            int strzel = 0;
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
            for(int i = 0; i < 4; i++ )     //cthulu move
            {
                if(tab_enemy1[i].licznik < 300 && tab_enemy1[i].kolid == false)                 // move left
                {
                    tab_enemy1[i].akcja(1);
                }
                if(tab_enemy1[i].licznik > 299 &&  tab_enemy1[i].kolid == false)                  //move right
                {
                    tab_enemy1[i].akcja(2);
                }
                if(tab_enemy1[i].licznik < 300 && tab_enemy1[i].kolid == true)                 // move dead
                {
                    tab_enemy1[i].akcja(tab_enemy1[i].kolid_2);
                }
                if(tab_enemy1[i].licznik > 601)    //reset timer
                {
                    tab_enemy1[i].licznik = 0;
                }
                                                    // colision
                for(int x = 0; x < tab_bullet.size(); x++)
                {
                    if(tab_enemy1[i].sprite.getGlobalBounds().intersects(tab_bullet[x].sprite.getGlobalBounds()) == true)
                    {
                        tab_enemy1[i].kolizja();
                        strzel++;
                    }
                }
                if(tab_enemy1[i].licznik%75 == 1)                  //cthulu shoot
                {
                    sf::Vector2f kordyn;
                    kordyn = tab_enemy1[i].sprite.getPosition();
                    kordyn.x = kordyn.x + 50;
                    kordyn.y = kordyn.y + 151;
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
                //****************************drawing
            okno.clear(sf::Color(155,0,0));
            okno.draw(tlo);
            for(int i = 0; i < 4; i++)
            {
                okno.draw(tab_enemy1[i].sprite);
            }
            for(int i = 0; i < tab_bullet.size(); i++)
            {
                okno.draw(tab_bullet[i].sprite);
            }
            okno.draw(gracz.sprite);
           if(strzel >= 4)
          {
               kontrol = 5;
           }

        }
        //************************************************************************************LEVEL 2
        if(kontrol == 5)
        {
            sf::Event zdarzenie;
            tlo.setTexture(texture_bl_2);               //change background


            laser tab_laser[1]                          //enemy list
            {
                laser(sf::Vector2f(100,100))
            };

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
            //laser enemy behavior
            sf::Vector2f xy_gracz;
            sf::Vector2f xy_laser;
            for(int i = 0; i < 1; i++)
            {
                xy_gracz = gracz.sprite.getPosition();
                xy_laser = tab_laser[i].sprite.getPosition();
                if(xy_gracz.x > xy_laser.x)
                {
                    tab_laser[i].control = 1;
                }

                if(xy_gracz.x < xy_laser.x)
                {
                    tab_laser[i].control = 2;
                }

                tab_laser[i].ruch();
            }

            //bullet behavior
            for(int i = 0; i < tab_bullet.size(); i++)
            {
                tab_bullet[i].ruch();
            }
            //********************drawing
            okno.clear(sf::Color(155,0,0));
            okno.draw(tlo);

            for(int i = 0; i < 1; i++)
            {
                okno.draw(tab_laser[i].sprite);
            }
            okno.draw(gracz.sprite);
            for(int i = 0; i < tab_bullet.size(); i++)
            {
                okno.draw(tab_bullet[i].sprite);
            }

        }
        okno.display();
    }

}

