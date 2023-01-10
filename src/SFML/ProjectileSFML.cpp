#include "ProjectileSFML.h"
#include "Vect2D.h"
#include <iostream>
#include <cassert>
#include <SFML/Graphics.hpp>

ProjectileSFML::ProjectileSFML(){
    assert(m_texture.loadFromFile("data/sprite/balle.png"));
    m_sprite.setTexture(m_texture);
    m_sprite.setOrigin(m_texture.getSize().x/2, m_texture.getSize().y/2);
    m_sprite.setPosition(m_projectile.getCentre().x  *TAILLE_CASE, m_projectile.getCentre().y *TAILLE_CASE);
}

ProjectileSFML::ProjectileSFML(const Projectile & projectile) : m_projectile(projectile) {
    assert(m_texture.loadFromFile("data/sprite/balle.png"));
    m_sprite.setTexture(m_texture);
    m_sprite.setOrigin(m_texture.getSize().x/2, m_texture.getSize().y/2);
    m_sprite.setPosition(m_projectile.getCentre().x  *TAILLE_CASE, m_projectile.getCentre().y *TAILLE_CASE);
}

ProjectileSFML::~ProjectileSFML(){}

void ProjectileSFML::setPosition(float x, float y) {
    m_projectile.setPosition(x, y);
    m_sprite.setPosition(m_projectile.getCentre().x  *TAILLE_CASE, m_projectile.getCentre().y *TAILLE_CASE);
}

void ProjectileSFML::setRotation(const Vect2D & vectTir) {
	m_sprite.setRotation(atan2(vectTir.y, vectTir.x) * 180 / PI +90);
}

void ProjectileSFML::avancer() {
    m_projectile.avancer();
    m_sprite.move(m_projectile.getDirection().x*m_projectile.getVitesse()*TAILLE_CASE, 
                  m_projectile.getDirection().y*m_projectile.getVitesse()*TAILLE_CASE);
}

void ProjectileSFML::setProjectile(const Projectile & projectile){
    m_projectile.setProjectile(projectile);
}

HitboxRectangle ProjectileSFML::getHitbox() const{
    return m_projectile.getHitbox();
}

sf::Sprite ProjectileSFML::getSprite() const{
	return m_sprite;
}

sf::Texture ProjectileSFML::getTexture() const{
	return m_texture;
}