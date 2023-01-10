#include "Arme.h"
#include <iostream>
#include "cassert"

Arme::Arme(): m_decompte(0), m_nbProjectile(0){

}

Arme::Arme(const Arme & a) : m_delai(a.m_delai), m_nbMunition(a.m_nbMunition), m_nbMunitionMax(a.m_nbMunitionMax),
m_munitionType(a.m_munitionType), m_decompte(a.m_decompte), m_nbProjectile(0){

}

Arme::Arme(float delai, int nbMunitionMax, Projectile munitionType) : m_delai(delai),
m_nbMunition(nbMunitionMax), m_nbMunitionMax(nbMunitionMax), m_munitionType(munitionType), m_decompte(0), m_nbProjectile(0){

}

Arme::Arme(float delai, int nbMunitionMax, int degat, float vitesse, int penetration, float largeur, float hauteur) : 
m_delai(delai), m_nbMunition(nbMunitionMax), m_nbMunitionMax(nbMunitionMax), m_decompte(0), m_nbProjectile(0){
    setMunitionType(degat, vitesse, penetration, largeur, hauteur);
}

Arme::~Arme(){

}



void Arme::set(const Arme & arme){
    m_delai = arme.m_delai;
    m_nbMunition = arme.m_nbMunition;
    m_nbMunitionMax = arme.m_nbMunitionMax;
    setMunitionType(arme.m_munitionType.getDegat(), arme.m_munitionType.getVitesse(), 100,
        arme.m_munitionType.getHitbox().getLargeur(), arme.m_munitionType.getHitbox().getHauteur());
}

void Arme::set(float delai, int nbMunitionMax, int degat, float vitesse, int penetration, float largeur, float hauteur){
    m_delai = delai;
    m_nbMunition = nbMunitionMax;
    m_nbMunitionMax = nbMunitionMax;
    setMunitionType(degat, vitesse, penetration, largeur, hauteur);
}



int Arme::getNombreProjectile() const{
    return m_nbProjectile;
}

int Arme::getNbBalleRestante() const{
    return m_nbMunition;
}

void Arme::ajouterProjectile(const Projectile & nvProjectile){
    m_projectiles.push_back(nvProjectile);
    m_nbProjectile ++;
}

void Arme::supprimerIemeProjectile(const int i){
    assert(i < m_nbProjectile);

    m_projectiles.erase(m_projectiles.begin() + i);
    m_nbProjectile --;
}

Projectile Arme::getIemeProjectile(const int i) const{
    assert(i < m_nbProjectile);

    return m_projectiles[i];
}


bool Arme::tirer(const Vect2D & vectTir, const Point2D & position){
    if(m_decompte == 0 && m_nbMunition >0){
        m_nbProjectile ++;
        Projectile p(m_munitionType);

        p.setPosition(
            position.x + m_munitionType.getHauteur()/2,
            position.y + m_munitionType.getLargeur()/2);
        

        p.setDirection(vectTir);

        ajouterProjectile(p);
        m_nbMunition --;

        m_decompte = m_delai;

        return true;
    }
    else if(m_nbMunition <= 0){
        m_decompte = m_delai*2.5;
        m_nbMunition = m_nbMunitionMax;
    }

    return false;
}

bool Arme::tirerSansBalle(){
    if(m_decompte == 0 && m_nbMunition >0){
        m_nbProjectile ++;
        Projectile p(m_munitionType);

        m_nbMunition --;

        m_decompte = m_delai;

        return true;
    }
    
    else if(m_nbMunition <= 0){
        recharger();
    }
    return false;
}



void Arme::avancerIemeProjectile(const int i){
    m_projectiles[i].avancer();
}

Projectile Arme::getMunitionType()const{
    return m_munitionType;
}

void Arme::setMunitionType(int degat, float vitesse, int penetration, float largeur, float hauteur){
    m_munitionType.setProjectile(degat, vitesse, penetration, largeur, hauteur);
}

void Arme::updateDelai(){
    if(m_decompte-1 <= 0){
        m_decompte = 0;
    }
    else{
        m_decompte --;
    }
}

void Arme::recharger(){
    m_decompte = m_delai*2.5;
    m_nbMunition = m_nbMunitionMax;
}

std::ostream& operator<<(std::ostream& o, const Arme & a){
    o<<"delai: "<<a.m_delai<<", nbMunition: "<<a.m_nbMunition;
    o<<", decompte: "<<a.m_decompte<<", nbProjectile: "<<a.m_nbProjectile;
    return o;
}