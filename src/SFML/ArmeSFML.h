#ifndef ArmeSFML_H
#define ArmeSFML_H

#include "Perso.h"
#include "Arme.h"
#include "ProjectileSFML.h"

#include <SFML/Graphics.hpp>

/**
 * @brief (surcouche de la classe Arme) Permet de gérer les armes avec SFML
 * 
 */
class ArmeSFML{
    public :

    /**
     * @brief Constructeur par défaut de ArmeSFML
     * 
     */
    ArmeSFML();

    /**
     * @brief Constructeur de ArmeSFML qui permet de choisir les paramètres de l'arme
     * 
     * @param delai float : délai entre chaque tir
     * @param nbMunition int : nombre de munitions de l'arme
     * @param degat int : dégâts infligés par l'arme
     * @param vitesse float : vitesse du projetcile de l'arme
     * @param penetration int pénétration du projectile
     */
    ArmeSFML(float delai, int nbMunition, int degat, float vitesse, int penetration,  float largeur, float hauteur);

    /**
     * @brief Constructeur par copie de ArmeSFML
     * 
     * @param a ArmeSFML : arme à copier
     */
    ArmeSFML(const ArmeSFML & a);

    /**
     * @brief Destructeur de ArmeSFML
     * 
     */
    ~ArmeSFML();


    /**
     * @brief Modifie les données membres de l'ArmeSFML
     * 
     * @param delai float : délai entre chaque tir
     * @param nbMunition int : nombre de munitions de l'arme
     * @param degat int : dégâts infligés par l'arme
     * @param vitesse float : vitesse du projetcile de l'arme
     * @param penetration int pénétration du projectile
     * @param largeur float : largeur du projectile
     * @param hauteur float : hauteur du projectile
     */
    void setArme(float delai, int nbMunition, int degat, float vitesse, int penetration,  float largeur, float hauteur);

    /**
     * @brief Retourne l'Arme qui est donnée membre de ArmeSFML
     * 
     * @return Arme 
     */
    Arme getArme() const;

    /**
     * @brief Update le délai entre chaque tir
     * 
     */
    void updateDelai();

    /**
     * @brief Tire i projectiles dans un angle choisi (imite un fusil à pompe)
     * 
     * @param vectTir Vect2D : vecteur de tir
     * @param p ProjectileSFML : projectile utilisé pour tirer les projectiles
     * @param position Point2D : position du joueur
     * @param i int : nombre de projectiles à tirer
     * @param angle float : angle de dispersion des projectiles
     */
    bool tirerIProjectiles(const Vect2D & vectTir, ProjectileSFML & p, const Point2D & position, int i, float angle);

    /**
     * @brief Tire un projectile
     * 
     * @param vectTir Vect2D : vecteur de tir
     * @param p ProjectileSFML : projectile utilisé pour tirer les projectiles
     * @param position Point2D : position du joueur 
     */
    bool tirer(const Vect2D & vectTir, ProjectileSFML & p, const Point2D & position);

    /**
     * @brief Tire un projectile sans vérifier le nombre de projectiles disponibles (pour débugger)
     * 
     * @param vectTir Vect2D : vecteur de tir
     * @param p ProjectileSFML : projectile utilisé pour tirer les projectiles
     * @param position Point2D : position du joueur 
     */
    void tirerForceur(const Vect2D & vectTir, ProjectileSFML & p, const Point2D & position);


    /**
     * @brief Recharge les munitions
     * 
     */
    void recharger();
    
    /**
     * @brief Retourne le nombre de projectiles SFML
     * 
     * @return int : nombre de projectiles
     */
    int getNbProjectileSFML() const;

    /**
     * @brief Retourne le nombre dee Balle Restante dans le chargeur de l'arme
     * 
     * @return int : nombre dee Balle Restante
     */
    int getNbBalleRestante() const;

    /**
     * @brief Ajoute un projectile à l'arme
     * 
     * @param nvProjectile ProjectileSFML : projectile à ajouter à l'arme
     */
	void ajouterProjectile(const ProjectileSFML & nvProjectile);

    /**
     * @brief Supprime le i-ème projectile de l'arme
     * 
     * @param i int : indice du projectile à supprimer
     */
	void supprimerIemeProjectile(const int i);

    /**
     * @brief Retourne le i-ème projectile
     * 
     * @param i int : indice du projectile à retourner
     * @return ProjectileSFML : projectile à retourner
     */
	ProjectileSFML getIemeProjectile(const int i) const;

    /**
     * @brief Fait avancer le i-ème projectile
     * 
     * @param i int : indice du projectile à faire avancer
     */
    void avancerIemeProjectile(const int i);



    private :

    Arme m_arme; 

    int m_nbProjectileSFML;
    std::vector <ProjectileSFML> m_projectiles;
};

#endif