#include "Noeud.h"

Noeud &Noeud::operator=(const Noeud &n){
    heuristique = n.heuristique;
    distanceDepart = n.distanceDepart;
    score = n.score;

    parent = n.parent;
    position = n.position;

    return *this;
}


std::ostream& operator<<(std::ostream& o, const Noeud & n){
    o<<"POSITION : "<<n.position << "  PARENT : "<<n.parent<< " SCORE : "<<n.score<<std::endl;
    return o;
}


//bool operator==(const Noeud & n) const{}