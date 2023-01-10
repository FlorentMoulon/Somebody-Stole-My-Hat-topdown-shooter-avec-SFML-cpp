#include "TerrainSFML.h"
#include "JeuSFML.h"
#include <iostream>



int main(){
    JeuSFML jeu;
    jeu.init();
    /*std::cout<<"etape 0"<<std::endl;
    jeu.genererNiveau(1, 25, 30);
    std::cout<<"etape 1"<<std::endl;
    //jeu.test();

    jeu.genererNiveau(5, 30, 30);
    std::cout<<"etape 2"<<std::endl;
    //jeu.test();*/

    jeu.genererNiveau(1, 50, 50);
    std::cout<<"etape 3"<<std::endl;
    //jeu.test();

    

    

    return 0;
}