#ifndef MEUBLE_H
#define MEUBLE_H

#include "Point2D.h"
#include "iostream"
#include "Case.h"


/**
 * @brief Modélise un meuble du terrain avec des coordonnées, une hauteur et une largeur et un type
 * 
 */
class Meuble
{
    public:

    /**
     * @brief Constructeur par défaut, créer un meuble de dimension 0 par 0
     * 
     */
    Meuble();

    /**
     * @brief Créer un meuble de dimention hauteur*largeur avec type
     * 
     * @param largeur unsigned int : largeur du meuble
     * @param hauteur unsigned int : hauteur du meuble
     * @param type char : type du meuble
     */
    Meuble(unsigned int largeur, unsigned int hauteur, char type);

    /**
     * @brief Créer un meuble de dimention hauteur*largeur avec type
     * 
     * @param largeur unsigned int : largeur du meuble
     * @param hauteur unsigned int : hauteur du meuble
     * @param type char : type du meuble
     * @param id Point2D : reférence pour la texture à utiliser
     */
    Meuble(unsigned int largeur, unsigned int hauteur, char type, Point2D id);

    /**
     * @brief Créer un meuble de dimention hauteur*largeur avec type
     * 
     * @param largeur unsigned int : largeur du meuble
     * @param hauteur unsigned int : hauteur du meuble
     * @param type char : type du meuble
     * @param id_x int : ordonné de la reférence pour la texture à utiliser
     * @param id_y int : abscisse de la reférence pour la texture à utiliser
     */
    Meuble(unsigned int largeur, unsigned int hauteur, char type, int id_x, int id_y);

    /**
     * @brief Destructeur de Meuble
     * 
     */
    ~Meuble();


    /**
     * @brief Tourne un meuble dans une direction alleatoire
     * 
     * @return Point2D : une direction pour le rapprocher du mur
     */
    Point2D tournerAleatoirement();


    /**
     * @brief Change la position du meuble
     * 
     * @param chg Point2D : les coordonnées du nouveau coin haut gauche du meuble 
     */
    void setChg(const Point2D& chg);

    /**
     * @brief Change la position du meuble
     * 
     * @param x unsigned int : ordonné du nouveau coin haut gauche du meuble
     * @param y unsigned int : abscisse du nouveau coin haut gauche du meuble 
     */
    void setChg(unsigned int x, unsigned int y);

    /**
     * @brief  Redimentionne le meuble et change son type
     * 
     * @param L int : largeur du meuble
     * @param H int : hauteur du meuble
     * @param TYPE char : type du meuble
     * @param idIm Point2D : reférence pour la texture à utiliser
     */
    void set(int L, int H, char TYPE,  Point2D idIm);


    /**
     * @brief Renvoie le type du meuble
     * 
     * @return char : le type du meuble 
     */
    char getType() const;

    /**
     * @brief Renvoie l'orientation du meuble
     * 
     * @return char : l'orientation du meuble
     */
    char getDir() const;

    /**
     * @brief Renvoie le coin haut gauche du meuble
     * 
     * @return Point2D : le coin haut gauche du meuble
     */
    Point2D getChg() const;

    /**
     * @brief Renvoie le coin bas droit du meuble
     * 
     * @return Point2D : le coin bas droit du meuble
     */
    Point2D getCbd() const;

    /**
     * @brief Renvoie le coin haut gauche de la zone ou on aimerai avoir un mur
     * 
     * @return Point2D : le coin haut gauche de la zone ou on aimerai avoir un mur
     */
    Point2D getMurChg() const;

        /**
     * @brief Renvoie le coin bas droit de la zone ou on aimerai avoir un mur
     * 
     * @return Point2D : le coin bas droit de la zone ou on aimerai avoir un mur
     */
    Point2D getMurCbd() const;

    /**
     * @brief Renvoie la largeur du meuble
     * 
     * @return unsigned int : la largeur du meuble
     */
    unsigned int getLargeur() const;

    /**
     * @brief Renvoie la hauteur du meuble
     * 
     * @return unsigned int : la hauteur du meuble
     */
    unsigned int getHauteur() const;

    /**
     * @brief Affiche le meuble
     * 
     * @param o std::ostream : flux
     * @param m Meuble : meuble à afficher
     * @return std::ostream& : flux
     */
    friend std::ostream& operator<<(std::ostream& o, const Meuble & m);
    

    /**
     * @brief Reférence pour la texture à utiliser
     * 
     */
    Point2D m_id;


    
    private:

    unsigned int m_largeur;
    unsigned int m_hauteur;
    char m_type;
    char m_dir;

    Point2D m_chg;
    Point2D m_cbd;
    Point2D m_murChg;
    Point2D m_murCbd;

    void setCbd();
    void setMur();
    void setDim(unsigned int largeur, unsigned int hauteur);
    void changerDir(char dir);

};

#endif // MEUBLE_H