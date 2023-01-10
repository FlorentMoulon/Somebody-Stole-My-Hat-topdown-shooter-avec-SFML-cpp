#ifndef Perso_H
#define Perso_H

#include <vector>
#include "Vect2D.h"
#include "Point2D.h"
#include "HitboxRectangle.h"
#include "Projectile.h"
#include "Arme.h"
#pragma once


/**
 * @brief Modélise les personages du jeu (joueur et non joueur) avec leur vie, arme, boite de collision. Peu se déplacer, tirer, detecter des collision.
 * 
 */
class Perso{

public:

	/**
	 * @brief Constructeur par défaut de Perso
	 * 
	 */
	Perso();

	/**
	* @brief Constructeur par copie de Perso, créer une copie d'un perso
	* 
	* @param perso Perso : le perso à copier
	*/
	Perso(const Perso & perso);

	/**
	 * @brief Créer un Perso et initialise sa vie, sa position, sa vitesse et sa taille
	 * 
	 * @param vie int : vie du perso
	 * @param vieMax int : vie maximale du perso
	 * @param x float : ordonné du perso
	 * @param y float : abscisse du perso
	 * @param vitesse float : vitesse du perso, en case par frame
	 * @param largeur float : largeur du perso
	 * @param hauteur float : hauteur du perso
	 */
	Perso(int vie, int vieMax, float x, float y, float vitesse, float largeur, float hauteur);

	/**
	 * @brief Destructeur de Perso
	 * 
	 */
	~Perso();


	/**
	 * @brief Affiche la position du perso
	 * 
	 */
	void affichePosition() const;

	/**
	 * @brief Change la position du perso
	 * 
	 * @param x float : ordonné du perso
	 * @param y float : abscisse du perso
	 */
	void setPosition(float x, float y);

	/**
	 * @brief Remet le perso à l'état vivant et sa vie au maximum
	 * 
	 */
	void setVivant();

	/**
	 * @brief Fait avencer le perso dans une certaine direction
	 * 
	 * @param direction Vect2D : direction dans laquelle le perso doit avancer
	 */
	void deplacement(Vect2D direction);

	/**
	 * @brief Retourne une hitbox prédictive du deplacement du Perso affin de detecter les collisions
	 * 
	 * @param vecteurDeplacement Vect2D : direction dans laquelle le perso doit avancer
	 * @return HitboxRectangle : hitbox virtuelle du perso, c'est à dire la hitbox qu'il aurait si il avait fait le déplacement
	 */
	HitboxRectangle detecterCollision(Vect2D vecteurDeplacement);

	/**
	 * @brief Retourne la hitbox du Perso
	 * 
	 * @return HitboxRectangle : hitbox du perso
	 */
	HitboxRectangle getHitbox()const;


	/**
	 * @brief Change la vitesse du perso
	 * 
	 * @param vitesse Float : vitesse du perso
	 */
	void setVitesse(float vitesse);

	/**
	 * @brief Retourne la vitesse du perso
	 * 
	 * @return float : vitesse du perso
	 */
	float getVitesse() const;


	/**
	 * @brief Permet de savoir si le perso est touché par une balle
	 * 
	 * @param balle Projectile : la balle à tester
	 * @return true : si la balle le touche
	 * @return false : si la balle ne le touche pas
	 */
	bool estToucheParBalle(const Projectile & balle);


	/**
	 * @brief Diminue la vie du Perso en fonction du nombre de degat reçus
	 * 
	 * @param degat int : nombre de degat reçus
	 */
	void prendreDegat(int degat);

	/**
	 * @brief Gère la mort du perso
	 * 
	 */
	void mourir();

	/**
	 * @brief Permet de savoir si un perso est mort
	 * 
	 * @return true : si le perso est mort
	 * @return false : si le perso est vivant
	 */
	bool getMort();
	

	/**
	 * @brief Retourne la position du perso
	 * 
	 * @return Point2D : position du perso
	 */
	Point2D getPosition() const;

	/**
	 * @brief Retourne les coordonées du centre du perso
	 * 
	 * @return Point2D : coordonées du centre du perso
	 */
	Point2D getCentre() const;

	/**
	 * @brief Retourne les coordonées du perso sous forme de Vect2D
	 * 
	 * @return Vect2D : coordonées du perso
	 */
	Vect2D convertitPosition() const;

	/**
     * @brief Retourne le nombre de Balle Restante dans le chargeur de l'arme du perso
     * 
     * @return int : nombre de Balle Restante
     */
    int getNbBalleRestante() const;

	/**
     * @brief Trouve le bon deplacement à faire pour ne pas rentrer des les perso, mais juste venir si coller
     * 
     * @param hitbox HitboxRectangle : la hitbox de l'objet à déplacer
     * @param hitboxVirtuelle HitboxRectangle : la hitbox virtuelle (prévusualisation du déplacement) de l'objet à déplacer
     * @param direction Vect2D : direction du deplacement
     * @return Vect2D : un vecteur qui permet de coller la hitbox au mur à la place de rentrer dedans
     */
    Vect2D collisionPerso(const HitboxRectangle & hitbox, HitboxRectangle hitboxVirtuelle, const Vect2D & direction) const;
    

	/**
	 * @brief Vérifie si le perso est en contact avec une hitbox
	 * 
	 * @param hitbox HitboxRectangle
	 * @return true : si ils sont en contact
	 * @return false : si ils ne sont pas en contact
	 */
    bool estEnContact(const HitboxRectangle & hitbox) const;
    


	/**
	 * @brief Change l'arme du perso en une arme donnée
	 * 
	 * @param arme Arme : l'arme du perso
	 */
	void setArme(const Arme & arme);

	/**
	 * @brief Modifie l'arme du perso
	 * 
	 * @param delai float : delai de l'arme
	 * @param nbMunitionMax int : nombre de munition maximum dans un chargeur
	 * @param degat int : degat de l'arme
	 * @param vitesse float : vitesse des balles tirées par l'arme
	 * @param penetration int : penetration des balles tirées par l'arme
	 * @param largeur float : largeur des balles tirées par l'arme
	 * @param hauteur float : hauteur des balles tirées par l'arme
	 */
	void setArme(float delai, int nbMunitionMax, int degat, float vitesse, int penetration, float largeur, float hauteur);
	
	/**
	 * @brief Retourne les munitions type utilisé par l'arme du perso
	 * 
	 * @return Projectile :  munitions type utilisé par l'arme
	 */
	Projectile getMunitionType() const;

	/**
	 * @brief Retourne le nombre de projectile actuellement en "vie"
	 * 
	 * @return int : nombre de projectile
	 */
	int getNombreProjectile() const;

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
	 * @brief Tire une balle dans une direction donnée
	 * 
	 * @param vectTir Vect2D : direction dans laquelle il faut tirer
	 */
	void tirer(const Vect2D & vectTir);

	/**
	 * @brief Met à jour les delai de l'arme
	 * 
	 */
	void updateDelai();

	/**
	 * @brief Affiche le perso
	 * 
	 * @param o std::ostream : flux
	 * @param p Perso : perso à afficher
	 * @return std::ostream& : flux
	 */
	friend std::ostream& operator<<(std::ostream& o, const Perso & p);


protected: 

	int m_vie, m_vieMax; 
	Point2D m_position;
	float m_vitesse;
	HitboxRectangle m_hitbox;

	bool m_estMort;

	Arme m_arme;
};

#endif 