
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


class vec4f {
public:
    float x, y, z, w;
    vec4f() {
        x = 0.f;
        y = 0.f;
        z = 0.f;
        w = 0.f;
    }
    vec4f(float x, float y, float z,float w) : x(x), y(y), z(z), w(w) {};
};
class mat4f {
public:
    std::vector<float> mat = 
    {
        0.f,0.f,0.f,0.f,    //0, 1, 2, 3,   n
        0.f,0.f,0.f,0.f,    //4, 5, 6, 7,   |
        0.f,0.f,0.f,0.f,    //8, 9, 10,11,  V
        0.f,0.f,0.f,0.f     //12,13,14,15   m-->
    };
    mat4f() {};
    float get(int n, int m) {
        return mat.at(4*(n-1)+(m-1));
    }
};

vec4f mltplyMatVec(mat4f mat, vec4f vec) {
    vec4f result;
    result.x = mat.mat[0]  * vec.x + mat.mat[1]  * vec.y + mat.mat[2]  * vec.z + mat.mat[3]  * vec.w;
    result.y = mat.mat[4]  * vec.x + mat.mat[5]  * vec.y + mat.mat[6]  * vec.z + mat.mat[7]  * vec.w;
    result.z = mat.mat[8]  * vec.x + mat.mat[9]  * vec.y + mat.mat[10] * vec.z + mat.mat[11] * vec.w;
    result.w = mat.mat[12] * vec.x + mat.mat[13] * vec.y + mat.mat[14] * vec.z + mat.mat[15] * vec.w;
    return result;
}
mat4f mltplyMatMat(mat4f mat1, mat4f mat2) {
    mat4f result;
    result.mat[0 ] = mat1.mat[0 ] * mat2.mat[0 ] + mat1.mat[1 ] * mat2.mat[4 ] + mat1.mat[2 ] * mat2.mat[8 ] + mat1.mat[3 ] * mat2.mat[12];//
    result.mat[1 ] = mat1.mat[0 ] * mat2.mat[1 ] + mat1.mat[1 ] * mat2.mat[5 ] + mat1.mat[2 ] * mat2.mat[9 ] + mat1.mat[3 ] * mat2.mat[13];//
    result.mat[2 ] = mat1.mat[0 ] * mat2.mat[2 ] + mat1.mat[1 ] * mat2.mat[6 ] + mat1.mat[2 ] * mat2.mat[10] + mat1.mat[3 ] * mat2.mat[14];//
    result.mat[3 ] = mat1.mat[0 ] * mat2.mat[3 ] + mat1.mat[1 ] * mat2.mat[7 ] + mat1.mat[2 ] * mat2.mat[11] + mat1.mat[3 ] * mat2.mat[15];//

    result.mat[4 ] = mat1.mat[4 ] * mat2.mat[0 ] + mat1.mat[5 ] * mat2.mat[4 ] + mat1.mat[6 ] * mat2.mat[8 ] + mat1.mat[7 ] * mat2.mat[12];//
    result.mat[5 ] = mat1.mat[4 ] * mat2.mat[1 ] + mat1.mat[5 ] * mat2.mat[5 ] + mat1.mat[6 ] * mat2.mat[9 ] + mat1.mat[7 ] * mat2.mat[13];//
    result.mat[6 ] = mat1.mat[4 ] * mat2.mat[2 ] + mat1.mat[5 ] * mat2.mat[6 ] + mat1.mat[6 ] * mat2.mat[10] + mat1.mat[7 ] * mat2.mat[14];//
    result.mat[7 ] = mat1.mat[4 ] * mat2.mat[3 ] + mat1.mat[5 ] * mat2.mat[7 ] + mat1.mat[6 ] * mat2.mat[11] + mat1.mat[7 ] * mat2.mat[15];//

    result.mat[8 ] = mat1.mat[8 ] * mat2.mat[0 ] + mat1.mat[9 ] * mat2.mat[4 ] + mat1.mat[10] * mat2.mat[8 ] + mat1.mat[11] * mat2.mat[12];//
    result.mat[9 ] = mat1.mat[8 ] * mat2.mat[1 ] + mat1.mat[9 ] * mat2.mat[5 ] + mat1.mat[10] * mat2.mat[9 ] + mat1.mat[11] * mat2.mat[13];//
    result.mat[10] = mat1.mat[8 ] * mat2.mat[2 ] + mat1.mat[9 ] * mat2.mat[6 ] + mat1.mat[10] * mat2.mat[10] + mat1.mat[11] * mat2.mat[14];//
    result.mat[11] = mat1.mat[8 ] * mat2.mat[3 ] + mat1.mat[9 ] * mat2.mat[7 ] + mat1.mat[10] * mat2.mat[11] + mat1.mat[11] * mat2.mat[15];//

    result.mat[12] = mat1.mat[12] * mat2.mat[0 ] + mat1.mat[13] * mat2.mat[4 ] + mat1.mat[14] * mat2.mat[8 ] + mat1.mat[15] * mat2.mat[12];//
    result.mat[13] = mat1.mat[12] * mat2.mat[1 ] + mat1.mat[13] * mat2.mat[5 ] + mat1.mat[14] * mat2.mat[9 ] + mat1.mat[15] * mat2.mat[13];//
    result.mat[14] = mat1.mat[12] * mat2.mat[2 ] + mat1.mat[13] * mat2.mat[6 ] + mat1.mat[14] * mat2.mat[10] + mat1.mat[15] * mat2.mat[14];//
    result.mat[15] = mat1.mat[12] * mat2.mat[3 ] + mat1.mat[13] * mat2.mat[7 ] + mat1.mat[14] * mat2.mat[11] + mat1.mat[15] * mat2.mat[15];//

    return result;
}
mat4f Tmat(mat4f mat) {
    mat4f result;
    result.mat[0 ] = mat.mat[0]; result.mat[1 ] = mat.mat[4]; result.mat[2 ] = mat.mat[8 ]; result.mat[3 ] = mat.mat[12];     //0, 1, 2, 3,   n
    result.mat[4 ] = mat.mat[1]; result.mat[5 ] = mat.mat[5]; result.mat[6 ] = mat.mat[9 ]; result.mat[7 ] = mat.mat[13];     //4, 5, 6, 7,   |
    result.mat[8 ] = mat.mat[2]; result.mat[9 ] = mat.mat[6]; result.mat[10] = mat.mat[10]; result.mat[11] = mat.mat[14];     //8, 9, 10,11,  V
    result.mat[12] = mat.mat[3]; result.mat[13] = mat.mat[7]; result.mat[14] = mat.mat[11]; result.mat[15] = mat.mat[15];     //12,13,14,15   m-->
    return result;
}

sf::Vector3f toCameraPos(vec4f CamCoordPos, float aspect,float Zfar,float Znear,int fov) {
    vec4f inCamPos;
    mat4f Pmat;
    Pmat.mat = {
        float(1 / (tan(fov / 2) * aspect)), 0.f , 0.f , 0.f,
        0.f,     float(1 / (tan(fov / 2)))    , 0.f , 0.f,
        0.f,0.f,((Zfar + Znear) / (Znear - Zfar)), ((2 * Zfar * Znear) / (Znear - Zfar)),
        0.f,0.f,                              -1.f , 0.f
    };
    inCamPos = mltplyMatVec(Pmat, CamCoordPos);
    return { (inCamPos.x / inCamPos.w), (inCamPos.y / inCamPos.w), (inCamPos.z / inCamPos.w) };
}
sf::Vector2f inScrnPospx(float x, float y,int W,int H) {
    return { ( ( (x - 1) / 2) * W),( ( (1 - y) / 2) * H) };
}

class camera {
private:
    unsigned short fov;
    mat4f ViewMat;
public:
    camera(int fov) : fov(fov) {
        ViewMat.mat = { 1.f, 0.f, 0.f, 0.f,    //rvecx rvecy rvecz -camposvecx
                        0.f, 1.f, 0.f,-1.f,    //uvecx uvecy uvecz -camposvecy
                        0.f, 0.f, 1.f, 0.f,    //vvecx vvecy vvecz -camposvecz
                        0.f, 0.f, 0.f, 1.f     //0     0     0      1
        };
    };

    void moveTo(float x, float y, float z) {
        ViewMat.mat[3]  = -x;
        ViewMat.mat[7]  = -y;
        ViewMat.mat[11] = -z;
    }
    vec4f onScrnPos(sf::Vector3f pos) {
        vec4f toScrnPos;
        toScrnPos = mltplyMatVec(ViewMat, vec4f(pos.x, pos.y, pos.z, 1.f) );
        return toScrnPos;
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
    unsigned short W = 1600, H = 900,fov=90;
    float aspect = W / H,Zfar=1000.f,Znear=1.f;

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
        }

        window.clear();

        window.display();


    };
    return 0;
}