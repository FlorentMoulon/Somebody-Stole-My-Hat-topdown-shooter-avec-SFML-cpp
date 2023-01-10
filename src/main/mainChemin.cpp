#include "Chemin.h"
#include "TerrainSFML.h"
#include "Point2D.h"

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>



int main(){
    TerrainSFML ter(20, 20, 100);

    std::cout<<"etape0"<<std::endl;

    ter.genererImage();
    std::cout<<"etape1"<<std::endl;
    Point2D depart (2, 18);
    Point2D arrivee (5, 11);

    std::cout<<"etape2"<<std::endl;

    Chemin chemin(ter.m_ter, depart, arrivee);

    std::cout<<"etape3"<<std::endl; 

    std::vector<Point2D> c;

    //std::cout<<"etape4"<<std::endl;

    c = chemin.trouveChemin();

    std::cout<<"etape4"<<c.size()<<std::endl;

    sf::Image traitL;
    traitL.create(100/5, 100/5);
    //sf::Image traitH;
    //traitH.create(m_tailleCase, m_tailleCase/5);
    sf::Image map;
    map.loadFromFile("tmp/map.png");

    for (int i =0; i<(int) c.size(); i++){
        map.copy(traitL, ((c[i].x)*100), ((c[i].y)*100));
        std::cout<<c[i];
    }
    std::cout<<ter.m_ter;
    map.saveToFile("tmp/pathFinding.png");

    Point2D nouveauDepart (13, 9);
    Point2D nouveauArrivee (15,11 );
    traitL.create(20, 20, sf::Color::Red);

    chemin.setArriveeDepart(nouveauDepart, nouveauArrivee);
    std::cout<<nouveauDepart<< "      "<< std::endl;
    c.clear();
    std::cout<<"passe0"<<std::endl;
    c=chemin.trouveChemin();
    std::cout<<"passe0"<<std::endl;
    for (int i =0; i<(int) c.size(); i++){
        map.copy(traitL, ((c[i].x)*100) , ((c[i].y)*100));
        std::cout<<c[i];
    }
    std::cout<<ter.m_ter;
    map.saveToFile("tmp/pathFinding.png");


    return 0;
}