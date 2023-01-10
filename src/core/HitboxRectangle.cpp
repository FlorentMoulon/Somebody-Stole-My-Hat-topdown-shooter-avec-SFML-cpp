#include "HitboxRectangle.h"
#include "cassert"

HitboxRectangle::HitboxRectangle(): m_largeur(0),m_hauteur(0), m_centre(0,0){

}

HitboxRectangle::HitboxRectangle(HitboxRectangle const & hitbox):
m_largeur(hitbox.m_largeur),m_hauteur(hitbox.m_hauteur), m_centre(hitbox.m_centre){

}

HitboxRectangle::HitboxRectangle(float largeur,float hauteur, Point2D centre) :
m_largeur(largeur),m_hauteur(hauteur), m_centre(centre){

}

HitboxRectangle::HitboxRectangle(float largeur,float hauteur, float x, float y) :
m_largeur(largeur), m_hauteur(hauteur), m_centre(x,y){

}

bool HitboxRectangle::pointEstDans(float x, float y) const{
    if(x >= (m_centre.x - m_largeur/2)
    && x <= (m_centre.x + m_largeur/2)
    && y >= (m_centre.y - m_largeur/2)
    && y <= (m_centre.y + m_largeur/2))
    return true;

    else return false;
}

bool HitboxRectangle::estEnContact(const HitboxRectangle & hitbox) const{
    if(pointEstDans(hitbox.m_centre.x - hitbox.m_largeur/2, hitbox.m_centre.y - hitbox.m_hauteur/2)
    || pointEstDans(hitbox.m_centre.x + hitbox.m_largeur/2, hitbox.m_centre.y + hitbox.m_hauteur/2)
    || pointEstDans(hitbox.m_centre.x - hitbox.m_largeur/2, hitbox.m_centre.y + hitbox.m_hauteur/2)
    || pointEstDans(hitbox.m_centre.x + hitbox.m_largeur/2, hitbox.m_centre.y - hitbox.m_hauteur/2))
    return true;

    else return false;
}

Point2D HitboxRectangle::getChg() const{
    Point2D chg(m_centre.x - m_largeur/2, m_centre.y - m_hauteur/2);   
    return chg;
}

Point2D HitboxRectangle::getChd() const{
    Point2D chd(m_centre.x + m_largeur/2, m_centre.y - m_hauteur/2);   
    return chd;
}

Point2D HitboxRectangle::getCbd() const{
    Point2D cbd(m_centre.x + m_largeur/2, m_centre.y + m_hauteur/2);   
    return cbd;
}

Point2D HitboxRectangle::getCbg() const{
    Point2D cbg(m_centre.x - m_largeur/2, m_centre.y + m_hauteur/2);   
    return cbg;
}

Point2D HitboxRectangle::getCentre() const{
    return m_centre;
}

void HitboxRectangle::setCentre(const float x, const float y){
    assert(x >= 0);
    assert(y >= 0);

    m_centre.x = x;
    m_centre.y = y;
}

void HitboxRectangle::setCentre(const Point2D & point2D){
    assert(point2D.x >= 0);
    assert(point2D.y >= 0);

    m_centre.x = point2D.x;
    m_centre.y = point2D.y;
}

void HitboxRectangle::setTaille(float largeur, float hauteur){
    assert(hauteur > 0);
    assert(largeur > 0);

    m_largeur = largeur;
    m_hauteur = hauteur;
}

float HitboxRectangle::getLargeur() const{
    return m_largeur;
}

float HitboxRectangle::getHauteur() const{
    return m_hauteur;
}

HitboxRectangle &HitboxRectangle::operator=(const HitboxRectangle & hitbox){
    m_largeur = hitbox.m_largeur;
    m_hauteur = hitbox.m_hauteur;
    m_centre = hitbox.m_centre;

    return *this;
}

std::ostream& operator<<(std::ostream& o, const HitboxRectangle & h){
    o<<"hauteur: "<<h.m_hauteur<<", largeur: "<<h.m_largeur;
    o<<", centre: ("<<h.m_centre.x<<","<<h.m_centre.y<<")";
    return o;
}
