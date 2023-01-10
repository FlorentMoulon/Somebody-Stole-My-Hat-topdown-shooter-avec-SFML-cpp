#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "EcranBase.h"
#include "Bouton.h"

#include <SFML/Graphics.hpp>

/**
 * @brief (hérite de la classe EcranBase) Permet de gérer le game over
 * 
 */
class GameOver : public EcranBase {
    public:

    /**
     * @brief Constructeur par défaut de l'écran de game over
     * 
     */
    GameOver();

    /**
     * @brief Destructeur par défaut de l'écran de game over
     * 
     */
    ~GameOver();


    /**
     * @brief Boucle permettant de faire tourner l'écran de game over
     * 
     * @param window RenderWIndow : Fenêtre dans laquelle on affiche l'écran de game over
     * @param view View : vue permettant d'afficher tout l'écran
     * @return int : Chiffre correspondant à l'écran auquel on souhaite accéder : 1 pour retourner au menu
     */
    virtual int boucle(sf::RenderWindow & window, sf::View & view);

};



#endif