#include "Projectile.h"
#include "iostream"
#include <cassert>

Projectile::Projectile(){

}

Projectile::Projectile(const Projectile & p) : 
m_degat(p.m_degat), m_vitesse(p.m_vitesse), m_penetration(p.m_penetration),
 m_largeur(p.m_largeur), m_hauteur(p.m_hauteur),
m_direction(p.m_direction), m_position(p.m_position), m_hitbox(p.m_hitbox){
    m_direction.normaliser();
}

Projectile::Projectile(int degat, float vitesse, int penetration, Vect2D direction,
Point2D position, float largeur, float hauteur) : 
m_degat(degat), m_vitesse(vitesse), m_penetration(penetration), m_largeur(largeur),
m_hauteur(hauteur), m_direction(direction), m_position(position),
m_hitbox(largeur, hauteur,getCentre().x, getCentre().y){
    m_direction.normaliser();
}

Projectile::~Projectile(){

}




void Projectile::setDirection(const Vect2D & direction){
    m_direction.x = direction.x;
    m_direction.y = direction.y;
    m_direction.normaliser();
}

void Projectile::setPosition(float x, float y){
    m_position.x = x;
    m_position.y = y;
    m_hitbox.setCentre(getCentre());
}

void Projectile::setProjectile(int degat, float vitesse, int penetration, float largeur, float hauteur){
    assert(hauteur > 0);
    assert(largeur > 0);

    m_degat = degat;
    m_vitesse = vitesse;
    m_penetration = penetration;
    m_largeur = largeur;
    m_hauteur = hauteur;
    m_hitbox.setCentre(getCentre());
    m_hitbox.setTaille(largeur, hauteur);
}


void Projectile::setProjectile(const Projectile & projectile){
    m_degat = projectile.m_degat;
    m_vitesse = projectile.m_vitesse;
    m_penetration = projectile.m_penetration;
    m_largeur = projectile.m_largeur;
    m_hauteur = projectile.m_hauteur;
    m_hitbox.setCentre(getCentre());
    m_hitbox.setTaille(m_largeur, m_hauteur);
}



void Projectile::avancer(){
    m_position.x += m_direction.x*m_vitesse;
    m_position.y += m_direction.y*m_vitesse;
    m_hitbox.setCentre(getCentre());
}

HitboxRectangle Projectile::detecterCollision(){
    HitboxRectangle hitboxVirtuelle(m_hitbox);

    hitboxVirtuelle.setCentre(
        hitboxVirtuelle.getCentre().x + m_vitesse * m_direction.x,
        hitboxVirtuelle.getCentre().y + m_vitesse * m_direction.y);

    return hitboxVirtuelle;
}



void Projectile::afficher(){
    std::cout<<"x :"<<m_position.x<<",  y :"<<m_position.y<<",  vitesse :"<<m_vitesse;
    std::cout<<", largeur :"<<m_largeur<<", hauteur :"<<m_hauteur<<std::endl;
}



Point2D Projectile::getCentre() const{
    Point2D pt(
        m_position.x + m_largeur/2,
        m_position.y + m_hauteur/2);
    return pt;
}

Point2D Projectile::getPosition() const{
    return m_position;
}

HitboxRectangle Projectile::getHitbox() const{
    return m_hitbox;
}

float Projectile::getHauteur()const{
    return m_hauteur;
}

float Projectile::getLargeur()const{
    return m_largeur;
}

float Projectile::getVitesse()const{
    return m_vitesse;
}

Vect2D Projectile::getDirection()const{
    return m_direction;
}

int Projectile::getDegat()const{
    return m_degat;
}

std::ostream& operator<<(std::ostream& o, const Projectile & p){
    o<<"Projectile : x :"<<p.m_position.x<<",  y :"<<p.m_position.y<<",  vitesse :"<<p.m_vitesse;
    o<<", largeur :"<<p.m_largeur<<", hauteur :"<<p.m_hauteur<<std::endl;
    return o;
}