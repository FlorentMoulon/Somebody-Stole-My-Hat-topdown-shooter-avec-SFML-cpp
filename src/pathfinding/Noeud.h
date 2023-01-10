#ifndef NOEUD_H
#define NOEUD_H

#include "Point2D.h"

struct Noeud{
    /**
     * @brief Le point parent du noeud
     * 
     */
    Point2D parent;

    /**
     * @brief Position du noeud
     * 
     */
    Point2D position;

    /**
     * @brief Valeur de l'heusitique du noeud, concept lié au pathfinding
     * 
     */
    int heuristique; 


    /**
     * @brief Distance du noeud avec le point de départ
     * 
     */
    int distanceDepart;

    /**
     * @brief Score du noeud
     * 
     */
    int score;  

    /**
     * @brief Copie un noeud donné
     * 
     * @param n Noeud : noeud à copier
     * @return Noeud& : noeud une fois copié
     */
    Noeud &operator=(const Noeud &n);

    /**
     * @brief Affiche le noeud
     * 
     * @param o ostream : flux 
     * @param n Noeud : noeud à afficher
     * @return std::ostream& : flux
     */
    friend std::ostream& operator<<(std::ostream& o, const Noeud & n);
    
    //bool operator==(const Noeud & n) const;
    //bool operator!=(const Noeud & n) const;

};

#endif