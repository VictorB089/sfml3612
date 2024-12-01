
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

class mat4f {
private:
    std::vector<float> mat = 
    {
        0.f,0.f,0.f,0.f,
        0.f,0.f,0.f,0.f,
        0.f,0.f,0.f,0.f,
        0.f,0.f,0.f,0.f
    };
public:
    mat4f(std::vector<float> aR, std::vector<float> bR, std::vector<float> cR, std::vector<float> dR) 
    {
        mat =
        {
            aR[0],aR[1],aR[2],aR[3],    //0, 1, 2, 3,   n
            bR[0],bR[1],bR[2],bR[3],    //4, 5, 6, 7,   |
            cR[0],cR[1],cR[2],cR[3],    //8, 9, 10,11,  V
            dR[0],dR[1],dR[2],dR[3]     //12,13,14,15   m-->
        };
    }
    float get(int n, int m) {
        return mat.at(4*(n-1)+(m-1));
    }
};

class camera {
private:
    unsigned short fov;
    sf::Vector3f position;
    sf::Vector3f normalVec;
public:
    camera(): position({ 0.f,1.f,0.f }), normalVec({0.f,0.f,1.f}),fov(85) {};

    void move(float x, float y, float z) {
        position += sf::Vector3f{x,y,z};
    }
    void rotate(float x, float y) {
        normalVec += {x,y,0.f};
    }
};

class world {
private:
    sf::Color floorColor=sf::Color(100,100,100);
    sf::Color skyColor=sf::Color::Cyan;
    float groundLevel = 0.f;
public:
    world() {}
    void draw(sf::RenderWindow window) {
    //window.draw()
    }
};

int main()
{
    

    bool Mleft = false, Mright = false, Mmid = false;
    unsigned short W = 1600, H = 900;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distW(0, W);//rand pos x
    std::uniform_int_distribution<> distH(0, H);//rand pos y

    std::vector<float> Mmove = { 0.f,0.f };

    sf::RenderWindow window(sf::VideoMode(W, H), "SFML");
    window.setFramerateLimit(120);
    window.setMouseCursorVisible(false);
    window.setMouseCursorGrabbed(true);
    
    camera Camera1();


    while (window.isOpen()) {

        Mleft = false;
        Mright = false;
        Mmid = false;

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

        if (event.type == sf::Event::MouseMoved) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            Camera1().rotate()
        }

        window.clear();

        window.display();


    };
    return 0;
}