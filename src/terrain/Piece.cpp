#include "Piece.h"
#include "Point2D.h"
#include "iostream"

Piece::Piece() : m_largeur(1), m_hauteur(1), m_chg(1,1)
{

}

Piece::Piece(unsigned int largeur, unsigned int hauteur): 
m_largeur(largeur), m_hauteur(hauteur), m_chg(1,1)
{

}

Piece::Piece(const Point2D& chg, const Point2D& cbd) : 
m_largeur(cbd.x - chg.x +1 ), m_hauteur(cbd.y - chg.y +1), m_chg(chg)
{

}






Point2D Piece::getChg() const{
    return m_chg;
}

Point2D Piece::getCbd() const{
    Point2D cbd(m_chg.x + m_largeur, m_chg.y + m_hauteur);
    return cbd;
}

unsigned int Piece::getLargeur() const{
    return m_largeur;
}

unsigned int Piece::getHauteur() const{
    return m_hauteur;
}






std::ostream& operator<<(std::ostream& o, const Piece & m){
    o<<"Piece : ";
    o<<"largeur:"<<m.m_largeur<<", hauteur:"<<m.m_hauteur<<std::endl;
    o<<"x:"<<m.m_chg.x<<", y:"<<m.m_chg.y<<std::endl;

    return o;
}