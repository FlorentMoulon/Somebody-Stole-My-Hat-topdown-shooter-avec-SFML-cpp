#ifndef TERRAINSFML_H
#define TERRAINSFML_H


#include "Terrain.h"
#include "Point2D.h"
#include "Meuble.h"
#include <SFML/Graphics.hpp>

/**
 * @brief (surcouche de la classe Terrain) Permet de gérer le terrain avec SFML
 * 
 */
class TerrainSFML{
    public :

    /**
     * @brief Constructeur par défaut de Terrain
     * 
     */
    TerrainSFML();

    /**
     * @brief Constructeur de TerrainSFML reprenant les propriétés d'un Terrain
     * 
     * @param ter Terrain : terrain à partir duquel on crée le TerrainSFML
     * @param t_case float : taille d'une case du terrain en pixel
     */
    TerrainSFML(const Terrain & ter, float t_case);

    /**
     * @brief Constructeur de TerrainSFML à partir de dimensions données
     * 
     * @param l int : Largeur du TerrainSFML à créer
     * @param h int : Longueur du TerrainSFML à créer
     * @param t_case float : taille d'une case du terrain en pixel
     */
    TerrainSFML(int l, int h, float t_case);

    /**
     * @brief Destructeur par défaut de TerrainSFML
     * 
     */
    ~TerrainSFML();

    
    /**
     * @brief Génère l'image correspondant au terrain, utilisée comme background dans le jeu
     * 
     */
    void genererImage();


    /**
     * @brief Teste si une case est un mur ou non
     * 
     * @param X int : abscisse de la case
     * @param Y int : ordonnée de la case
     * @return true : la case est un mur
     * @return false : la case n'est pas un mur
     */
    bool estMur( int X, int Y);

    /**
     * @brief Remplace le terrainSFML par celui passé en paramètre
     * 
     * @param ter TerrainSFML : terrainSFML à partir duquel on modifie le TerrainSFML de la classe
     */
    void changerTerrain(const TerrainSFML & ter);
    
    //bool estMeuble(int X, int Y);

    sf::Image m_image;
    Terrain m_ter; 

    private : 
    float m_tailleCase;

    sf::Rect<int> rectMeuble(const Meuble &m);
    sf::Rect<int> rectPiece(const Piece &p);
};

#endif