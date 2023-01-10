#ifndef BOUTON_H
#define BOUTON_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

/**
 * @brief Permet de créer des boutons avec un sprite et du texte
 * 
 */
class Bouton {
    public:

    /**
     * @brief Constructeur de la classe bouton
     * 
     * @param position Vector2f : position du point à créer
     * @param texte string : texte à afficher dans le bouton
     */
    Bouton(sf::Vector2f position, std::string texte);

    /**
     * @brief Destructeur de la classe bouton
     * 
     */
    ~Bouton();

    sf::Sprite m_sprite;
    sf::Text m_texte;
    
    /**
     * @brief Retourne un booléen qui indique si la souris est sur le bouton
     * 
     * @param posSouris Vector2f : position de la souris
     * @return true si la souris est sur le bouton
     * @return false si la souris n'est pas sur le bouton
     */
    bool hover(sf::Vector2f posSouris);

    /**
     * @brief Retourne un booléen qui indique si le bouton a été cliqué
     * 
     * @param posSouris Vector2f : position de la souris
     * @return true si le bouton est cliqué
     * @return false si le bouton n'est pas cliqué
     */
    bool clicSouris(sf::Vector2f posSouris);

    /**
     * @brief Redéfinit la position du bouton
     * 
     * @param position Vector2f : position à laquelle placer le bouton
     */
    void setPosition(sf::Vector2f position);

    /**
     * @brief Retourne la taille du sprite du bouton
     * 
     * @return sf::Vector2u : taille du sprite
     */
    sf::Vector2u getTailleSprite();

    /**
     * @brief Affiche le bouton dans la fenêtre
     * 
     * @param window RenderWindow : fenêtre dans laquelle afficher le bouton
     */
    void afficher(sf::RenderWindow & window);

    private:

    sf::Vector2f m_position;
    sf::Texture m_texture;
    sf::Font m_police;

};



#endif