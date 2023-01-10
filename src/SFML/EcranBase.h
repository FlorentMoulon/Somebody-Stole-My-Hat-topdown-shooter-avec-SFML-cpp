#ifndef EcranBase_H_INCLUDED
#define EcranBase_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

/**
 * @brief Classe mère des différents écrans du jeu 
 * 
 */
class EcranBase{
    public:
    /**
     * @brief Destructeur par défaut de la classe EcranBase
     * 
     */
    virtual ~EcranBase() = default;

    /**
     * @brief Boucle permettant de faire tourner l'écran
     * 
     * @param window RenderWIndow : Fenêtre dans laquelle on affiche l'écran
     * @param view View : vue permettant d'afficher tout l'écran
     * @return int : Chiffre correspondant à l'écran auquel on souhaite accéder
     */
    virtual int boucle (sf::RenderWindow &window, sf::View & view) = 0;
};
#endif