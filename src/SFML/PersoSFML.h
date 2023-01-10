#ifndef PersoSFML_H
#define PersoSFML_H

#include "Perso.h"
#include "ArmeSFML.h"
#include "ProjectileSFML.h"

#include <SFML/Graphics.hpp>

/**
 * @brief (surcouche de la classe personnage) Permet de gérer le personnage avec SFML
 * 
 */
class PersoSFML{
    public :

    /**
     * @brief Constructeur par défaut de PersoSFML
     * 
     */
    PersoSFML();

    /**
     * @brief Constructeur permettant de créer un PersoSFML ayant les propriétés d'un Perso
     * 
     * @param perso Perso :perso dont on copie les propriétés
     */
    PersoSFML(const Perso & perso);

    /**
     * @brief Constructeur permetttant de créer un PersoSFML en paramétrant ses données membres.
     * 
     * @param vie int : vie du perso
     * @param vieMax int : vie maximale du perso
     * @param x float : position en abscisse
     * @param y float : position en ordonnée
     * @param vitesse float : vitesse du perso
     * @param largeur float : largeur de la hitbox du perso
     * @param hauteur float : hauteur de la hitbox du perso
     */
    PersoSFML(int vie, int vieMax, float x, float y, float vitesse, float largeur, float hauteur);

    /**
     * @brief Constructeur permetttant de créer un PersoSFML en paramétrant ses données membres.
     * 
     * @param vie int : vie du perso
     * @param vieMax int : vie maximale du perso
     * @param x float : position en abscisse
     * @param y float : position en ordonnée
     * @param vitesse float : vitesse du perso
     * @param largeur float : largeur de la hitbox du perso
     * @param hauteur float : hauteur de la hitbox du perso
     * @param arme ArmeSFML : arme dont on équipe le personnage
     */
    PersoSFML(int vie, int vieMax, float x, float y, float vitesse, float largeur, float hauteur, const ArmeSFML & arme);

    /**
     * @brief Destructeur par défaut de PersoSFML
     * 
     */
    ~PersoSFML();


    /**
     * @brief Modifie les propriétés de l'arme du perso
     * 
     * @param delai float : délai entre chaque tir
     * @param nbMunition int : nombre de munitions de l'arme
     * @param degat int : dégâts infligés par l'arme
     * @param vitesse float : vitesse du projetcile de l'arme
     * @param penetration int pénétration du projectile
     * @param largeur float : largeur du projectile
     * @param hauteur float : hauteur du projectile
     */
    void setArme(float delai, int nbMunition, int degat, float vitesse, int penetration, float largeur, float hauteur);
    void setVivant();


    /**
     * @brief Définit la position du personnage
     * 
     * @param x float : abscisse de la position
     * @param y float : ordonnée de la position
     */
    void setPosition(float x, float y);
    
    void setPosition(const Point2D & pt);


    /**
     * @brief Déplace le perso dans la direction du vecteur
     * 
     * @param vecteur Vect2D : direction dans lequel on se déplace
     */
    void deplacement(const Vect2D & vecteur);


    /**
     * @brief Tire un projectile dans la direction d'un vecteur donné
     * 
     * @param vectTir Vect2D : vecteur de tir
     * @param p ProjectileSFML : projectile que l'on tire
     */
    bool tirer(const Vect2D & vectTir, ProjectileSFML & p);

    /**
     * @brief Tire i projectiles dans un angle et une direction choisie
     * 
     * @param vectTir Vect2D : vecteur de tir
     * @param p ProjectileSFML : projectile que l'on tire
     * @param i int : indice du projectile que l'on tire
     * @param angle float : angle dans lequel on tire (imite un fusil à pompe)
     */
    void tirerIProjectiles(const Vect2D & vectTir, ProjectileSFML & p, int i, float angle);

    /**
     * @brief Recharge les munitions de l'arme
     * 
     */
    void recharger();

    /**
     * @brief Supprime le i-ème projectile du tableau de projectiles du perso
     * 
     * @param i int : indice du projectile à supprimer
     */
	void supprimerIemeProjectile(const int i);

    /**
     * @brief Renvoie le i-ème projectile du perso
     * 
     * @param i int : indice du projectile que l'on renvoie
     * @return ProjectileSFML : i-ème projectile du perso
     */
	ProjectileSFML getIemeProjectile(const int i) const;

    /**
     * @brief Fait avancer le i-ème projectile du perso
     * 
     * @param i int : indice du projectile que l'on fait avancer
     */
    void avancerIemeProjectile(const int i);

    /**
     * @brief Renvoie le nombre de projectiles du perso
     * 
     * @return int : nombre de projectiles du perso
     */
    int getNbProjectile()const;

    /**
     * @brief Retourne le nombre de Balle Restante dans le chargeur de l'arme
     * 
     * @return int : nombre de Balle Restante
     */
    int getNbBalleRestante() const;


    /**
     * @brief Update le délai entre chaque tir
     * 
     */
    void updateDelai();

    /**
     * @brief Retourne le sprite du perso
     * 
     * @return sf::Sprite : sprite du perso
     */
    sf::Sprite getSprite() const;

    /**
     * @brief Retourne le texture du perso
     * 
     * @return sf::Texture : texture du perso
     */
    sf::Texture getTexture() const;

    /**
     * @brief Tourne le srpite dans une direction donnée
     * 
     * @param angle double : nouvel angle
     */
    void setRotationSprite(double angle);

    /**
     * @brief Ajuster le srpite à la position du joueur
     * 
     */
    void ajusterSrpite();

    Perso m_perso;
    ArmeSFML m_armeSFML;


    private :

    sf::Texture m_texture;
    sf::Sprite m_sprite;

};

#endif