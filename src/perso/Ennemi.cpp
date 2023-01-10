#include "Ennemi.h"
#include "math.h"
#include "cassert"
#include<chrono>
#include <time.h>  
#include<thread>


Ennemi::Ennemi() : Perso::Perso(), m_nbPointPatrouille(0), m_pointDestination(0), m_aggro(false) {

}

Ennemi::Ennemi(int vie, int vieMax, float x, float y,
float vitesse, float largeur, float hauteur) : 
Perso::Perso(vie, vieMax, x, y, vitesse, largeur, hauteur),
m_champVision(80), m_orientation(0,-1),
m_nbPointPatrouille(0), m_pointDestination(0), m_aggro(false){

}
    
Ennemi::~Ennemi(){

}

bool Ennemi::estDansChampVision(Point2D & pt){
    Point2D tmp;
    tmp = m_position - pt;

    Vect2D direction (pt.convertirPtToVect());
    float teta = direction.angle(m_orientation);
    teta = teta * 3.1415926535 / 180;
    if ((sqrt(teta*teta) <= m_champVision / 2) && m_position.distance(pt)<5) return true;
    //if (m_position.distance(pt) < 5) return true;
    return false;
}


void Ennemi::setCheminJoueur(std::vector <Point2D> c){
    m_cheminJoueur.clear();
    m_pointDestination = 0;
    m_cheminJoueur = c;
}

void Ennemi::setCheminPatrouille(std::vector <Point2D> c){
    m_pointsPatrouille.clear();
    m_pointDestination = 0;
    m_pointsPatrouille = c;
    
    for (int i; i<(int) c.size(); i++){
        m_pointsPatrouille.push_back(c[(int)c.size()-i+1]);
    }
}

void Ennemi::setAggro(bool b){
    m_aggro = true;
    m_pointDestination = 0;
}

int Ennemi::getIndiceDeplacement() const{
    return m_pointDestination;
}

Vect2D Ennemi::tirEnnemi(Point2D & pt){
    Point2D tmpPt;
    tmpPt = pt - m_position;

    int randomizer = rand() % 9;
    float angle = (randomizer - 5) * 3.1415926535 / 180;

    Vect2D tmp = tmpPt.convertirPtToVect();
    tmp.rotation(angle);
    
    tirer(tmp);
    return tmp;
}

HitboxRectangle Ennemi::patrouilleDetecterCollision(){
    assert(m_nbPointPatrouille > 0);

    Vect2D direction(
        m_pointsPatrouille[m_pointDestination].x - m_position.x,
        m_pointsPatrouille[m_pointDestination].y - m_position.y
    );

    return detecterCollision(direction);
}

Vect2D Ennemi::patrouilleDeplacement(){
    Vect2D direction(0, 0);
    if (m_pointsPatrouille.size() >0){
        direction.x = m_pointsPatrouille[m_pointDestination].x - m_position.x;
        direction.y = m_pointsPatrouille[m_pointDestination].y - m_position.y;
        direction.normaliser();

        if(m_pointDestination < (int) m_pointsPatrouille.size()){
            if (m_position.distance(m_pointsPatrouille[m_pointDestination]) <= m_vitesse * direction.norme()){
                m_pointDestination++;
                direction.x = m_pointsPatrouille[m_pointDestination].x - m_position.x;    
                direction.y = m_pointsPatrouille[m_pointDestination].y - m_position.y;
            }
            direction.normaliser();
        }
    }
    
    return direction;
}


Vect2D Ennemi::cheminDeplacement(){
    Vect2D direction(0, 0);
    if (m_cheminJoueur.size() >0){
        direction.x = m_cheminJoueur[m_pointDestination].x - m_position.x;
        direction.y = m_cheminJoueur[m_pointDestination].y - m_position.y;
        direction.normaliser();

        if(m_pointDestination < (int) m_cheminJoueur.size()){
            if (m_position.distance(m_cheminJoueur[m_pointDestination]) <= m_vitesse * direction.norme()){
                m_pointDestination++;
                direction.x = m_cheminJoueur[m_pointDestination].x - m_position.x;    
                direction.y = m_cheminJoueur[m_pointDestination].y - m_position.y;
            }
            direction.normaliser();
        }
    }
    return direction;
}


void Ennemi::afficherChemin(){
    for (int i = 0; i < (int)m_cheminJoueur.size(); i++){
		std::cout<<"Point "<<i<<" "<< m_cheminJoueur[i]<<std::endl;
	}
}

bool Ennemi::estAggro() const{
    return m_aggro;
}

void Ennemi::ajouterPointPatrouille(const Point2D & pt){
    m_pointsPatrouille.push_back(pt);
    m_nbPointPatrouille ++;
}

void Ennemi::ajouterPointPatrouille(const int x, const int y){
    Point2D pt(x,y);
    m_pointsPatrouille.push_back(pt);
    m_nbPointPatrouille ++;
}

float Ennemi::distancePointDestination() const{
    return sqrt(
        pow(m_position.x - m_pointsPatrouille[m_pointDestination].x, 2) +
        pow(m_position.y - m_pointsPatrouille[m_pointDestination].y, 2));
}

void Ennemi::passerAuPointDestinationSuivant(){
    m_pointDestination ++;
    m_pointDestination = m_pointDestination % m_nbPointPatrouille;
}

std::ostream& operator<<(std::ostream& o, const Ennemi & e){
    o<<"Ennemi : vie :"<<e.m_vie<<", vieMax :"<<e.m_vieMax;
    o<<", vitesse :"<<e.m_vitesse<<", estMort ?"<<e.m_estMort<<std::endl;

    o<<"position :"<<e.m_position<<std::endl;
    o<<"hitbox :"<<e.m_hitbox<<std::endl;
    o<<"arme :"<<e.m_arme<<std::endl;
    o<<"orientation :"<<e.m_orientation<<std::endl;

    o<<"distTir :"<<e.m_distTir<<", aggro :"<<e.m_aggro<<", champVision :"<<e.m_champVision;
    o<<", nbPointPatrouille :"<<e.m_nbPointPatrouille<<", pointDestination :"<<e.m_pointDestination;

    for(int i=0; i<e.m_nbPointPatrouille; i++){
        o<<std::endl<<i<<"eme point de patrouille :"<<e.m_pointsPatrouille[i];
    }

    return o;
}