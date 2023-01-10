#include "TerrainSFML.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <cassert>

const int TAILLE_TEXTURE_LARGEUR = 1500;
const int TAILLE_TEXTURE_HAUTEUR = 1000;


TerrainSFML::TerrainSFML(){}

TerrainSFML::TerrainSFML(int l, int h, float t_case ) : m_ter(l, h), m_tailleCase(t_case){
    m_ter.generer();
    sf::Color couleur(0, 0, 0);
    m_image.create(40*100, 40*100, couleur);
}

TerrainSFML::TerrainSFML(const Terrain & ter, float t_case) : m_ter(ter), m_tailleCase(t_case) {
    sf::Color couleur(0, 0, 0);
    m_image.create(40*100, 40*100, couleur);
}

TerrainSFML::~TerrainSFML(){}


void TerrainSFML::changerTerrain(const TerrainSFML & ter){
    m_ter = ter.m_ter;
    m_image = ter.m_image;
}



void TerrainSFML::genererImage(){

    int j = 0;
    sf::Image textureSol;
    assert(textureSol.loadFromFile("data/texture/parquet.png"));
    while(j< (int) m_ter.getNbPiece()){
        float coordX = (m_ter.getIemePiece(j).getChg().x-1/2) * m_tailleCase;
        float coordY = (m_ter.getIemePiece(j).getChg().y-1/2) * m_tailleCase;
        
        int c = rand()%4;
        switch(c){
        case 0 : 
            break;

        case 1 : 
            textureSol.flipHorizontally();
            break;

        case 2 : 
            textureSol.flipVertically();
            break;

        case 3 : 
            textureSol.flipHorizontally();
            textureSol.flipVertically();
            break;

        default : 
            assert(false);
            break;
        }

        m_image.copy(textureSol,  (int)coordX, (int)coordY, rectPiece(m_ter.getIemePiece(j)), true);
        j++;
    
    }   

    sf::Image mur;
    mur.create(m_tailleCase, m_tailleCase);

    for (int i = 0; i<m_tailleCase*m_ter.getLargeur(); i += m_tailleCase){
        for (int j=0; j<m_tailleCase*m_ter.getHauteur(); j+= m_tailleCase){
            if (estMur(i/m_tailleCase, j/m_tailleCase)) m_image.copy(mur, i, j);            
        }
    }

    
    int i = 0;
    sf::Image tileSet;
    assert(tileSet.loadFromFile("data/sprite/tileSet.png"));

    while(i< (int)m_ter.getNbMeuble()){
        int coordX = m_ter.getIemeMeuble(i).getChg().x * m_tailleCase;
        int coordY = m_ter.getIemeMeuble(i).getChg().y * m_tailleCase;

        m_image.copy(tileSet,  coordX, coordY, rectMeuble(m_ter.getIemeMeuble(i)), true);
        i++;
    
    }
    //if(!m_image.saveToFile("tmp/map.png")) std::cout<<"erreur";
}


bool TerrainSFML::estMur(int X, int Y){
    if (m_ter.getYX(Y,X)=='X') return true;
    else return false;
}

sf::Rect<int> TerrainSFML::rectMeuble(const Meuble &m){
    int coordX = m.m_id.x;
    int coordY = m.m_id.y;
    switch (m.getDir()){
        case('b') :
        break;

        case('d') :
        coordX += m.getHauteur();
        break;

        case('g') : 
        coordX += m.getHauteur() + m.getLargeur();
        break;

        case('h') : 
        coordX +=m.getHauteur() *2 + m.getLargeur();
        break;

        default : 
        break;
        
    }
    
    int largeur = m.getLargeur() * m_tailleCase;
    int hauteur = m.getHauteur() * m_tailleCase;
    sf::Rect<int> rectangle(coordX*m_tailleCase, coordY*m_tailleCase, largeur, hauteur);
    return rectangle;

}


sf::Rect<int> TerrainSFML::rectPiece(const Piece &p){
    float coordX = 0 ;//rand()%(int)((TAILLE_TEXTURE_LARGEUR/m_tailleCase - (5 + p.getLargeur())));
    float coordY = 0 ; //rand()%(int)((TAILLE_TEXTURE_HAUTEUR/m_tailleCase - (5 + p.getHauteur())));

    int largeur = (p.getLargeur()+1) * m_tailleCase;
    int hauteur = (p.getHauteur()+1) * m_tailleCase;
    sf::Rect<int> rectangle((int)(coordX), (int)(coordY), largeur, hauteur);
    return rectangle;
}

/*
bool TerrainSFML::estMeuble(int X, int Y){
    if (m_ter.getYX(Y,X) !='X' && m_ter.getYX(Y,X)!=' ' && m_ter.getYX(Y,X)!='-') return true;
    else return false;
}*/

