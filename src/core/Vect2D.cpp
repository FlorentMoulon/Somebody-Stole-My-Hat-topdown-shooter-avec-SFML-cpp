#include "Vect2D.h"
#include "math.h"
#include <iostream>

Vect2D::Vect2D(float X, float Y) : x(X), y(Y){

}

Vect2D::Vect2D(const Vect2D &v) : x(v.x), y(v.y){}

void Vect2D::set(float X, float Y){
    x=X;
    y=Y;
}

void Vect2D::normaliser(){
    if (x != 0 || y!=0){
        float norme = sqrt(x*x+y*y);
        x = x/norme;
        y = y/norme;
    }  
}

float Vect2D::scalaire(const Vect2D & v){
    return v.x * x + v.y * y;
}

float Vect2D::norme(){
    return sqrt(x*x + y*y);
}

float Vect2D::angle (Vect2D & v){
    float angle; 
    angle = scalaire(v) / (norme() * v.norme());
    angle = acos(angle);
    if (angle > 180) angle = 360 - angle;
    return angle; 
}

void Vect2D::rotation (float angle){
    float oldX = x;
    float oldY = y;
    x = oldX*cos(angle) - oldY * sin (angle);
    y = oldX*sin(angle) + oldY* cos (angle);
}

void Vect2D::afficher(){
    std::cout<<std::endl<<"VECTEUR, X : "<<x<<" Y : "<<y<<std::endl;
}

bool Vect2D::estNul()const{
    return (y == 0  &&  x == 0);
}


Vect2D Vect2D::operator-(const Vect2D& v){
    Vect2D Ve(0.0, 0.0);
    Ve.x=x-v.x;
    Ve.y=y-v.y;
    return Ve;
}

Vect2D &Vect2D::operator=(const Vect2D &v) { 
        x=v.x;
        y=v.y;
        return *this;
}


std::ostream& operator<<(std::ostream& o, const Vect2D & v){
    o<<"Point2D : COORDONEES X : "<<v.x << "  COORDONEES Y : "<<v.y;
    return o;
}

