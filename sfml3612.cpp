
#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <cmath>
#include <random>
#include <thread>
#include <iostream>
#include <vector>
#include <memory>


int main()
{
    bool Mleft = false, Mright = false, Mmid = false;
    unsigned short W = 1600, H = 900;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distW(0, W);//rand pos x
    std::uniform_int_distribution<> distH(0, H);//rand pos y

    sf::Vector2f Mpos = { 0.f,0.f };

    sf::RenderWindow window(sf::VideoMode(W, H), "SFML");
    window.setFramerateLimit(120);


    while (window.isOpen()) {

        Mleft = false;
        Mright = false;
        Mmid = false;

        Mpos = (sf::Vector2f)sf::Mouse::getPosition(window);

        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) Mleft = true;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) Mright = true;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) Mmid = true;

        window.clear();

        window.display();


    };
    return 0;
}