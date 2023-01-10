#ifndef ProjectileSFML_H
#define ProjectileSFML_H


#include "Projectile.h"

#include <math.h>
#include <SFML/Graphics.hpp>

const int TAILLE_CASE = 100;
const double PI = 3.1415926535897;

/**
 * @brief (surcouche de la classe Projectile) Permet de gérer les projectiles avec SFML
 * 
 */
class ProjectileSFML{
    public :

    /**
     * @brief Constructeur par défaut de ProjectileSFML
     * 
     */
    ProjectileSFML();

    /**
     * @brief Constructeur permettant de créer un projectileSFML ayant les propriétés d'un projectile
     * 
     * @param projectile Projectile : projectile dont on copie les propriétés
     */
    ProjectileSFML(const Projectile & projectile);

    /**
     * @brief Destructeur par défaut de ProjectileSFML
     * 
     */
    ~ProjectileSFML();


    /**
     * @brief Remplace les propriétés du ProjectileSFML par celles du projectile
     * 
     * @param projectile Projectile : projectile dont on copie les propriétés
     */
    void setProjectile(const Projectile & projectile);


    /**
     * @brief Définit la position du projectile
     * 
     * @param x float : abscisse de la position
     * @param y float : ordonnée de la position
     */
    void setPosition(float x, float y);

    /**
     * @brief Définit la rotation du projectile
     * 
     * @param vectTir Vect2D : direction dans laquelle orienter le projectile
     */
    void setRotation(const Vect2D & vectTir);


    /**
     * @brief Fait avancer le projectileSFML avec sa direction et sa vitesse
     * 
     */
    void avancer();   

    /**
     * @brief Retourne la hitbox du projectile
     * 
     * @return HitboxRectangle : hitbox du projectile
     */
    HitboxRectangle getHitbox() const;

    /**
     * @brief Retourne le sprite du projectile
     * 
     * @return sf::Sprite : sprite du projectile
     */
    sf::Sprite getSprite() const;

    /**
     * @brief Retourne le texture du projectile
     * 
     * @return sf::Texture : texture du projectile
     */
    sf::Texture getTexture() const;



    Projectile m_projectile; 


    private :

    sf::Texture m_texture;
    sf::Sprite m_sprite;
};

#endif