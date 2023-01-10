#ifndef EnnemiSFML_H
#define EnnemiSFML_H

#include "Ennemi.h"
#include "PersoSFML.h"
#include "ArmeSFML.h"
#include "ProjectileSFML.h"
#include <vector>

#include <SFML/Graphics.hpp>

/**
 * @brief (surcouche de la classe Ennemi) Permet de gérer les ennemis avec SFML
 * 
 */
class EnnemiSFML {
    public :

    /**
     * @brief Constructeur par défaut de EnnemiSFML
     * 
     */
    EnnemiSFML();

    /**
     * @brief Constructeur permettant de créer un EnnemiSFML ayant les propriétés d'un Ennemi
     * 
     * @param ennemi Ennemi : ennemi dont on copie les propriétés
     */
    EnnemiSFML(const Ennemi & ennemi);

    /**
     * @brief Constructeur permetttant de créer un EnnemiSFML en paramétrant ses données membres.
     * 
     * @param vie int : vie de l'ennemi
     * @param vieMax int : vie maximale de l'ennemi
     * @param x float : position en abscisse
     * @param y float : position en ordonnée
     * @param vitesse float : vitesse de l'ennemi
     * @param largeur float : largeur de la hitbox de l'ennemi
     * @param hauteur float : hauteur de la hitbox de l'ennemi
     */
    EnnemiSFML(int vie, int vieMax, float x, float y, float vitesse, float largeur, float hauteur);

    /**
     * @brief Destructeur par défaut de EnnemiSFML
     * 
     */
    ~EnnemiSFML();


    /**
     * @brief   Retourne la poition de l'ennemi
     * 
     * @return Point2D : poition de l'ennemi
     */
    Point2D getPosition() const;


    /**
     * @brief Permet de déplacer l'ennemi avec un vecteur donné
     * 
     * @param vecteur Vect2D : vecteur donnant la direction dans laquelle l'ennemi se déplace
     */
    void deplacement(const Vect2D & vecteur);

    /**
     * @brief Change la position de l'ennemi
     * 
     * @param x float : position en abscisse
     * @param y float : position en ordonnée
     */
    void setPosition(float x, float y) ;

    void setPosition(Point2D & pt);
    

    /**
     * @brief Change le chemin pour arriver au joueur
     * 
     * @param c vector<Point2D> : tableau de points permettant de définir un chemin jusqu'au joueur
     */
    void setCheminJoueur(std::vector <Point2D> c);
    void setCheminPatrouille(std::vector <Point2D> c);

    void setAggro(bool b);
    
    /**
     * @brief Donne la direction dans laquelle l'ennemi doit avancer pour suivre le chemin jusqu'au personnage
     * 
     * @return Vect2D : vecteur de la direction de déplacement
     */
    Vect2D cheminDeplacement();

    /**
     * @brief Donne la direction dans laquelle l'ennemi doit avancer pour suivre le chemin jusqu'au personnage
     * 
     * @return Vect2D : vecteur de la direction de déplacement
     */
    Vect2D patrouilleDeplacement();
    

    /**
     * @brief Affiche dans le terminal la position de l'ennemi
     * 
     */
    void afficherPosition();

    /**
     * @brief Affiche le chemin que suit l'ennemi
     * 
     */
    void afficherChemin();

    bool estAggro();

    



    int m_nbProjectileSFML;
    std::vector <ProjectileSFML> m_projectiles;


    /**
     * @brief Retourne le sprite de l'ennemi
     * 
     * @return sf::Sprite : sprite de l'ennemi
     */
    sf::Sprite getSprite() const;

    /**
     * @brief Retourne le texture de l'ennemi
     * 
     * @return sf::Texture : texture de l'ennemi
     */
    sf::Texture getTexture() const;


    /**
     * @brief Modifie les propriétés de l'arme de l'ennemi
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

    /**
     * @brief Tire un projectile selon un vecteur à partir d'une position
     * 
     * @param vectTir Vect2D : vecteur de tir
     * @param p ProjectileSFML : projectile que l'on tire
     * @param pt Point2D : position à partir de laquelle on tire
     */
    void tirer(const Vect2D & vectTir, ProjectileSFML & p, Point2D & pt);

    /**
     * @brief Tire un projectile selon un vecteur
     * 
     * @param vectTir Vect2D : vecteur de tir
     * @param p : ProjectileSFML : projectile que l'on tire
     */
    void tirer(const Vect2D & vectTir, ProjectileSFML & p);

    /**
     * @brief Renvoie la direction dans laquelle l'ennemi doit viser le personnage
     * 
     * @param coordCentrePerso Point2D : coordonnées du centre du personnage
     * @param p ProjectileSFML : projectile que l'on tire
     * @return Vect2D : vecteur de la direction dans laquelle l'ennemi doit tirer
     */
    Vect2D tirEnnemi(Point2D & coordCentrePerso, ProjectileSFML & p);

    /**
     * @brief Supprime le i-ème projectile du tableau de projectiles de l'ennemi
     * 
     * @param i int : indice du projectile à supprimer
     */
	void supprimerIemeProjectile(const int i);

    /**
     * @brief Renvoie le i-ème projectile de l'ennemi
     * 
     * @param i int : indice du projectile que l'on renvoie
     * @return ProjectileSFML : i-ème projectile de l'ennemi
     */
	ProjectileSFML getIemeProjectile(const int i) const;

    /**
     * @brief Fait avancer le i-ème projectile de l'ennemi
     * 
     * @param i int : indice du projectile que l'on fait avancer
     */
    void avancerIemeProjectile(const int i);

    /**
     * @brief Renvoie le nombre de projectiles de l'ennemi
     * 
     * @return int : nombre de projectiles de l'ennemi
     */
    int getNbProjectile()const;

    /**
     * @brief Retourne l'indice du point actuel sur le chemin de l'ennemi
     * 
     * @return int : indice du point actuel sur le chemin de l'ennemi
     */
    int getIndiceDeplacement();


    /**
     * @brief Update le délai entre chaque tir
     * 
     */
    void updateDelai();

    /**
     * @brief Tourne le srpite dans une direction donnée
     * 
     * @param angle double : nouvel angle
     */
    void setRotationSprite(double angle);


    Ennemi m_ennemi;
    ArmeSFML m_armeSFML;



    private:

    sf::Texture m_texture;
    sf::Sprite m_sprite;

};

#endif