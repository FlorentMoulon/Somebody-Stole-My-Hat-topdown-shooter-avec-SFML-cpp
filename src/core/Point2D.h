#ifndef Point2D_H
#define Point2D_H

#include "Vect2D.h"
#include<iostream>

/**
 * @brief Point dans un espace en 2 dimensions
 * 
 */
struct Point2D{

    /**
     * @brief float : ordonné du point
     * 
     */
    float x;

    /**
     * @brief float : abscisse du point
     * 
     */
    float y;

    /**
     * @brief Créer un point avec un ordonné et une abscisse donnés
     * 
     * @param X float : ordonné du point
     * @param Y float : abscisse du point
     */
    Point2D(float X=0, float Y=0);

    /**
     * @brief Constructeur par copie de Point2D
     * 
     * @param pt Point2D : point à copier
     */
    Point2D(const Point2D & pt);


    /**
     * @brief Modifie l'ordonné et l'abscisse du point
     * 
     * @param X float : ordonné du point
     * @param Y float : abscisse du point
     */
    void set(float X, float Y);


    /**
     * @brief Retourne un point avec l'abscisse et l'ordonné échangés
     * 
     * @return Point2D : le point inversé
     */
    Point2D inverser() const;

    /**
     * @brief Retourne un point avec l'abscisse et l'ordonné arondie à l'inférieur
     * 
     * @return Point2D 
     */
    Point2D arrondir() const;

    /**
     * @brief Rapproche le point d'un autre Point2D
     * 
     * @param pt Point2D : point dont il faut se rapprocher
     */
    void rapprocheCoord(Point2D & pt);

    /**
     * @brief Retourne un Vect2D équivalent au Point2D (même x et y)
     * 
     * @return Vect2D : le Point2D converti en Vect2D
     */
    Vect2D convertirPtToVect() const;

    /**
     * @brief Transforme un Vect2D en Point2D équivalent (même x et y)
     * 
     * @param v :Vect2D : le vecteur à transformer
     * @return Point2D : le Vect2D transformé en Point2D 
     */
    Point2D convertir(const Vect2D &v) const;

    /**
     * @brief Calcule la distance entre le point et un autre Point2D
     * 
     * @param pt Point2D : point avec lequel on calcule la distance
     * @return float : distance entre les deux points
     */
    float distance(const Point2D & pt);

    /**
     * @brief Calcule la distance Manhattan (concept lié au pathfinding) entre le point et un autre Point2D
     * 
     * @param pt Point2D : point avec lequel on calcule la distance
     * @return float : distance Manhattan entre les deux points
     */
    float distanceManhattan(const Point2D & pt);


    /**
     * @brief Somme deux Point2D
     * 
     * @param pt Point2D : point à sommer
     * @return Point2D : point somme des deux autres
     */
    Point2D operator+(const Point2D& pt) ;

    /**
     * @brief Soustrait deux Point2D
     * 
     * @param pt Point2D : point à soustraire
     * @return Point2D : point soustraction des deux autres
     */
    Point2D operator-(const Point2D& pt) ;

    /**
     * @brief Copie un Point2D
     * 
     * @param pt Point2D : point à copier
     * @return Point2D& : le point copié
     */
    Point2D &operator=(const Point2D &pt);

    /**
     * @brief Affiche le point
     * 
	 * @param o std::ostream : flux
	 * @param pt Point2D : point à afficher
	 * @return std::ostream& : flux
     */
    friend std::ostream& operator<<(std::ostream& o, const Point2D & pt);

    /**
     * @brief Vérifie que deux point sont égaux, c'est à dire même x et même y
     * 
     * @param pt Point2D : point à comparer
     * @return true : si les deux points sont égaux
     * @return false : si les deux points sont différent
     */
    bool operator==(const Point2D & pt) const;
};

#endif 