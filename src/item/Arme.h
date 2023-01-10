#ifndef Arme_H
#define Arme_H

#include <vector>
#include "Vect2D.h"
#include "Point2D.h"
#include "Projectile.h"
#include "iostream"

/**
 * @brief Modélise les armes avec leur munition et leur caddence de tir. Peut tirer est gérer ses balles.
 * 
 */
class Arme{

    public :

    /**
     * @brief Constructeutr par défaut d'Arme
     * 
     */
    Arme();

    /**
     * @brief Constructeur par copie d'Arme
     * 
     * @param a Arme : arme à copier
     */
    Arme(const Arme & a);

    /**
     * @brief Créer une arme avec sa cadence et ses munitions types
     * 
     * @param delai float : dealai minimal entre deux tire, en nombre de frame
     * @param nbMunitionMax int : nombre maximale de munition pouvant être tiré avant de recharger
     * @param munitionType Projectile : les munition type tiré par l'arme
     */
    Arme(float delai, int nbMunitionMax, Projectile munitionType);

    /**
	 * @brief Créer une arme avec son delai, se degats et ses munitions types
	 * 
	 * @param delai float : delai de l'arme
	 * @param nbMunitionMax int : nombre de munition maximum dans un chargeur
	 * @param degat int : degat de l'arme
	 * @param vitesse float : vitesse des balles tirées par l'arme
	 * @param penetration int : penetration des balles tirées par l'arme
	 * @param largeur float : largeur des balles tirées par l'arme
	 * @param hauteur float : hauteur des balles tirées par l'arme
	 */
    Arme(float delai, int nbMunitionMax, int degat, float vitesse, int penetration, float largeur, float hauteur);

    /**
     * @brief Destructeur d'Arme
     * 
     */
    ~Arme();
    

    /**
     * @brief Affiche l'Arme
	 * 
	 * @param o std::ostream : flux
	 * @param p Arme : arme à afficher
	 * @return std::ostream& : flux
     */
    friend std::ostream& operator<<(std::ostream& o, const Arme & a);


    /**
     * @brief Change tout les paramètre de l'arme
     * 
	 * @param delai float : delai de l'arme
	 * @param nbMunitionMax int : nombre de munition maximum dans un chargeur
	 * @param degat int : degat de l'arme
	 * @param vitesse float : vitesse des balles tirées par l'arme
	 * @param penetration int : penetration des balles tirées par l'arme
	 * @param largeur float : largeur des balles tirées par l'arme
	 * @param hauteur float : hauteur des balles tirées par l'arme
     */
    void set(float delai, int nbMunitionMax, int degat, float vitesse, int penetration, float largeur, float hauteur);
    
    /**
     * @brief Transforme l'arme en une copie d'une arme donnée
     * 
	 * @param arme Arme : arme à copier
     */
    void set(const Arme & arme);

    /**
     * @brief Recharge les munitions
     * 
     */
    void recharger();
    

    /**
     * @brief Retourne la munition type de l'arme
     * 
     * @return Projectile : munition type de l'arme
     */
    Projectile getMunitionType()const;

    /**
     * @brief Retourne le nombre dee Balle Restante dans le chargeur de l'arme
     * 
     * @return int : nombre dee Balle Restante
     */
    int getNbBalleRestante() const;

    /**
     * @brief Change la munition type de l'arme
     * 
	 * @param degat int : degat de l'arme
	 * @param vitesse float : vitesse des balles tirées par l'arme
	 * @param penetration int : penetration des balles tirées par l'arme
	 * @param largeur float : largeur des balles tirées par l'arme
	 * @param hauteur float : hauteur des balles tirées par l'arme
     */
    void setMunitionType(int degat, float vitesse, int penetration, float largeur, float hauteur);

	/**
	 * @brief Retourne le nombre de projectile actuellement en "vie"
	 * 
	 * @return int : nombre de projectile
	 */
	int getNombreProjectile() const;

    /**
     * @brief Ajoute un projectile au tableau gérant les balles actuellement en "vie"
     * 
     * @param nvProjectile Projectile : projectile à ajouter au tableau 
     */
	void ajouterProjectile(const Projectile & nvProjectile);

	/**
	 * @brief Supprime le Ième prjectile actuellement en "vie"
	 * 
	 * @param i int : indice du projectile à supprimer
	 */
	void supprimerIemeProjectile(const int i);

    /**
	 * @brief Retourne le Ième prjectile actuellement en "vie"
	 * 
	 * @param i int : indice du projectile à recupérer
	 * @return Projectile : Ième prjectile
	 */
	Projectile getIemeProjectile(const int i) const;

    /**
	 * @brief Fait avancer le Ième prjectile
	 * 
	 * @param i int : indice du projectile à faire avancer
	 */
	void avancerIemeProjectile(const int i);


    /**
	 * @brief Tire une balle dans une direction donnée à partir d'un point donné
	 * 
	 * @param vectTir Vect2D : direction dans laquelle il faut tirer
     * @param position Point2D : point à pertir duquel il faut tirer
     * @return true : si il est possible de tirer, en fonction du delai
     * @return false : s'il n'est pas possible de tirer
     */
    bool tirer(const Vect2D & vectTir, const Point2D & position);

    /**
     * @brief  Vérifie s'il est possible de tirer, en fonction du delai, sans tirer de balle
     * 
     * @return true : si il est possible de tirer, en fonction du delai
     * @return false : s'il n'est pas possible de tirer
     */
    bool tirerSansBalle();

	/**
	 * @brief Met à jour les delai de l'arme
	 * 
	 */
    void updateDelai();


    private :
    
    float m_delai;
    int m_nbMunition;
    int m_nbMunitionMax;
    Projectile m_munitionType;
    float m_decompte;

    std::vector<Projectile> m_projectiles;
    int m_nbProjectile;
};

#endif 