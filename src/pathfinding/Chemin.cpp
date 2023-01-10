#include "Chemin.h"
#include "math.h"
#include <cassert>

Chemin::Chemin(){}

Chemin::Chemin(const Terrain & t) : m_graph(t), m_depart(0,0), m_arrivee(0,0){}

Chemin::Chemin(const Terrain & t, Point2D & ptDepart, Point2D & ptArrivee) : m_graph(t),
m_depart(ptDepart.inverser()), m_arrivee(ptArrivee.inverser())  {}

Chemin::~Chemin(){}


void Chemin::setArriveeDepart(Point2D & ptArrivee, Point2D & ptDepart){
    assert(m_depart.x >= 0);
    assert(m_depart.y >= 0);
    assert(m_depart.x < m_graph.getLargeur());
    assert(m_depart.y < m_graph.getHauteur());
    assert(m_arrivee.x >= 0);
    assert(m_arrivee.y >= 0);
    assert(m_arrivee.x < m_graph.getLargeur());
    assert(m_arrivee.y < m_graph.getHauteur());

    m_depart = ptDepart.arrondir();
    m_arrivee = ptArrivee.arrondir();
}

void Chemin::setGraph(const Terrain & t){
    m_graph = t;
}


std::vector<Point2D> Chemin::trouveChemin(){
    cheminReset();
    std::vector<Point2D> chemin;
    if (m_depart == m_arrivee){
        chemin.push_back(m_arrivee);
        return chemin;}
    Noeud actuel;
    actuel = InitialisationNoeud();
    int index;

    while (!(actuel.position == m_arrivee) && m_listeOuverte.size()!=0) {
        actuel = m_listeOuverte[0];

        index = 0;

        //Trouver le minimum 
        for (int i =0; i<(int)m_listeOuverte.size(); i++){
            if (m_listeOuverte[i].score < actuel.score){
                index = i;
                actuel = m_listeOuverte[i];
            }
        }
        
        m_listeOuverte.erase(m_listeOuverte.begin()+index);
        m_listeFermee.push_back(actuel);

        traiteNoeudsAdjacents(actuel); 
    }
    
    if (!(actuel.position == m_arrivee)){
        return chemin;
    }
    chemin = retrouveChemin(m_listeFermee);
    return chemin;
}

bool Chemin::cheminExiste(){
    std::vector<Point2D> c;
    c = trouveChemin();
    if (c.size()==0){
        return false;}
    return true;
}

void Chemin::cheminReset(){
    m_listeFermee.clear();
    m_listeOuverte.clear();
}

Noeud Chemin::InitialisationNoeud(){
    Noeud tmp; 

    tmp.position = m_depart;
    tmp.parent=m_depart;

    tmp.distanceDepart = 0;
    tmp.score = m_depart.distanceManhattan(m_arrivee);
    m_listeOuverte.push_back(tmp);
    
    return tmp;
}

void Chemin::traiteNoeudsAdjacents(const Noeud & n){
    Noeud tmp;
    int coordX = n.position.x;
    int coordY = n.position.y;
    if (estPlacable(m_graph.m_matrice[coordY+1][coordX]) && estPlacable(m_graph.m_matrice[coordY][coordX+1])) {
        traiteNoeud(n, 1, 1);
    }
    if (estPlacable(m_graph.m_matrice[coordY+1][coordX]) && estPlacable(m_graph.m_matrice[coordY][coordX-1])) {
        traiteNoeud(n, -1, 1);
    }
    if (estPlacable(m_graph.m_matrice[coordY-1][coordX]) && estPlacable(m_graph.m_matrice[coordY][coordX+1])) {
        traiteNoeud(n, 1, -1);
    }
    if (estPlacable(m_graph.m_matrice[coordY-1][coordX]) && estPlacable(m_graph.m_matrice[coordY][coordX-1])) {
        traiteNoeud(n, -1, -1);
    }
    traiteNoeud(n, 0, -1);
    traiteNoeud(n, -1, 0);
    traiteNoeud(n, 0, 1);
    traiteNoeud(n, 1, 0);
}

void Chemin::traiteNoeud(const Noeud & n, int x, int y){ 
    Noeud tmp;
    int coordX = n.position.x + x;
    int coordY = n.position.y + y;
    Point2D nCoord (coordX, coordY);
    if (! (coordX<0 || coordY < 0 || coordX >= (int)m_graph.getLargeur()-1 || coordY >= (int)m_graph.getHauteur()-1) ){
        if (estPlacable(m_graph.m_matrice[coordY][coordX])){
            tmp = definitNoeud(n, coordY , coordX);
            if (!(estDansListe(m_listeFermee, tmp))){
                if (!(estDansListe(m_listeOuverte, tmp))) m_listeOuverte.push_back(tmp);
                else majScore(m_listeOuverte, tmp);
            }
        }
    }  
}


std::vector<Point2D> Chemin::retrouveChemin(std::vector<Noeud> & l){
    std::vector<Point2D> chemin;
    Noeud tmp;
    Point2D centre (0.5, 0.5);
    //chemin.push_back(m_arrivee + centre);

    tmp = l.back();
    tmp = trouveNoeud(l, tmp.parent);
    while (!(tmp.parent == m_depart) && !(tmp.parent == tmp.position)){

        chemin.push_back(tmp.position + centre);
        tmp = trouveNoeud(l, tmp.parent);
    }
    chemin.push_back(m_depart + centre);
    return chemin;
}


bool Chemin::estPlacable(const Case & c){
    if (c.type == ' ' || c.type =='-') return true;
    else return false;
}


bool Chemin::estDansListe(const std::vector<Noeud> & l, const Noeud & n){
    for (int i =0; i<(int)l.size(); i++){
            if (l[i].position == n.position) return true; 
        }
    return false;
}


void Chemin::majScore(std::vector<Noeud> & l, const Noeud & n){
   for (int i =0; i<(int)l.size(); i++){
        if (l[i].position == n.position){
            if (n.distanceDepart<l[i].distanceDepart) {
                l[i].distanceDepart = n.distanceDepart;
                l[i].parent = n.parent;
                break;                    
            }
        } 
    }
}


Noeud Chemin::trouveNoeud(std::vector<Noeud> & l, const Point2D & pt){
    for (int i = 0; i<(int)l.size(); i++){
        if (l[i].position == pt){
            return l[i];}
    }
    return l[0];
}
    

Noeud Chemin::definitNoeud(const Noeud & parent, int coordY, int coordX){
    Noeud tmp;

    tmp.parent = parent.position;
    Point2D coord (coordX, coordY);
    tmp.position = coord;
    tmp.heuristique = coord.distanceManhattan(m_arrivee);
    tmp.distanceDepart = parent.distanceDepart + coord.distanceManhattan(parent.position);
    tmp.score = tmp.heuristique + tmp.distanceDepart;

    return tmp;
}

