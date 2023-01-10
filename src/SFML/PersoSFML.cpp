#include "PersoSFML.h"
#include <iostream>
#include <cassert>
#include <SFML/Graphics.hpp>

PersoSFML::PersoSFML(){
	assert(m_texture.loadFromFile("data/sprite/sombrero.png"));
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_texture.getSize().x/2, m_texture.getSize().y/2);
	m_sprite.setScale(0.13, 0.13);
	m_sprite.setPosition(m_perso.getCentre().x  *TAILLE_CASE, m_perso.getCentre().y *TAILLE_CASE);
}

PersoSFML::PersoSFML(const Perso & perso) : m_perso(perso) {
	assert(m_texture.loadFromFile("data/sprite/sombrero.png"));
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_texture.getSize().x/2, m_texture.getSize().y/2);
	m_sprite.setScale(0.13, 0.13);
	m_sprite.setPosition(m_perso.getCentre().x  *TAILLE_CASE, m_perso.getCentre().y *TAILLE_CASE);
}

PersoSFML::PersoSFML(int vie, int vieMax, float x, float y, float vitesse, float largeur, float hauteur) : 
m_perso(vie, vieMax, x, y, vitesse, largeur, hauteur) {
	assert(m_texture.loadFromFile("data/sprite/sombrero.png"));
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_texture.getSize().x/2, m_texture.getSize().y/2);
	m_sprite.setScale(0.13, 0.13);
	m_sprite.setPosition(m_perso.getCentre().x  *TAILLE_CASE, m_perso.getCentre().y *TAILLE_CASE);
}

PersoSFML::PersoSFML(int vie, int vieMax, float x, float y, float vitesse, float largeur, float hauteur, const ArmeSFML & arme) : 
m_perso(vie, vieMax, x, y, vitesse, largeur, hauteur), m_armeSFML(arme){
	assert(m_texture.loadFromFile("data/sprite/sombrero.png"));
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_texture.getSize().x/2, m_texture.getSize().y/2);
	m_sprite.setScale(0.13, 0.13);
	m_sprite.setPosition(m_perso.getCentre().x  *TAILLE_CASE, m_perso.getCentre().y *TAILLE_CASE);
}


PersoSFML::~PersoSFML(){}

void PersoSFML::setPosition(float x, float y) {
	m_perso.setPosition(x, y);
	m_sprite.setPosition(m_perso.getCentre().x * TAILLE_CASE, m_perso.getCentre().y * TAILLE_CASE);
}

void PersoSFML::setPosition(const Point2D & pt){
	m_perso.setPosition(pt.x, pt.y);
	m_sprite.setPosition(pt.x*TAILLE_CASE, pt.y*TAILLE_CASE);
}

void PersoSFML::setVivant(){
	m_perso.setVivant();
}

void PersoSFML::deplacement(const Vect2D & vecteur) {
	m_perso.deplacement(vecteur);
	m_sprite.move(vecteur.x*TAILLE_CASE, vecteur.y*TAILLE_CASE);
}



void PersoSFML::supprimerIemeProjectile(const int i){
	m_armeSFML.supprimerIemeProjectile(i);
}

ProjectileSFML PersoSFML::getIemeProjectile(const int i) const{
	return m_armeSFML.getIemeProjectile(i);
}


bool PersoSFML::tirer(const Vect2D & vectTir, ProjectileSFML & p){
	return m_armeSFML.tirer(vectTir, p, m_perso.getCentre());
}

void PersoSFML::tirerIProjectiles(const Vect2D & vectTir, ProjectileSFML & p, int i, float angle){
	m_armeSFML.tirerIProjectiles(vectTir, p, m_perso.getCentre(), i, angle);
}

void PersoSFML::recharger(){
	m_armeSFML.recharger();
}

void PersoSFML::avancerIemeProjectile(const int i){
	m_armeSFML.avancerIemeProjectile(i);
}

void PersoSFML::setArme(float delai, int nbMunition, int degat, float vitesse, int penetration, float largeur, float hauteur){
	m_armeSFML.setArme(delai, nbMunition, degat, vitesse, penetration, largeur, hauteur);
}

int PersoSFML::getNbProjectile()const{
	return m_armeSFML.getNbProjectileSFML();
}

int PersoSFML::getNbBalleRestante() const{
	return m_armeSFML.getNbBalleRestante();
}

void PersoSFML::updateDelai(){
	m_armeSFML.updateDelai();
}


sf::Sprite PersoSFML::getSprite() const{
	return m_sprite;
}

sf::Texture PersoSFML::getTexture() const{
	return m_texture;
}

void PersoSFML::setRotationSprite(double angle){
	m_sprite.setRotation(angle);
}

void PersoSFML::ajusterSrpite(){
	m_sprite.setPosition(
		m_perso.getCentre().x * TAILLE_CASE, 
        m_perso.getCentre().y * TAILLE_CASE);
}