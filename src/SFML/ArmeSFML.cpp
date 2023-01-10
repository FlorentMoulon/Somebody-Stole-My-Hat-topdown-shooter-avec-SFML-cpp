#include "ArmeSFML.h"
#include <iostream>
#include <cassert>
#include <SFML/Graphics.hpp>

ArmeSFML::ArmeSFML():
m_arme(100, 100, 50, 1, 400, 0.5, 0.5), m_nbProjectileSFML(0){

}

ArmeSFML::ArmeSFML(float delai, int nbMunition, int degat, float vitesse, int penetration,  float largeur, float hauteur):
m_arme(delai, nbMunition, degat, vitesse, penetration, largeur, hauteur), m_nbProjectileSFML(0){

}

ArmeSFML::ArmeSFML(const ArmeSFML & a):
m_arme(a.m_arme), m_nbProjectileSFML(0){

}

ArmeSFML::~ArmeSFML(){}





void ArmeSFML::setArme(float delai, int nbMunition, int degat, float vitesse, int penetration,  float largeur, float hauteur){
	m_arme.set(delai, nbMunition, degat, vitesse, penetration, largeur, hauteur);
}

void ArmeSFML::updateDelai(){
	m_arme.updateDelai();
}


void ArmeSFML::ajouterProjectile(const ProjectileSFML & nvProjectile){
	m_projectiles.push_back(nvProjectile);
	m_nbProjectileSFML ++;
}

void ArmeSFML::supprimerIemeProjectile(const int i){
	assert(i < m_nbProjectileSFML);
	
	m_projectiles.erase(m_projectiles.begin() + i);
	m_nbProjectileSFML --;
}

ProjectileSFML ArmeSFML::getIemeProjectile(const int i) const{
	assert(i < m_nbProjectileSFML);

	return m_projectiles[i];
}


bool ArmeSFML::tirer(const Vect2D & vectTir, ProjectileSFML & p, const Point2D & positionCentrePerso){
	if(m_arme.tirerSansBalle()){
		p.setProjectile(m_arme.getMunitionType());
		
		p.setPosition(
			positionCentrePerso.x - m_arme.getMunitionType().getLargeur()/2,
			positionCentrePerso.y - m_arme.getMunitionType().getHauteur()/2);
		p.setRotation(vectTir);

		p.m_projectile.setDirection(vectTir);

		ajouterProjectile(p);

		return true;
	}
	return false;
}



void ArmeSFML::tirerForceur(const Vect2D & vectTir, ProjectileSFML & p, const Point2D & positionCentrePerso){
	p.setProjectile(m_arme.getMunitionType());

	p.setPosition(
		positionCentrePerso.x + m_arme.getMunitionType().getLargeur()/2,
		positionCentrePerso.y + m_arme.getMunitionType().getHauteur()/2);
	p.setRotation(vectTir);


	p.m_projectile.setDirection(vectTir);

	ajouterProjectile(p);
}

bool ArmeSFML::tirerIProjectiles(const Vect2D & vectTir, ProjectileSFML & p, const Point2D & positionCentrePerso, int i, float angle){
	if(m_arme.tirerSansBalle()){
		p.setProjectile(m_arme.getMunitionType());

		p.setPosition(
			positionCentrePerso.x + m_arme.getMunitionType().getLargeur()/2,
			positionCentrePerso.y + m_arme.getMunitionType().getHauteur()/2);

		for(int j=0; j<i; j++){
			Vect2D v(vectTir);
			float mini=angle/2 - angle;
			v.rotation(mini + j*(angle/i));

			p.setRotation(v);

			p.m_projectile.setDirection(v);

			ajouterProjectile(p);
		}

		return true;
	}

	return false;
}

void ArmeSFML::recharger(){
	m_arme.recharger();
}
    

int ArmeSFML::getNbBalleRestante() const{
	return m_arme.getNbBalleRestante();
}

int ArmeSFML::getNbProjectileSFML() const{
	return m_projectiles.size();
}


void ArmeSFML::avancerIemeProjectile(const int i){
	m_projectiles[i].avancer();
}

Arme ArmeSFML::getArme() const{
	return m_arme;
}