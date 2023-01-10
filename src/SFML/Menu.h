#ifndef Menu_H
#define Menu_H

#include "EcranBase.h"
#include "Bouton.h"

#include <SFML/Graphics.hpp>

/**
 * @brief (hérite de la classe EcranBase) Permet de gérer le menu de jeu
 * 
 */
class Menu : public EcranBase {
    public:

    /**
     * @brief Constructeur par défaut du menu
     * 
     */
    Menu();

    /**
     * @brief Destructeur du menu
     * 
     */
    ~Menu();


    /**
     * @brief Boucle permettant de faire tourner le menu
     * 
     * @param window RenderWIndow : Fenêtre dans laquelle on affiche le menu
     * @param view View : vue permettant d'afficher tout l'écran
     * @return int : Chiffre correspondant à l'écran auquel on souhaite accéder : 1 pour le jeu, -1 pour quitter
     */
    virtual int boucle(sf::RenderWindow & window, sf::View & view);

};



#endif