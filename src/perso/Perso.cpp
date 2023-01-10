#include "Perso.h"
#include <iostream>
#include "cassert"


Perso::Perso() : 
m_vie(100), m_vieMax(100), m_position(12 ,12), m_vitesse(0.1), 
m_hitbox(1, 1, 12, 12), m_estMort(false)
{

}

Perso::Perso(int vie, int vieMax, float x, float y, float vitesse, 
float largeur, float hauteur) : 
m_vie(vie), m_vieMax(vieMax), m_position(x, y), m_vitesse(vitesse),
m_hitbox(largeur,hauteur, x+largeur/2, y+hauteur/2), m_estMort(false)
{

}

Perso::Perso(const Perso & perso) : 
m_vie(perso.m_vie), m_vieMax(perso.m_vieMax), m_position(perso.m_position), m_vitesse(perso.m_vitesse),
m_hitbox(perso.m_hitbox), m_estMort(perso.m_estMort){

}

Perso::~Perso(){}


void Perso::setPosition(float x, float y) {
    m_position.x = x;
    m_position.y = y;
    m_hitbox.setCentre(getCentre().x, getCentre().y);
}

void Perso::setVivant(){
    m_estMort = false;
    m_vie = m_vieMax;
}

void Perso::deplacement(Vect2D vecteurDeplacement){
    m_position.x += vecteurDeplacement.x*m_vitesse;
    m_position.y += vecteurDeplacement.y*m_vitesse;
    m_hitbox.setCentre(getCentre());
}

HitboxRectangle Perso::detecterCollision(Vect2D direction){
    HitboxRectangle hitboxVirtuelle(m_hitbox);

    hitboxVirtuelle.setCentre(
        hitboxVirtuelle.getCentre().x + m_vitesse*direction.x,
        hitboxVirtuelle.getCentre().y + m_vitesse*direction.y);

    return hitboxVirtuelle;
}

HitboxRectangle Perso::getHitbox() const{
    return m_hitbox;
}

Point2D Perso::getPosition() const{
    return m_position;
}



void Perso::affichePosition() const{
    std::cout<<"x : "<<m_position.x<<"  y : "<<m_position.y<<std::endl;
}

Vect2D Perso::convertitPosition() const{
    Vect2D tmp;
    tmp.x=m_position.x;
    tmp.y=m_position.y;
    return tmp;
}

void Perso::setVitesse(float vitesse){
    if (vitesse > 0){m_vitesse = vitesse;}  
}

float Perso::getVitesse() const {
    return m_vitesse;
}





bool Perso::estToucheParBalle(const Projectile & balle){
    return m_hitbox.estEnContact(balle.getHitbox());
}

void Perso::prendreDegat(const int degat){
    assert(degat>=0);

    if(m_vie - degat <= 0){
        m_vie = 0;
        mourir();
    }
    else{
        m_vie -= degat;
    }
}

void Perso::mourir(){
    m_estMort = true;
}

bool Perso::getMort() {
    return m_estMort;
}

void Perso::setArme(const Arme & arme){
    m_arme.set(arme);
}

void Perso::setArme(float delai, int nbMunitionMax, int degat, float vitesse, int penetration, float largeur, float hauteur){
    m_arme.set(delai, nbMunitionMax, degat, vitesse, penetration, largeur, hauteur);
}

void Perso::tirer(const Vect2D & vectTir){
    m_arme.tirer(vectTir, m_position);
}

Projectile Perso::getMunitionType() const{
    return m_arme.getMunitionType();
}

int Perso::getNombreProjectile() const{
    return m_arme.getNombreProjectile();
}

void Perso::supprimerIemeProjectile(const int i){
    m_arme.supprimerIemeProjectile(i);
}

Projectile Perso::getIemeProjectile(const int i) const{
    return m_arme.getIemeProjectile(i);
}

int Perso::getNbBalleRestante() const{
    return m_arme.getNbBalleRestante();
}

void Perso::updateDelai(){
    m_arme.updateDelai();
}

void Perso::avancerIemeProjectile(const int i){
    m_arme.avancerIemeProjectile(i);
}

Point2D Perso::getCentre() const{
    Point2D pt(
        m_position.x + m_hitbox.getLargeur()/2,
        m_position.y + m_hitbox.getHauteur()/2);
    return pt;
}


std::ostream& operator<<(std::ostream& o, const Perso & p){
    o<<"Perso : vie :"<<p.m_vie<<", vieMax :"<<p.m_vieMax;
    o<<", vitesse :"<<p.m_vitesse<<", estMort ?"<<p.m_estMort<<std::endl;

    o<<"position :"<<p.m_position<<std::endl;
    o<<"hitbox :"<<p.m_hitbox<<std::endl;
    o<<"arme :"<<p.m_arme;

    return o;
}

bool Perso::estEnContact(const HitboxRectangle & hitbox) const{
    return m_hitbox.estEnContact(hitbox);
}

Vect2D Perso::collisionPerso(const HitboxRectangle & hitbox, HitboxRectangle hitboxVirtuelle, const Vect2D & direction) const{
    if(! direction.estNul()){
        while (m_hitbox.estEnContact(hitboxVirtuelle)){
            hitboxVirtuelle.setCentre(
                hitboxVirtuelle.getCentre().x - direction.x*0.05,
                hitboxVirtuelle.getCentre().y - direction.y*0.05
            );
        }
    }   
    
    Vect2D deplacement(
        hitboxVirtuelle.getCentre().x - hitbox.getCentre().x,
        hitboxVirtuelle.getCentre().y - hitbox.getCentre().y
    );

    return deplacement;
}