#include "EnnemiSFML.h"
#include "ArmeSFML.h"
#include "ProjectileSFML.h"
#include <iostream>
#include <cassert>
#include <SFML/Graphics.hpp>

EnnemiSFML::EnnemiSFML(){
	assert(m_texture.loadFromFile("data/sprite/pirate.png"));
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_texture.getSize().x/2, m_texture.getSize().y/2);
	m_sprite.setScale(0.13, 0.13);
	m_sprite.setPosition(m_ennemi.getCentre().x  *TAILLE_CASE, m_ennemi.getCentre().y *TAILLE_CASE);
}

EnnemiSFML::EnnemiSFML(const Ennemi & ennemi) : m_ennemi(ennemi) {
	assert(m_texture.loadFromFile("data/sprite/pirate.png"));
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_texture.getSize().x/2, m_texture.getSize().y/2);
	m_sprite.setScale(0.13, 0.13);
	m_sprite.setPosition(m_ennemi.getCentre().x  *TAILLE_CASE, m_ennemi.getCentre().y *TAILLE_CASE);
}

EnnemiSFML::EnnemiSFML(int vie, int vieMax, float x, float y, float vitesse, float largeur, float hauteur) : 
m_ennemi(vie, vieMax, x, y, vitesse, largeur, hauteur) {
	assert(m_texture.loadFromFile("data/sprite/pirate.png"));
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_texture.getSize().x/2, m_texture.getSize().y/2);
	m_sprite.setScale(0.13, 0.13);
	m_sprite.setPosition(m_ennemi.getCentre().x  *TAILLE_CASE, m_ennemi.getCentre().y *TAILLE_CASE);
}

EnnemiSFML::~EnnemiSFML(){}


Point2D EnnemiSFML::getPosition() const{
	return m_ennemi.getCentre();
}

int EnnemiSFML::getIndiceDeplacement(){
	return m_ennemi.getIndiceDeplacement();
}

void EnnemiSFML::setPosition(float x, float y) {
	m_ennemi.setPosition(x, y);
	m_sprite.setPosition(m_ennemi.getCentre().x  *TAILLE_CASE, m_ennemi.getCentre().y *TAILLE_CASE);
}

void EnnemiSFML::setPosition(Point2D & pt) {
	m_ennemi.setPosition(pt.x, pt.y);
	m_sprite.setPosition(pt.x*TAILLE_CASE, pt.y*TAILLE_CASE);
}

void EnnemiSFML::setCheminJoueur(std::vector <Point2D> c){
	m_ennemi.setCheminJoueur(c);
}

void EnnemiSFML::setCheminPatrouille(std::vector <Point2D> c){
	m_ennemi.setCheminPatrouille(c);
}

void EnnemiSFML::setAggro(bool b){
	m_ennemi.setAggro(true);
}

Vect2D EnnemiSFML::cheminDeplacement(){
	return m_ennemi.cheminDeplacement();
}

Vect2D EnnemiSFML::patrouilleDeplacement(){
	return m_ennemi.patrouilleDeplacement();
}

void EnnemiSFML::deplacement(const Vect2D & vecteur) {
	m_ennemi.deplacement(vecteur);
	m_sprite.setPosition(m_ennemi.getCentre().x  *TAILLE_CASE, m_ennemi.getCentre().y *TAILLE_CASE);
}

bool EnnemiSFML::estAggro(){
	return m_ennemi.estAggro();
}



void EnnemiSFML::supprimerIemeProjectile(const int i){
	m_armeSFML.supprimerIemeProjectile(i);
}

ProjectileSFML EnnemiSFML::getIemeProjectile(const int i) const{
	return m_armeSFML.getIemeProjectile(i);
}


void EnnemiSFML::tirer(const Vect2D & vectTir, ProjectileSFML & p, Point2D & pt){
	m_armeSFML.tirer(vectTir, p, pt);
}

void EnnemiSFML::tirer(const Vect2D & vectTir, ProjectileSFML & p){
	m_armeSFML.tirer(vectTir, p, getPosition());
}


void EnnemiSFML::avancerIemeProjectile(const int i){
	m_armeSFML.avancerIemeProjectile(i);
}

void EnnemiSFML::setArme(float delai, int nbMunition, int degat, float vitesse, int penetration, float largeur, float hauteur){
	m_armeSFML.setArme(delai, nbMunition, degat, vitesse, penetration, largeur, hauteur);
}


int EnnemiSFML::getNbProjectile()const{
	return m_armeSFML.getNbProjectileSFML();
}

Vect2D EnnemiSFML::tirEnnemi(Point2D & coordCentrePerso, ProjectileSFML & p){
	int randomizer = rand() % 9;
    float angle = (randomizer - 5) * 3.1415926535 / 180;

    Vect2D tmp(
		coordCentrePerso.x - m_ennemi.getCentre().x ,
		coordCentrePerso.y - m_ennemi.getCentre().y );

	tmp.rotation(angle);

	m_armeSFML.tirer(tmp, p, getPosition());
    return tmp;	
}

void EnnemiSFML::updateDelai(){
	m_armeSFML.updateDelai();
}

void EnnemiSFML::afficherPosition(){
	std::cout << m_ennemi.getPosition()<<std::endl;
}

void EnnemiSFML::afficherChemin(){
	std::cout<<"-----------------------------------------------------"<<std::endl;
	m_ennemi.afficherChemin();
	std::cout<<"-----------------------------------------------------"<<std::endl;
}

sf::Sprite EnnemiSFML::getSprite() const{
	return m_sprite;
}

sf::Texture EnnemiSFML::getTexture() const{
	return m_texture;
}

void EnnemiSFML::setRotationSprite(double angle){
	m_sprite.setRotation(angle);
}