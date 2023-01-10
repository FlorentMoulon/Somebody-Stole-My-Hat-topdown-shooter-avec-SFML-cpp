#ifndef PIECE_H
#define PIECE_H

#include "Point2D.h"
#include "iostream"


/**
 * @brief Modélise une piece du terrain avec des coordonnées, une hauteur et une largeur
 * 
 */
class Piece
{
    public:

    /**
     * @brief Constructeur par defaut de Piece
     * 
     */
    Piece();

    /**
     * @brief Créer une piece avec une position et une taille donné
     * 
     * @param chg Point2D : coin haut gauche de la piece
     * @param cbd Point2D : coin bas droit de la piece
     */
    Piece(const Point2D& chg, const Point2D& cbd);

    /**
     * @brief Créer une piece avec une taille donné
     * 
     * @param largeur unsigned int : largeur de la piece
     * @param hauteur unsigned int : hauteur de la piece
     */
    Piece(unsigned int largeur, unsigned int hauteur);


    /**
     * @brief Change le coin haut gauche de la piece
     * 
     * @param chg Point2d : coin haut gauche de la piece
     */
    void setChg(const Point2D& chg);


    /**
     * @brief Renvoie le coin haut gauche de la piece
     * 
     * @return Point2D : coin haut gauche de la piece
     */
    Point2D getChg() const;

    /**
     * @brief Renvoie le coin bas droit de la piece
     * 
     * @return Point2D : coin bas droit de la piece
     */
    Point2D getCbd() const;
    
    /**
     * @brief Get the Largeur object
     * 
     * @return unsigned int 
     */

    /**
     * @brief Renvoie la largeur de la piece
     * 
     * @return unsigned int : la largeur de la piece
     */
    unsigned int getLargeur() const;

    /**
     * @brief Renvoie la hauteur de la piece
     * 
     * @return unsigned int : la hauteur de la piece
     */
    unsigned int getHauteur() const;


    /**
     * @brief Affiche la piece
     * 
     * @param o std::ostream : flux
     * @param m Piece : piece à afficher
     * @return std::ostream& : flux
     */
    friend std::ostream& operator<<(std::ostream& o, const Piece & m);

    
    
    private:

    unsigned int m_largeur;
    unsigned int m_hauteur;

    Point2D m_chg;
};

#endif // PIECE_H