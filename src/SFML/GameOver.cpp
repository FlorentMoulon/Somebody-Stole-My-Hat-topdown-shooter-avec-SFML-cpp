#include "GameOver.h"

#include <iostream>
#include <cassert>
#include <chrono> //librairies utilisées pour arrêter le temps
#include <thread>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

GameOver::GameOver() {

}

GameOver::~GameOver() {

}

int GameOver::boucle(sf::RenderWindow & window, sf::View & view) {
    sf::Event event;

    //création des boutons
    Bouton boutonTitre(sf::Vector2f(window.getSize().x/2, window.getSize().y/7), "Game Over !");
    boutonTitre.m_sprite.setScale(1.5, 1.5);
    boutonTitre.m_texte.setCharacterSize(60);
    boutonTitre.m_texte.move(50, 0);
    Bouton boutonQuitter(sf::Vector2f(window.getSize().x/2, 4*window.getSize().y/7), "Retourner au menu");
    boutonQuitter.m_sprite.setScale(1.0, 1.0);
    boutonQuitter.m_texte.move(8, -15);

    //musique de fond
    sf::Music backgroundMusic;
    assert(backgroundMusic.openFromFile("data/music/MusiqueMort.wav"));
    backgroundMusic.setVolume(20);
    backgroundMusic.play();

    //sons de clic et de survol des boutons
    sf::SoundBuffer buffer_hover;
    buffer_hover.loadFromFile("data/music/MENU/MENU_SURVOLE.ogg");
    sf::Sound son_hover;
    bool estDansBoutonQuitter; //permet de tester si l'on doit rejouer le son de hover ou non

    sf::SoundBuffer buffer_clic;
    buffer_clic.loadFromFile("data/music/MENU/MENU_CLIC.ogg");
    sf::Sound son_clic;

    while(true) 
    {   
        view.setCenter(sf::Vector2f(window.getSize().x/2, window.getSize().y/2));
        while (window.pollEvent(event)) 
        {
			if (event.type == sf::Event::Closed) {
                backgroundMusic.stop();
				return (-1);
			}
			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
                case sf::Keyboard::Escape:
                    backgroundMusic.stop();
                    return 0;
				default:
					break;
				}
			}
            if(event.type == sf::Event::MouseMoved) {
                sf::Vector2f posSouris(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

                if(boutonQuitter.hover(posSouris)) {
                    if(!estDansBoutonQuitter) {
                    son_hover.setBuffer(buffer_hover);
                    son_hover.play();
                    }
                    estDansBoutonQuitter = true;
                } else estDansBoutonQuitter = false;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f posSouris(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
                    if(boutonQuitter.clicSouris(posSouris)) {
                        son_clic.setBuffer(buffer_clic);
                        son_clic.play();
                        backgroundMusic.stop();
                        std::this_thread::sleep_for(std::chrono::milliseconds(500));
                        return 0;
                    }
                }
    		}
        }

        //affichage
        window.clear();
        window.setView(view);
        boutonTitre.afficher(window);
        boutonQuitter.afficher(window);
        window.display();

    }
}