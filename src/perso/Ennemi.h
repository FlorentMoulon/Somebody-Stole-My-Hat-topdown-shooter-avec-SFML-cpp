#ifndef Ennemi_H
#define Ennemi_H


#include "Perso.h"
#include "Point2D.h"
#include "Vect2D.h"
#include <vector>


/**
 * @brief Hérite de Perso. Modélise les personages non joueurs avec leur vie, arme, boite de collision. Peu se déplacer vers le joueur, patrouiller, tirer, detecter des collision. 
 * 
 */
class Ennemi : public Perso{

    public : 

    /**
     * @brief Constructeur par défaut de Ennemi
     * 
     */
    Ennemi();

    /**
     * @brief Créer un ennemi et initialise sa vie, sa position, sa vitesse et sa taille
     * 
	 * @param vie int : vie de l'ennemi
	 * @param vieMax int : vie maximale de l'ennemi
	 * @param x float : ordonné de l'ennemi
	 * @param y float : abscisse de l'ennemi
	 * @param vitesse float : vitesse de l'ennemi, en case par frame
	 * @param largeur float : largeur de l'ennemi
	 * @param hauteur float : hauteur de l'ennemi
     */
    Ennemi(int vie, int vieMax, float x, float y, float vitesse, float largeur, float hauteur);

    /**
     * @brief Destructeur de Ennemi
     * 
     */
    ~Ennemi();


    /**
     * @brief Tire vers un point donné
     * 
     * @param pt point2D : point vers lequel l'ennmi tire
     * @return Vect2D : direction dans laquelle l'ennemi tire vraiment
     */
    Vect2D tirEnnemi(Point2D & pt);

    /**
     * @brief Change le chemin de l'ennemi
     * 
     * @param c std::vector <Point2D> : le tableau de Point2D représentant le chemin de l'ennemi
     */
    void setCheminJoueur(std::vector <Point2D> c);

    /**
     * @brief Change le chemin de patrouille de l'ennemi
     * 
     * @param c std::vector <Point2D> : le tableau de Point2D représentant le chemin de l'ennemi
     */
    void setCheminPatrouille(std::vector <Point2D> c);


    void setAggro(bool b);


    /**
     * @brief Retourne l'indice du point actuel sur le chemin de l'ennemi
     * 
     * @return int : indice du point actuel sur le chemin de l'ennemi
     */
    int getIndiceDeplacement() const;

    /**
     * @brief Permet de vérifier si un point est dans le champs de vision de l'ennemi
     * 
     * @param pt Point2D : point à vérifier
     * @return true : si le point est dans le champs de vision de l'ennemi
     * @return false : si le point n'est dans son champs de vision
     */
    bool estDansChampVision(Point2D & pt);


	/**
	 * @brief Retourne une hitbox prédictive du deplacement de l'ennemi si il patrouille, affin de detecter les collisions
	 * 
	 * @return HitboxRectangle : hitbox virtuelle de l'ennemi, c'est à dire la hitbox qu'il aurait si il avait fait le déplacement
	 */
    HitboxRectangle patrouilleDetecterCollision();

    /**
     * @brief Avance selon les points de patrouilles
     * 
     */
    Vect2D patrouilleDeplacement();

    /**
     * @brief  Avance selon les points du chemin
     * 
     * @return Vect2D : direction dans laquelle l'ennemi avance
     */
    Vect2D cheminDeplacement();

    /**
     * @brief Ajoute un point à la patrouille de l'ennemi
     * 
     * @param pt Point2D : point à ajouter à la patrouille
     */
    void ajouterPointPatrouille(const Point2D & pt);

    /**
     * @brief Ajoute un point à la patrouille de l'ennemi
     * 
     * @param x int : ordonné du point à ajouter à la patrouille
     * @param y int : abscisse du point à ajouter à la patrouille
     */
    void ajouterPointPatrouille(const int x, const int y);

    /**
     * @brief Affiche le Chemin de l'ennemi
     * 
     */
    void afficherChemin();

    /**
     * @brief 
     * 
     * @return true si l'ennemi est en état d'aggro
     * @return false sinon
     */
    bool estAggro() const;

    
	/**
	 * @brief Affiche l'ennemi
	 * 
	 * @param o std::ostream : flux
	 * @param p Perso : perso à afficher
	 * @return std::ostream& : flux
	 */
    friend std::ostream& operator<<(std::ostream& o, const Ennemi & e);


    private : 

    float m_distTir;
    float m_champVision;
    Vect2D m_orientation;

    int m_nbPointPatrouille;
    int m_pointDestination;
    std::vector < Point2D > m_pointsPatrouille;
    std::vector < Point2D > m_cheminJoueur;

    bool m_aggro;

    float distancePointDestination() const;
    void passerAuPointDestinationSuivant();
};

#endif