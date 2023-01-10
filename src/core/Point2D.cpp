#include"Point2D.h"
#include"Vect2D.h"
#include <math.h>


Point2D::Point2D(float X, float Y) : x(X), y(Y){

}

Point2D::Point2D(const Point2D & pt) : x(pt.x), y(pt.y){

}

void Point2D::set(float X, float Y){
    x=X;
    y=Y;
}

Point2D Point2D::inverser() const{
    Point2D tmp;
    tmp.x = y;
    tmp.y = x;
    return tmp;
}

Point2D Point2D::arrondir() const{
    Point2D tmp;
    tmp.x = floor(x);
    tmp.y = floor(y);
    return tmp;
}

void Point2D::rapprocheCoord(Point2D & pt){
    if (!(pt.x=x && pt.y==y)){
        Point2D tmp(x, y);
        tmp = pt - tmp;
        if (sqrt(tmp.x * tmp.x) < sqrt(tmp.y*tmp.y)){
            if (tmp.y < 0) y++;
            else y--;
        } 
        else {
            if (tmp.x < 0) x--;
            else x++;
        }
    }
}

Point2D Point2D::convertir(const Vect2D &v ) const{
    Point2D tmp;
    tmp.x=v.x;
    tmp.y=v.y;
    return tmp;
}

Vect2D Point2D::convertirPtToVect() const{
    Vect2D tmp;
    tmp.x=x;
    tmp.y=y;
    return tmp;
}

float Point2D::distance(const Point2D & pt){
    Point2D tmp; 
    tmp.x = pt.x - x;
    tmp.y = pt.y - y;
    float norme = sqrt(tmp.x*tmp.x + tmp.y * tmp.y);
    return norme;
}

float Point2D::distanceManhattan(const Point2D & pt){
    Point2D tmp; 
    tmp.x = pt.x - x;
    tmp.y = pt.y - y;
    float norme = sqrt(tmp.x*tmp.x) + sqrt(tmp.y * tmp.y);
    return norme;
}

Point2D Point2D::operator+(const Point2D& pt){
    Point2D point(0.0, 0.0);
    point.x=x+pt.x;
    point.y=y+pt.y;
    return point;
    
}

Point2D Point2D::operator-(const Point2D& pt){
    Point2D point(0.0, 0.0);
    point.x=x-pt.x;
    point.y=y-pt.y;
    return point;
    
}

Point2D &Point2D::operator=(const Point2D &pt) { 
    x=pt.x;
    y=pt.y;
    return *this;
}

bool Point2D::operator==(const Point2D & pt) const{
    if (x==pt.x && y==pt.y) return true;
    return false;
}

std::ostream& operator<<(std::ostream& o, const Point2D & pt){
    
    o<<"Point2D : COORDONEES X : "<<pt.x << "  COORDONEES Y : "<<pt.y;
    return o;
}