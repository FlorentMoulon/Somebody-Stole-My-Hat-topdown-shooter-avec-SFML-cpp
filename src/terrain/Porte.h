#ifndef PORTE_H
#define PORTE_H

#include "iostream"


/**
 * @brief Modélise une porte avec des coordonnées et une direction
 * 
 */
struct Porte
{
    /**
     * @brief Constructeur par défaut de Porte
     * 
     */
    Porte();

    /**
     * @brief Créer une porte à une certaine position avec une orientation donné
     * 
     * @param X int : ordonné de la porte
     * @param Y int : abscisse de la porte
     * @param Orientation char : orientation de la porte
     */
    Porte(int X, int Y, char Orientation);

    /**
     * @brief Affiche la porte
     * 
     * @param o std::ostream : flux
     * @param t Porte : porte
     * @return std::ostream& : flux
     */
    friend std::ostream& operator<<(std::ostream& o, const Porte & p);



    /**
     * @brief int : ordonné de la porte
     * 
     */
    int x;

    /**
     * @brief int : abscisse de la porte
     * 
     */
    int y;

    /**
     * @brief char : orientation de la porte
     * 
     */
    char orientation;
};

#endif