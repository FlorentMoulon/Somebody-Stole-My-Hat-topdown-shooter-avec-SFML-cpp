#include "Porte.h"
#include "iostream"

Porte::Porte() : x(0), y(0), orientation('h')
{

}

Porte::Porte(int X, int Y, char Orientation) : 
x(X), y(Y), orientation(Orientation)
{

}


std::ostream& operator<<(std::ostream& o, const Porte & p){
    o<<"Porte : x:"<<p.x<<", y:"<<p.y<<", orientation:"<<p.orientation<<std::endl;
    return o;
}