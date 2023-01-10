#ifndef Projectile_H
#define Projectile_H

#include "Vect2D.h"
#include "Point2D.h"
#include "HitboxRectangle.h"
#include "iostream"


/**
 * @brief Modélise les balles avec leur position, vitesse, hitbox et dégats.
 * 
 */
class Projectile{

    public :

    /**
     * @brief Constructeur par défaut de Projectile
     * 
     */
    Projectile();

    /**
     * @brief Constructeur par copie de Projectile
     * 
     * @param p Projectile : projectile à copier
     */
    Projectile(const Projectile & p);

    /**
     * @brief Créer un projectile avec sa position, sa taille, sa vitesse et ses dégats
     * 
     * @param degat int : degat du projectile
	 * @param vitesse float : vitesse du projectile
	 * @param penetration int : penetration du projectile
     * @param direction Vect2D : direction dans laquelle le projectile à été tiré
     * @param position Point2D : position du projectile
	 * @param largeur float : largeur du projectile
	 * @param hauteur float : hauteur du projectile
     */
    Projectile(int degat, float vitesse, int penetration, Vect2D direction, Point2D position, float largeur, float hauteur);
   
    /**
    * @brief Destructeur de Projectile
    * 
    */
    ~Projectile();
    

    /**
     * @brief Change la direction du projectile
     * 
     * @param direction : direction du projectile
     */
    void setDirection(const Vect2D & direction);

    /**
     * @brief Change la position du projectile
     * 
     * @param x float : ordonné du projectile
     * @param y float : abscisse du projectile
     */
    void setPosition(float x, float y);

    /**
     * @brief Modifie un projectile en changeant sa taille, sa vitesse et ses dégats
     * 
     * @param degat int : degat de 
	 * @param vitesse float : vitesse du projectile
	 * @param penetration int : penetration du projectile
	 * @param largeur float : largeur du projectile
	 * @param hauteur float : hauteur du projectile
     */
    void setProjectile(int degat, float vitesse, int penetration, float largeur, float hauteur);

    /**
     * @brief Copie un projectile
     * 
     * @param projectile Projectile : projectile à copier
     */
    void setProjectile(const Projectile & projectile);

    /**
     * @brief Retourne la position du projectile
     * 
     * @return Point2D : position du projectile
     */
    Point2D getPosition() const;

    /**
     * @brief Retourne la position du centre du projectile
     * 
     * @return Point2D : position du centre du projectile
     */
    Point2D getCentre() const;

    /**
     * @brief Retourne la hitbox du projectile
     * 
     * @return HitboxRectangle : hitbox du projectile
     */
    HitboxRectangle getHitbox() const;

    /**
     * @brief Retourne la hauteur du projectile
     * 
     * @return float : hauteur du projectile
     */
    float getHauteur()const;

    /**
     * @brief Retourne la largeur du projectile
     * 
     * @return float : largeur du projectile
     */
    float getLargeur()const;

    /**
     * @brief Retourne la vitesse du projectile
     * 
     * @return float : vitesse du projectile
     */
    float getVitesse()const;

    /**
     * @brief Retourne la direction du projectile
     * 
     * @return Vect2D : direction du projectile
     */
    Vect2D getDirection()const;

    /**
     * @brief Retourne les dégats du projectile
     * 
     * @return int : dégats du projectile
     */
    int getDegat()const;


    /**
     * @brief Affiche le projectile
     * 
     */
    void afficher();

	/**
	 * @brief Affiche le projectile
	 * 
	 * @param o std::ostream : flux
	 * @param p Projectile : projectile à afficher
	 * @return std::ostream& : flux
	 */
    friend std::ostream& operator<<(std::ostream& o, const Projectile & p);

    /**
     * @brief Fait avancer le projectile dans sa direction avec sa vitesse
     * 
     */
    void avancer();

	/**
	 * @brief Retourne une hitbox prédictive du deplacement du projectile affin de detecter les collisions
	 * 
	 * @return HitboxRectangle : hitbox virtuelle du projectile, c'est à dire la hitbox qu'il aurait si il avait fait le déplacement
	 */
    HitboxRectangle detecterCollision();


    private :
    
    int m_degat;
    float m_vitesse;
    int m_penetration;
    float m_largeur;
    float m_hauteur;

    Vect2D m_direction;
    Point2D m_position;
    HitboxRectangle m_hitbox;
};

#endif 