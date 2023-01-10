#include "Bouton.h"

#include <iostream>
#include <cassert>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


Bouton::Bouton(sf::Vector2f position, std::string texte) {
    assert(m_texture.loadFromFile("data/sprite/bouton_menu.png"));
	m_sprite.setTexture(m_texture);
    m_sprite.setOrigin(m_texture.getSize().x/2, 0);
    m_sprite.setPosition(position.x, position.y);

    m_texte.setCharacterSize(50);
    m_texte.setString(texte);

    m_texte.setFillColor(sf::Color(255, 255, 255, 255));
    m_texte.setOrigin(m_texture.getSize().x/2, 0);
    m_texte.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y+m_texture.getSize().y/3);

    assert(m_police.loadFromFile("data/font/Western.otf"));
    m_texte.setFont(m_police);
}

Bouton::~Bouton(){

}
    
bool Bouton::hover(sf::Vector2f posSouris) {
    if(m_sprite.getGlobalBounds().contains(posSouris))
    {
        m_sprite.setScale(1.1, 1.2);
        return true;
    }
    else {
        m_sprite.setScale(1.0, 1.0);
        return false;
    }

}
bool Bouton::clicSouris(sf::Vector2f posSouris) {
    if(m_sprite.getGlobalBounds().contains(posSouris))
    {
        return true;
    }
    else {
        return false;
    }
}

void Bouton::setPosition(sf::Vector2f position) {
    m_sprite.setPosition(position.x, position.y);
    m_texte.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y+m_texture.getSize().y/3);
}

sf::Vector2u Bouton::getTailleSprite() {
    return m_texture.getSize();
}

void Bouton::afficher(sf::RenderWindow & window) {
    window.draw(m_sprite);
    window.draw(m_texte);
}