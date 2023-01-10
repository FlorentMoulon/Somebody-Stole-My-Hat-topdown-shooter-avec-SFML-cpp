#ifndef PAUSE_H
#define PAUSE_H

#include "EcranBase.h"
#include "Bouton.h"

#include <SFML/Graphics.hpp>

/**
 * @brief (hérite de la classe EcranBase) Permet de gérer le fait de mettre en pause le jeu
 * 
 */
class Pause : public EcranBase {
    public:

    /**
     * @brief Constructeur par défaut de l'écran de pause
     * 
     */
    Pause();

    /**
     * @brief Destructeur par défaut de l'écran de pause
     * 
     */
    ~Pause();


    /**
     * @brief Boucle permettant de faire tourner l'écran de pause
     * 
     * @param window RenderWIndow : Fenêtre dans laquelle on affiche l'écran de pause
     * @param view View : vue permettant d'afficher tout l'écran
     * @return int : Chiffre correspondant à l'écran auquel on souhaite accéder : 1 pour retourner au menu, 1 pour retourner au jeu
     */
    virtual int boucle(sf::RenderWindow & window, sf::View & view);

};



#endif