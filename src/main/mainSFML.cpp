#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "Point2D.h"
#include "Case.h"
#include "Vect2D.h"

#include "Perso.h"

#include <SFML/Graphics.hpp>

#include "EcranBase.h"
#include "JeuSFML.h"
#include "Menu.h"
#include "Pause.h"
#include "GameOver.h"

//sert simplement à créer la fenêtre mais n'est pas utilisé car on passe la fenêtre en fullscreen
const unsigned int LARGEUR_FENETRE = 1920;
const unsigned int LONGUEUR_FENETRE = 1080;

int main()
{   
    //création de la fenêtre
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(LARGEUR_FENETRE, LONGUEUR_FENETRE, desktop.bitsPerPixel), "Somebody Stole my Hat", sf::Style::Fullscreen);
    window.setFramerateLimit(30);
    
    //création de la view
    sf::Vector2u sizeTmp = window.getSize();
    sf::Vector2f size;
    size.x = sizeTmp.x; size.y = sizeTmp.y;
    sf::View view(sf::Vector2f(1000, 1000), size);


    //tableau servant à stocker nos écrans
    std::vector<EcranBase*> Ecrans;
    int idEcran = 0;

    //création de nos écrans et ajout dans le tableau d'écrans
    Menu * menu = new Menu;
    Ecrans.push_back((EcranBase *)(menu));

    JeuSFML * jeuSFML = new JeuSFML;
    jeuSFML->init();
    Ecrans.push_back((EcranBase *)(jeuSFML));

    Pause * pause = new Pause;
    Ecrans.push_back((EcranBase *)(pause));

    GameOver * gameOver = new GameOver;
    Ecrans.push_back((EcranBase *)(gameOver));
    
    //boucle permettant de naviquer entre les différents écrans en fonction de l'idEcran
    while (idEcran >= 0) {
        idEcran = Ecrans[idEcran]->boucle(window, view);
    }

    //destruction de nos écrans
    delete menu;
    delete jeuSFML;
    delete pause;
    delete gameOver;
    

    return 0;
}