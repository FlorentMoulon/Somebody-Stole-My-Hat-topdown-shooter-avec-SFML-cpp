#ifndef HitboxRectangle_H
#define HitboxRectangle_H

#include "Point2D.h"

/**
 * @brief Boite de collision rectangulaire défini par des coordonnées et une taille. Peut detecter la collision avec une autre hitbox
 * 
 */
class HitboxRectangle{

    public :

    /**
     * @brief Constructeur par défaut de HitboxRectangle
     * 
     */
    HitboxRectangle();

    /**
     * @brief Constructeur par copie de HitboxRectangle
     * 
     * @param hitbox HitboxRectangle : hitbox à copier
     */
    HitboxRectangle(HitboxRectangle const & hitbox);

    /**
     * @brief Créer une HitboxRectangle d'une taille donnée avec une position donnée
     * 
     * @param largeur float : largeur de la HitboxRectangle
     * @param hauteur float : hauteur de la HitboxRectangle
     * @param centre Point2D : coordonnées du centre de la HitboxRectangle
     */
    HitboxRectangle(float largeur,float hauteur, Point2D centre);

    /**
     * @brief Créer une HitboxRectangle d'une taille donnée avec une position donnée
     * 
     * @param largeur float : largeur de la HitboxRectangle
     * @param hauteur float : hauteur de la HitboxRectangle
     * @param x float : ordonné du centre de la HitboxRectangle
     * @param y float : abscisse  du centre de la HitboxRectangle
     */
    HitboxRectangle(float largeur,float hauteur, float x, float y);


    /**
     * @brief Retourne le coin haut gauche de la hitbox
     * 
     * @return Point2D : coin haut gauche de la hitbox
     */
    Point2D getChg() const;
    /**
     * @brief Retourne le coin haut droit de la hitbox
     * 
     * @return Point2D : coin haut droit de la hitbox
     */
    Point2D getChd() const;
    
    /**
     * @brief Retourne le coin bas droit de la hitbox
     * 
     * @return Point2D : coin bas droitde de la hitbox
     */
    Point2D getCbd() const;

    /**
     * @brief Retourne le coin bas gauche de la hitbox
     * 
     * @return Point2D : coin bas gauche de la hitbox
     */
    Point2D getCbg() const;

    /**
     * @brief Retourne la largeur de la hitbox
     * 
     * @return float : largeur de la hitbox
     */
    float getLargeur() const;

    /**
     * @brief Retourne la hauteur de la hitbox
     * 
     * @return float : hauteur de la hitbox
     */
    float getHauteur() const;

    /**
     * @brief Retourne le centre de la hitbox
     * 
     * @return Point2D : centre de la hitbox
     */
    Point2D getCentre() const;


    /**
     * @brief Change le centre de la hitbox
     * 
     * @param x float : ordonné du centre de la HitboxRectangle
     * @param y float : abscisse  du centre de la HitboxRectangle
     */
    void setCentre(const float x, const float y);

    /**
     * @brief Change le centre de la hitbox
     * 
     * @param point2D Point2D : coordonnées du centre de la HitboxRectangle
     */
    void setCentre(const Point2D & point2D);

    /**
     * @brief Modifie la taille de la hitbox
     * 
     * @param largeur float : largeur de la hitbox
     * @param hauteur float : hauteur de la hitbox
     */
    void setTaille(float largeur, float hauteur);


    /**
     * @brief Vérifie si la hitbox est en contact avec une autre HitboxRectangle
     * 
     * @param hitbox HitboxRectangle : hitbox à vérifier
     * @return true : si les deux hitboxs sont en contact
     * @return false : si les deux hitboxs ne sont pas en contact
     */
    bool estEnContact(const HitboxRectangle & hitbox) const;

    /**
     * @brief Copie une HitboxRectangle
     * 
     * @param hitbox HitboxRectangle : hitbox à copier
     * @return HitboxRectangle& : hitbox copiée
     */
    HitboxRectangle &operator=(const HitboxRectangle & hitbox);

    /**
     * @brief Affiche la HitboxRectangle
	 * 
	 * @param o std::ostream : flux
	 * @param h HitboxRectangle : hitbox à afficher
	 * @return std::ostream& : flux
     */
    friend std::ostream& operator<<(std::ostream& o, const HitboxRectangle & h);

    private :
    
    float m_largeur;
    float m_hauteur;
    Point2D m_centre;

    bool pointEstDans(float x, float y) const;
};

#endif 