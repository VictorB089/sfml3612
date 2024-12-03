
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
    vec4f operator+(const vec4f& other) {
        return vec4f{ x + other.x,y + other.y ,z + other.z ,w + other.w };
    }
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
sf::Vector3f mltplyVec3fVec3f(sf::Vector3f vec1, sf::Vector3f vec2) {
    sf::Vector3f result;
    result = {
    vec1.y * vec2.z - vec1.z * vec2.y,
    vec1.z * vec2.x - vec1.x * vec2.z,
    vec1.x * vec2.y - vec1.y * vec2.x
    };
    return result;
}
float scalarVec4Prod(vec4f vec1,vec4f vec2) {
    return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}
vec4f mltplyVecFloat(float a, vec4f vec) {
    return { vec.x * a,vec.y * a ,vec.z * a ,vec.w * a };
}

sf::Vector3f toCameraPos(vec4f CamCoordPos, float aspect,float Zfar,float Znear,int fov) {//UPD pipeline cameracoords->clipcoords->normalcoords
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
sf::Vector2f toScrnPospx(float x, float y,int W,int H) {//UPD pipeline normalcoords->screencoords
    return { ( ( (x - 1) / 2) * W),( ( (1 - y) / 2) * H) };
}

sf::VertexArray drawPoligons(std::vector<sf::Vector2f> VBO,std::vector<sf::Color> color) {
    sf::VertexArray poligons(sf::Triangles,VBO.size());
    for (int i = 0; i < VBO.size(); i++) {
        poligons[i].position = VBO[i];
        poligons[i].color = sf::Color::Green;
    }
    return poligons;
}

class camera {
private:
    unsigned short fov;
    mat4f ViewMat;
public:
    vec4f camPos =      { 0.f,1.f,0.f,1.f };
    vec4f rightVec =    { 1.f,0.f,0.f,1.f };
    vec4f topVec =      { 0.f,1.f,0.f,1.f };
    vec4f ForwardVec =  { 0.f,0.f,1.f,1.f };
    camera(int fov) : fov(fov) {
        ViewMat.mat = { 1.f, 0.f, 0.f, 0.f,    //rvecx  rvecy  rvecz  -camposvecx
                        0.f, 1.f, 0.f,-1.f,    //tvecx  tvecy  tvecz  -camposvecy
                        0.f, 0.f, 1.f, 0.f,    //fwvecx fwvecy fwvecz -camposvecz
                        0.f, 0.f, 0.f, 1.f     //0      0      0       1
        };
    };

    void move(float dx, float dy, float dz) {
        camPos = camPos + mltplyVecFloat(dx, rightVec) + mltplyVecFloat(dy, topVec) + mltplyVecFloat(dz, ForwardVec);
    }
    void rotate(float yaw,float pitch,float roll) 
    {
        mat4f R,Ryaw,Rpitch,Rroll;
        //yaw()
        Ryaw.mat = {
        cos(yaw),   0.f,  sin(yaw), 0.f,
        0.f,        1.f,  0.f,      0.f,
        -sin(yaw),  0.f,  cos(yaw), 0.f,
        0.f,        0.f,  0.f,      1.f
        };
        //pitch()
        Rpitch.mat = {
        1.f,0.f,        0.f,        0.f,
        0.f,cos(pitch),-sin(pitch),0.f,
        0.f,sin(pitch), cos(pitch),0.f,
        0.f,0.f,        0.f,       1.f
        };
        //roll()
        Rroll.mat = {
        cos(roll),-sin(roll),0.f,0.f,
        sin(roll),cos(roll), 0.f,0.f,
        0.f,      0.f,       1.f,0.f,
        0.f,      0.f,       0.f,1.f
        };
        R = mltplyMatMat(mltplyMatMat(Ryaw, Rpitch), Rroll);//temp mat4f R
        ForwardVec = mltplyMatVec(R, ForwardVec);//new Forward
        topVec = mltplyMatVec(R, topVec);
        sf::Vector3f tempvec3f = mltplyVec3fVec3f( { ForwardVec.x, ForwardVec.y, ForwardVec.z }, { topVec.x, topVec.y, topVec.z } );
        rightVec = { tempvec3f.x ,tempvec3f.y ,tempvec3f.z ,1.f};//new right
        tempvec3f = mltplyVec3fVec3f({ ForwardVec.x, ForwardVec.y, ForwardVec.z }, { rightVec.x, rightVec.y, rightVec.z });
        topVec = { tempvec3f.x ,tempvec3f.y ,tempvec3f.z ,1.f };//new top
        ViewMat.mat = {
            rightVec.x,  rightVec.y,  rightVec.z,  -scalarVec4Prod(camPos,rightVec),
            topVec.x,    topVec.y,    topVec.z,    -scalarVec4Prod(camPos,topVec),
            ForwardVec.x,ForwardVec.y,ForwardVec.z,-scalarVec4Prod(camPos,ForwardVec),
            0.f,         0.f,         0.f,          1.f
        };

    }
    vec4f toCamCoords(sf::Vector3f pos) {//UPD pipeline wrldcoords->cameracoords
        vec4f inCamCoords;
        inCamCoords = mltplyMatVec(ViewMat, vec4f(pos.x, pos.y, pos.z, 1.f) );
        return inCamCoords;
    }
};

class world {
private:
    sf::Color skyColor=sf::Color::Cyan;
    float groundLevel = 0.f;
public:
    world() {}
    std::vector<sf::Vector3f> worldFloor = {
        {10.f,2.f,10.f},
        {-10.f,2.f,10.f},
        {0.f,10.f,10.f},
        //{10.f,0.f,0.f},
        //{0.f,0.f,0.f},
        //{-10.f,0.f,-10.f}
    };
    std::vector<sf::Color> floorColor = {
        {100,100,100},
        {100,100,100},
        {100,100,100},
        {100,100,100}, 
        {100,100,100},
        {100,100,100},
    };
};

int main()
{
    

    bool Mleft = false, Mright = false, Mmid = false;
    unsigned short W = 1600, H = 900,fov=90;
    float aspect = W / H,Zfar=100000.f,Znear=0.f;
    int time = 0;
    world Floor1;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distW(0, W);//rand pos x
    std::uniform_int_distribution<> distH(0, H);//rand pos y

    sf::RenderWindow window(sf::VideoMode(W, H), "SFML");
    window.setFramerateLimit(120);
    window.setMouseCursorVisible(false);
    window.setMouseCursorGrabbed(true);
    
    camera Camera1(fov);
    std::vector<vec4f> tempv4fcoords;
    std::vector<sf::Vector3f> tempv3fcoords;
    std::vector<sf::Vector2f> tempv2fcoords;
    tempv4fcoords.resize(100);
    tempv3fcoords.resize(100);
    tempv2fcoords.resize(100);
    
    sf::VertexArray VAB;

    while (window.isOpen()) {
        if (time == 20) time = 0;
        Mleft = false;
        Mright = false;
        Mmid = false;

        sf::Event event;
        if (window.hasFocus())   sf::Mouse::setPosition(sf::Vector2i(W/2, H/2), window);
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) Mleft = true;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) Mright = true;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) Mmid = true;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) Camera1.move(10.f, 0.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) Camera1.move(0.f, 0.f, 10.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) Camera1.move(-10.f, 0.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) Camera1.move(0.f, 0.f, -10.f);


        
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        Camera1.rotate( (mousePos.x-W/2)*0.01f , (mousePos.y-H/2) * 0.01f, 0.f);
        

        //UPD pipeline wrldcoords->cameracoords->clipcoords->normalcoords->screencoords
        for (int i = 0; i < Floor1.worldFloor.size(); i++)
        {
            tempv4fcoords[i] = Camera1.toCamCoords(Floor1.worldFloor[i]);//wrldcoords->cameracoords
        };
        for (int i = 0; i < tempv4fcoords.size(); i++) {
            tempv3fcoords[i] = toCameraPos(tempv4fcoords[i], aspect, Zfar, Znear, fov);//cameracoords->clipcoords->normalcoords
        };
        for (int i = 0; i < tempv3fcoords.size(); i++) {
            tempv2fcoords[i] = toScrnPospx(tempv3fcoords[i].x, tempv3fcoords[i].y,W,H);//normalcoords->screencoords
        }
        VAB = drawPoligons(tempv2fcoords,Floor1.floorColor);//screencoords->poligons->VertexArrayBuffer VAB
        //

        //debug 1st poligon pos on screen
        if (time==19)
        {
        std::cout << " x  " << Camera1.camPos.x << " y  " << Camera1.camPos.y
            << " z  " << Camera1.camPos.z << std::endl;
        std::cout << "look at x " << Camera1.ForwardVec.x << " y " << Camera1.ForwardVec.y
            << " z " << Camera1.ForwardVec.z << std::endl;
        }
        window.clear();
        window.draw(VAB);
        window.display();
        time++;

    };
    return 0;
}