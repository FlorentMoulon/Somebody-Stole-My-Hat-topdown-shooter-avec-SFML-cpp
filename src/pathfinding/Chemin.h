#ifndef CHEMIN_H
#define CHEMIN_H

#include "Point2D.h"
#include "Terrain.h"
#include "Noeud.h"

#include <SFML/Graphics.hpp>
#include <vector>

/**
 * @brief /////////////////////////////////////////////////////////////////////////////////
 * 
 */
class Chemin{
    public : 
    Chemin();
    Chemin(const Terrain & t);
    Chemin(const Terrain &t, Point2D & ptArrivee, Point2D & ptDepart);
    ~Chemin();

    /**
     * @brief Change m_arrivee et m_depart de la classe
     * 
     * @param ptArrivee Point2D : Nouvelle arrivée
     * @param ptDepart Point2D : Nouveau depart
     */
    void setArriveeDepart(Point2D & ptArrivee, Point2D & ptDepart);

    /**
     * @brief Change le terrain sur lequel on fait le pathfinding
     * 
     * @param t Terrain : Nouveau Terrain
     */
    void setGraph(const Terrain & t);

    /**
     * @brief Retrouve le chemin entre m_depart & m_arrivee sur m_ter
     * 
     * @return std::vector<Point2D> liste des coordonnées du chemin, vide si le chemin n'existe pas 
     */
    std::vector<Point2D> trouveChemin(); 

    /**
     * @brief Retourne vrai ou faux si le chemin existe ou non
     * 
     * @return true si il existe un chemin 
     * @return false sinon
     */
    bool cheminExiste();

    /**
     * @brief Definit un noeud en fonction du noeud passé en paramètre
     * 
     * @param parent Noeud : noeud parent pour les coordonnées parentes
     * @param coordY int : coordonnée X
     * @param coordX int : coordonnée X
     * @return Noeud : Noeud dont les coordonnées du parent 
     */
    Noeud definitNoeud(const Noeud & parent, int coordY, int coordX);


    private : 
    
    Terrain m_graph;
    Point2D m_depart;
    Point2D m_arrivee; 
    std::vector<Noeud> m_listeOuverte; 
    std::vector<Noeud> m_listeFermee;

    void cheminReset();
    Noeud InitialisationNoeud();     

    void traiteNoeudsAdjacents(const Noeud & n);
    void traiteNoeud(const Noeud & n, int x, int y);

    std::vector<Point2D> retrouveChemin(std::vector<Noeud> & l);

    
    bool estPlacable(const Case & c);
    bool estDansListe(const std::vector<Noeud> & l, const Noeud & n);
    void majScore(std::vector<Noeud> & l, const Noeud & n);
    Noeud trouveNoeud(std::vector<Noeud> & l, const Point2D & pt);

};  



#endif 