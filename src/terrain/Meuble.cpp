#include "Meuble.h"
#include "Point2D.h"
#include "Case.h"
#include "iostream"

Meuble::Meuble() :  m_id(0,0), m_largeur(1), m_hauteur(1), m_type('!'), m_dir('h'), m_chg(1,1)
{

}

Meuble::Meuble(unsigned int largeur, unsigned int hauteur, char type, Point2D id) : m_id(id),
m_largeur(largeur), m_hauteur(hauteur), m_type(type), m_dir('h'), m_chg(1,1)
{
    setCbd();
    setMur();
}

Meuble::Meuble(unsigned int largeur, unsigned int hauteur, char type) : m_id(0,0),
m_largeur(largeur), m_hauteur(hauteur), m_type(type), m_dir('h'), m_chg(1,1)
{
    setCbd();
    setMur();
}

Meuble::Meuble(unsigned int largeur, unsigned int hauteur, char type, int id_x, int id_y): m_id(id_x,id_y),
m_largeur(largeur), m_hauteur(hauteur), m_type(type), m_dir('h'), m_chg(1,1)
{

}

Meuble::~Meuble()
{

}



Point2D Meuble::tournerAleatoirement(){
    Point2D vectColler;
    int horientation = rand()%4;
    char hor;

    switch(horientation) {
        case 0:
            hor='h';
            vectColler.set(0,-1);
            break;
        case 1:
            hor='b';
            vectColler.set(0,1);
            break;
        case 2:
            hor='d';
            vectColler.set(1,0);
            break;
        case 3:
            hor='g';
            vectColler.set(-1,0);
            break;
        default:
            hor='h';
            vectColler.set(0,-1);
    }

    changerDir(hor);

    return vectColler;
}


char Meuble::getType()const{
    return m_type;
}

char Meuble::getDir()const{
    return m_dir;
}

Point2D Meuble::getChg() const{
    return m_chg;
}

Point2D Meuble::getCbd() const{
    return m_cbd;
}

Point2D Meuble::getMurChg() const{
    return m_murChg;
}

Point2D Meuble::getMurCbd() const{
    return m_murCbd;
}

unsigned int Meuble::getLargeur() const{
    return m_largeur;
}

unsigned int Meuble::getHauteur() const{
    return m_hauteur;
}




void Meuble::setMur(){
    switch(m_dir) {
        case 'h':
            m_murChg.set(m_chg.x, m_chg.y-1);
            m_murCbd.set(m_chg.x+m_largeur-1, m_chg.y-1);
            break;

        case 'b':
            m_murChg.set(m_chg.x, m_chg.y+m_hauteur);
            m_murCbd.set(m_chg.x+m_largeur-1, m_chg.y+m_hauteur);
            break;

        case 'd':
            m_murChg.set(m_chg.x+m_largeur, m_chg.y);
            m_murCbd.set(m_chg.x+m_largeur, m_chg.y+m_hauteur-1);
            break;

        case 'g':
            m_murChg.set(m_chg.x-1, m_chg.y);
            m_murCbd.set(m_chg.x-1, m_chg.y+m_hauteur-1);
            break;

        default:
            std::cout<<std::endl<<"EREUR : probleme de direction !"<<std::endl;
    }
}

void Meuble::setCbd(){
    m_cbd.x = m_chg.x + m_largeur-1;
    m_cbd.y = m_chg.y + m_hauteur-1;
    setMur();
}

void Meuble::setChg(const Point2D& chg){
    m_chg.x = chg.x;
    m_chg.y = chg.y;
    setCbd();
}

void Meuble::setChg(unsigned int x, unsigned int y){
    m_chg.x = x;
    m_chg.y = y;
    setCbd();
}

void Meuble::setDim(unsigned int largeur, unsigned int hauteur){
    m_largeur = largeur;
    m_hauteur = hauteur;
    setCbd();
}

void Meuble::changerDir(char dir){
    if (m_dir!=dir){
        if((m_dir=='h' && dir=='b') || (m_dir=='b' && dir=='h')){
            m_dir = dir;
            setMur();
        }else if((m_dir=='g' && dir=='d') || (m_dir=='d' && dir=='g')){
            m_dir = dir;
            setMur();
        }

        else{
            m_dir = dir;
            setDim(m_hauteur, m_largeur);
        }
    }
}

void Meuble::set(int L, int H, char TYPE, Point2D idIm){
    m_hauteur=H;
    m_largeur=L;
    m_type=TYPE;
    m_dir='h';
    m_id = idIm;
    
    setChg(0,0);
    setCbd();
    setMur();
}


std::ostream& operator<<(std::ostream& o, const Meuble & m){
    for (int i=m.m_chg.x; i<=m.m_cbd.x; i++){
        for (int j=m.m_chg.y; j<=m.m_cbd.y; j++){
            o<<m.m_type;
        }
        o<<std::endl;
    }o<<std::endl;o<<std::endl;

    o<<"largeur:"<<m.m_largeur<<", hauteur:"<<m.m_hauteur<<std::endl;

    return o;
}